
#line 1 "test3.rl"
#include "automaton.h"

void Test3::computeNextState(int *currentState, vector<double> *currentTimes, int *succ, int *reset, const int nextSymbol, const double newTime, const NumericVector &startInterval, const NumericVector &endInterval) {
#line 7 "../src/test3.cpp"
static const int foo_start = 1;
static const int foo_first_final = 4;
static const int foo_error = 0;

static const int foo_en_main = 1;


#line 19 "test3.rl"


int cs = *currentState, dummy = 0, eof = -1;


#line 21 "../src/test3.cpp"
	{
	}

#line 25 "../src/test3.cpp"
	{
	switch ( cs )
	{
#line 10 "test3.rl"
	{ ST(0) }
#line 8 "test3.rl"
	{ STATE(1); return; }
case 1:
#line 34 "../src/test3.cpp"
	if ( ( nextSymbol) == 0 )
		goto st2;
	goto tr0;
tr0:
#line 6 "test3.rl"
	{ (*reset)++; STATE(foo_start); RT return; }
	goto st0;
#line 42 "../src/test3.cpp"
st0:
cs = 0;
	goto _out;
st2:
#line 12 "test3.rl"
	{ ST(1) }
#line 8 "test3.rl"
	{ STATE(2); return; }
	( dummy) += 1;
case 2:
#line 53 "../src/test3.cpp"
	if ( ( nextSymbol) == 1 )
		goto st3;
	goto tr0;
st3:
#line 8 "test3.rl"
	{ STATE(3); return; }
	( dummy) += 1;
case 3:
#line 62 "../src/test3.cpp"
	if ( ( nextSymbol) == 2 )
		goto tr3;
	goto tr0;
tr3:
#line 13 "test3.rl"
	{ CT(1) }
#line 11 "test3.rl"
	{ CT(0) }
#line 7 "test3.rl"
	{ (*succ)++; }
	goto st4;
st4:
#line 12 "test3.rl"
	{ ST(1) }
#line 8 "test3.rl"
	{ STATE(4); return; }
	( dummy) += 1;
case 4:
#line 81 "../src/test3.cpp"
	if ( ( nextSymbol) == 1 )
		goto st3;
	goto tr0;
	}

	if ( ( dummy) == eof )
	{
	switch ( cs ) {
	case 1: 
	case 2: 
	case 3: 
#line 6 "test3.rl"
	{ (*reset)++; STATE(foo_start); RT return; }
	break;
#line 96 "../src/test3.cpp"
	}
	}

	_out: {}
	}

#line 27 "test3.rl"


return; 

}

Test3::Test3() {
   dimCount = 3;
   clockCount = 2;
}
