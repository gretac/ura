#include "automaton.h"

void ParserAutomaton::computeNextState(int *currentState, vector<double> *currentTimes, int *succ, int *reset, const int nextSymbol, const double newTime, const NumericVector &startInterval, const NumericVector &endInterval) {%%{
    machine foo;

    action R { (*reset)++; STATE(foo_start); RT return; }
    action U { (*succ)++; }
    action STEP { STATE(ftargs); return; }

    action ST0 { ST(0) }
    action CT0 { CT(0) }

    getkey nextSymbol;
    variable p dummy;
    write data;

}%%

int cs = *currentState, dummy = 0, eof = -1;

%%{
    main := ((0+) @CT0 >~ST0) @U $~STEP $lerr(	R);
    write init nocs;
    write exec noend;
}%%

return; 

}

ParserAutomaton::ParserAutomaton() {
   dimCount = 1;
   clockCount = 1;
}