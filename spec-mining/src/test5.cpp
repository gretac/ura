
#line 1 "automaton.rl"
#include "automaton.h"

void ParserAutomaton::computeNextState(int *currentState, vector<double> *currentTimes, int *succ, int *reset, const int nextSymbol, const double newTime, const NumericVector &startInterval, const NumericVector &endInterval) {
#line 7 "../src/automaton.cpp"
static const int foo_start = 1;
static const int foo_first_final = 4;
static const int foo_error = 0;

static const int foo_en_main = 1;


#line 21 "automaton.rl"


int cs = *currentState, dummy = 0, eof = -1;


#line 21 "../src/automaton.cpp"
	{
	}

#line 25 "../src/automaton.cpp"
	{
	switch ( cs )
	{
#line 10 "automaton.rl"
	{ ST(0) }
#line 8 "automaton.rl"
	{ STATE(1); return; }
case 1:
#line 34 "../src/automaton.cpp"
	if ( ( nextSymbol) == 0 )
		goto tr1;
	goto tr0;
tr0:
#line 6 "automaton.rl"
	{ (*reset)++; STATE(foo_start); RT return; }
	goto st0;
#line 42 "../src/automaton.cpp"
st0:
cs = 0;
	goto _out;
tr1:
#line 11 "automaton.rl"
	{ CT(0) }
	goto st2;
st2:
#line 12 "automaton.rl"
	{ ST(1) }
#line 8 "automaton.rl"
	{ STATE(2); return; }
	( dummy) += 1;
case 2:
#line 57 "../src/automaton.cpp"
	switch( ( nextSymbol) ) {
		case 0: goto tr1;
		case 1: goto tr2;
	}
	goto tr0;
tr2:
#line 13 "automaton.rl"
	{ CT(1) }
	goto st3;
st3:
#line 14 "automaton.rl"
	{ ST(2) }
#line 8 "automaton.rl"
	{ STATE(3); return; }
	( dummy) += 1;
case 3:
#line 74 "../src/automaton.cpp"
	switch( ( nextSymbol) ) {
		case 1: goto tr2;
		case 2: goto tr3;
	}
	goto tr0;
tr3:
#line 15 "automaton.rl"
	{ CT(2) }
#line 7 "automaton.rl"
	{ (*succ)++; }
	goto st4;
st4:
#line 8 "automaton.rl"
	{ STATE(4); return; }
	( dummy) += 1;
case 4:
#line 91 "../src/automaton.cpp"
	if ( ( nextSymbol) == 2 )
		goto tr3;
	goto tr0;
	}

	if ( ( dummy) == eof )
	{
	switch ( cs ) {
	case 1: 
	case 2: 
	case 3: 
#line 6 "automaton.rl"
	{ (*reset)++; STATE(foo_start); RT return; }
	break;
#line 106 "../src/automaton.cpp"
	}
	}

	_out: {}
	}

#line 29 "automaton.rl"


return; 

}

ParserAutomaton::ParserAutomaton() {
   dimCount = 3;
   clockCount = 3;
}