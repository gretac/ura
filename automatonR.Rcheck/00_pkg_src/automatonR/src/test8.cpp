
#line 1 "test8.rl"
#include "automaton.h"

void Test8::computeNextState(int *currentState, vector<double> *currentTimes, int *succ, int *reset, const int nextSymbol, const double newTime, const NumericVector &startInterval, const NumericVector &endInterval) {
#line 7 "../src/test8.cpp"
static const int foo_start = 1;
static const int foo_first_final = 5;
static const int foo_error = 0;

static const int foo_en_main = 1;


#line 17 "test8.rl"


int cs = *currentState, dummy = 0, eof = -1;


#line 21 "../src/test8.cpp"
	{
	}

#line 25 "../src/test8.cpp"
	{
	switch ( cs )
	{
#line 10 "test8.rl"
	{ ST(0) }
#line 8 "test8.rl"
	{ STATE(1); return; }
case 1:
#line 34 "../src/test8.cpp"
	if ( ( nextSymbol) == 0 )
		goto st2;
	goto tr0;
tr0:
#line 6 "test8.rl"
	{ (*reset)++; STATE(foo_start); RT return; }
	goto st0;
#line 42 "../src/test8.cpp"
st0:
cs = 0;
	goto _out;
st2:
#line 8 "test8.rl"
	{ STATE(2); return; }
	( dummy) += 1;
case 2:
#line 51 "../src/test8.cpp"
	if ( ( nextSymbol) == 1 )
		goto st3;
	goto tr0;
st3:
#line 8 "test8.rl"
	{ STATE(3); return; }
	( dummy) += 1;
case 3:
#line 60 "../src/test8.cpp"
	if ( ( nextSymbol) == 2 )
		goto st4;
	goto tr0;
st4:
#line 8 "test8.rl"
	{ STATE(4); return; }
	( dummy) += 1;
case 4:
#line 69 "../src/test8.cpp"
	if ( ( nextSymbol) == 3 )
		goto tr4;
	goto tr0;
tr4:
#line 11 "test8.rl"
	{ CT(0) }
#line 7 "test8.rl"
	{ (*succ)++; }
	goto st5;
st5:
#line 8 "test8.rl"
	{ STATE(5); return; }
	( dummy) += 1;
case 5:
#line 84 "../src/test8.cpp"
	goto tr0;
	}

	if ( ( dummy) == eof )
	{
	switch ( cs ) {
	case 1: 
	case 2: 
	case 3: 
	case 4: 
#line 6 "test8.rl"
	{ (*reset)++; STATE(foo_start); RT return; }
	break;
#line 98 "../src/test8.cpp"
	}
	}

	_out: {}
	}

#line 25 "test8.rl"


return; 

}

Test8::Test8() {
   dimCount = 4;
   clockCount = 1;
}
