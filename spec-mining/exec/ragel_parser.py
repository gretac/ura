global_clock_counter = 0 # counter for the clocks: increments when '>' symbol is detected
global_alphabet_counter = 0 # counter for the number of alphabets
global_beginterval_list = []
global_endinterval_list = []
def parser(input):
    global global_clock_counter

    expressions = ["("]
    i = 0
    global global_beginterval_list
    global global_endinterval_list
    interval_str=""
    check_input(input)

    while i < len(input):
        current_char = input[i]
        if current_char == '<':
            exp, i, counter = create_new_expression(input, i + 1, global_clock_counter, "")
            expressions.append(exp)
        elif current_char == '[':
            i+=1
            while current_char != ']':
		current_char = input[i]
		if current_char == ']':
                    break
                interval_str += current_char
                i += 1
            ainterval = interval_str.split(",")
            interval_str = ""
            #print(ainterval[0],ainterval[1])
	    global_beginterval_list.append(ainterval[0])
	    global_endinterval_list.append(ainterval[1])
	    interval_str = ""
        else:
            expressions.append(current_char)
        i += 1

    expressions.append(") @U $~STEP $lerr(R);")

    return "".join(expressions)


def create_new_expression(input, i, counter, new_exp):
    '''
        Creates a new expression which is added to the list of expressionsl
        Uses recursion to handle nested timed regular expressions.

        input: a timed regular expression
        i: index
        counter: clock counter
        new_exp: new expression that is being created

    '''
    global global_clock_counter
    global global_beginterval_list
    global global_endinterval_list
    new_exp += "("
    interval_str=""
    while i < len(input):
        current_char = input[i]
        if current_char == '<':
            i += 1
            new_exp, i, counter = create_new_expression(input, i, counter+1, new_exp)
        elif current_char == '>':
            new_exp = embed_actions(new_exp, counter)
            global_clock_counter += 1
            return (new_exp, i, counter-1)
        elif current_char == '[':
            i+=1
            while current_char != ']':
		current_char = input[i]
		if current_char == ']':
                    break
                interval_str += current_char
                i += 1
            ainterval = interval_str.split(",")
            interval_str = ""
            #print(ainterval[0],ainterval[1])
	    global_beginterval_list.append(ainterval[0])
	    global_endinterval_list.append(ainterval[1])
	    interval_str = ""
        else:
            new_exp += current_char
        i += 1

    return (new_exp, i, counter)


def check_input(input):
    '''
        Checks the input and throws a ValueException when the input is improper.
        Sets global_alphabet_counter to its appropriate value

        Improper input includes timed regular expressions that:
            - have no alphabets (e.g. <>: improper)
            - have characters instead of integers for their alphabets (e.g <a.b>: improper --> <0.1>: proper)
            - have alphabets that do not increment by one (e.g. <0.1.3>: improper --> <0.1.2>: proper)
            - have minimum alphabet that is not 0 (e.g <1.2>: improper --> <0.1>: proper)
            - do not have every '<' matching a corresponding '>' (e.g. <0.1.<2.3>: improper --> <0.1.<2.3>>: proper)

        input: a timed regular expression
    '''

    global global_alphabet_counter

    opening_count = 0
    closing_count = 0
    sq_bracket_count = 0
    alphabets = {}
    intervalMode = False

    for char in input:
        if char == '<':
            opening_count += 1
        if char == '>':
            closing_count += 1
        if char == '[':
            intervalMode = True
        if char == ']':
            intervalMode = False
        if char.isalpha():
            raise ValueError("The alphabet must be integers only")
        if char.isdigit() and (not intervalMode):
            if int(char) not in alphabets.keys():
                alphabets[int(char)] = 1
        if char == '[':
            sq_bracket_count+=1
	if char == ']':
	    sq_bracket_count-=1

    alphabets_list = sorted(alphabets.keys())
    global_alphabet_counter = len(alphabets_list)

    if not alphabets_list:
        raise ValueError("The timed regular expression must include at least one alphabet")

    if alphabets_list[0] is not 0:
        raise ValueError("The alphabet must start with 0 and increment by 1.")

    for i in range(1,global_alphabet_counter):
        if alphabets_list[i] - alphabets_list[i-1] > 1:
            raise ValueError("The alphabet must start with 0 and increment by 1.")

	if sq_bracket_count != 0:
	    raise ValueError("Each '[' must have a matching ']'")

    if not (opening_count == closing_count):
        raise ValueError("Each '<' must have a matching '>'")

    return


