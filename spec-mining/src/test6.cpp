
#line 1 "automaton.rl"
#include "automaton.h"

void Test6::computeNextState(int *currentState, vector<double> *currentTimes, int *succ, int *reset, const int nextSymbol, const double newTime, const NumericVector &startInterval, const NumericVector &endInterval) {
#line 7 "../src/automaton.cpp"
static const int foo_start = 1;
static const int foo_first_final = 4;
static const int foo_error = 0;

static const int foo_en_main = 1;


#line 17 "automaton.rl"


int cs = *currentState, dummy = 0, eof = -1;


#line 21 "../src/automaton.cpp"
	{
	}

#line 25 "../src/automaton.cpp"
	{
	switch ( cs )
	{
#line 8 "automaton.rl"
	{ STATE(1); return; }
case 1:
#line 32 "../src/automaton.cpp"
	if ( ( nextSymbol) == 0 )
		goto st2;
	goto tr0;
tr0:
#line 6 "automaton.rl"
	{ (*reset)++; STATE(foo_start); RT return; }
	goto st0;
#line 40 "../src/automaton.cpp"
st0:
cs = 0;
	goto _out;
st2:
#line 10 "automaton.rl"
	{ ST(0) }
#line 8 "automaton.rl"
	{ STATE(2); return; }
	( dummy) += 1;
case 2:
#line 51 "../src/automaton.cpp"
	if ( ( nextSymbol) == 1 )
		goto tr2;
	goto tr0;
tr2:
#line 11 "automaton.rl"
	{ CT(0) }
	goto st3;
st3:
#line 8 "automaton.rl"
	{ STATE(3); return; }
	( dummy) += 1;
case 3:
#line 64 "../src/automaton.cpp"
	switch( ( nextSymbol) ) {
		case 1: goto tr2;
		case 2: goto tr3;
	}
	goto tr0;
tr3:
#line 7 "automaton.rl"
	{ (*succ)++; }
	goto st4;
st4:
#line 8 "automaton.rl"
	{ STATE(4); return; }
	( dummy) += 1;
case 4:
#line 79 "../src/automaton.cpp"
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
#line 92 "../src/automaton.cpp"
	}
	}

	_out: {}
	}

#line 25 "automaton.rl"


return; 

}

Test6::Test6() {
   dimCount = 3;
   clockCount = 1;
}
