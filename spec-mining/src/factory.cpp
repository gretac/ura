#include "automaton.h"

unique_ptr<Automaton> automatonFactory(const int automaton) {

  switch(automaton) {

  case PARSER_AUTOMATON: {
    return unique_ptr<Automaton>(new ParserAutomaton);
  }

  case TEST1_AUTOMATON: {
    return unique_ptr<Automaton>(new Test1);
  }

  case TEST2_AUTOMATON: {
    return unique_ptr<Automaton>(new Test2);
  }

  case TEST3_AUTOMATON: {
    return unique_ptr<Automaton>(new Test3);
  }

  case TEST4_AUTOMATON: {
    return unique_ptr<Automaton>(new Test4);
  }

  // error in case of undefined automaton
  default:
    stop("Unsupported automaton");
    return unique_ptr<Automaton>();
  }
}