def embed_actions(exp, counter):
    return exp + ")" + " @CT" + str(counter) + " >~ST" + str(counter)


def create_actions(file, counter):
    '''
        Writes "action ST0 { ST(0) }" to the ragel file with appropriate clock number
    '''
    for x in range(counter):
        create_action_st(file, x)
        create_action_ct(file, x)
    return


def create_action_st(file, counter):
    file.write("    action ST" + str(counter) + " { ST(" + str(counter) + ") }\n" )
    return


def create_action_ct(file, counter):
    file.write("    action CT" + str(counter) + " { CT(" + str(counter) + ") }\n" )
    return

def writeIntervalList(aList, f, lstName):
    i = 0
    while i < len(aList):
        f.write(lstName +".push_back(" + aList[i] + ");\n")
  	i += 1

def write_to_file(input, temprl, headerLoc):
    '''
        Creates a custom automaton.rl ragel file used by the AutomatonR Package

        input: a timed regular expression
    '''
    global global_beginterval_list
    global global_endinterval_list
    f = open(temprl, "w+")
    ragel_expression = parser(input)

    f.write("#include \"" + str(headerLoc) + "\"\n\n")

    f.write("void ParserAutomaton::initIntervals() {\n")
    writeIntervalList(global_beginterval_list, f, "startInterval")
    writeIntervalList(global_endinterval_list, f, "endInterval")
    f.write("}\n")

    f.write("void ParserAutomaton::computeNextState(int *currentState, vector<double> *currentTimes, int *succ, int *reset, const int nextSymbol, const double newTime) {\n")

    f.write("%%{\n")

    f.write("    machine foo;\n\n")
    f.write("    action R { (*reset)++; STATE(foo_start); RT return; }\n")
    f.write("    action U { (*succ)++; }\n")
    f.write("    action STEP { STATE(ftargs); return; }\n\n")

    create_actions(f, global_clock_counter)

    f.write("\n    getkey nextSymbol;\n")
    f.write("    variable p dummy;\n")
    f.write("    write data;\n\n")
    f.write("}%%\n\n")

    f.write("int cs = *currentState, dummy = 0, eof = -1;\n\n")
    #f.write("std::cerr<<cs<<std::endl;")
    f.write("")
    f.write("%%{\n")
    f.write("    main := " + ragel_expression + "\n")
    f.write("    write init nocs;\n")
    f.write("    write exec noend;\n")
    f.write("}%%\n\n")

    f.write("return; \n\n}\n\n")

    f.write("int ParserAutomaton::getStartState() {\n")
    f.write("startState = %%{")
    f.write("    write start;")
    f.write("}%%;\n")
    f.write("return startState;\n")
    f.write("}\n")

    f.write("ParserAutomaton::ParserAutomaton() {\n")
    f.write("   dimCount = " + str(global_alphabet_counter) + ";\n")
    f.write("   clockCount = " + str(global_clock_counter) + ";\n")
    f.write("}\n")

    f.write("// [[Rcpp::export]]\n");
    f.write("Rcpp::XPtr<Automaton> getAutomatonPointer(){\n")
    f.write("Automaton *ptr = new ParserAutomaton();\n")
    f.write("Rcpp::XPtr< Automaton > p(ptr, true);\n")
    f.write("return p;\n")
    f.write("}")

    return
