import ragel_parser
import os
import sys

#input = raw_input("Timed Regular Expression: ")
#print sys.argv[1]
ragel_parser.write_to_file(sys.argv[1], sys.argv[2], sys.argv[4])
#os.system("ragel -G2 automaton.rl -o ../src/automaton.cpp")
cmdString = "ragel -G2 " + sys.argv[2].decode('string_escape') + " -o " + sys.argv[3].decode('string_escape')
#print cmdString
os.system(cmdString)
