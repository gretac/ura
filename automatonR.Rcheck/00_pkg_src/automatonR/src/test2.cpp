
#line 1 "test2.rl"
#include "automaton.h"

void Test2::computeNextState(int *currentState, vector<double> *currentTimes, int *succ, int *reset, const int nextSymbol, const double newTime, const NumericVector &startInterval, const NumericVector &endInterval) {
#line 7 "../src/test2.cpp"
static const int foo_start = 1;
static const int foo_first_final = 2;
static const int foo_error = 0;

static const int foo_en_main = 1;


#line 17 "test2.rl"


int cs = *currentState, dummy = 0, eof = -1;


#line 21 "../src/test2.cpp"
	{
	}

#line 25 "../src/test2.cpp"
	{
	switch ( cs )
	{
#line 10 "test2.rl"
	{ ST(0) }
#line 8 "test2.rl"
	{ STATE(1); return; }
case 1:
#line 34 "../src/test2.cpp"
	if ( ( nextSymbol) == 0 )
		goto tr1;
	goto tr0;
tr0:
#line 6 "test2.rl"
	{ (*reset)++; STATE(foo_start); RT return; }
	goto st0;
#line 42 "../src/test2.cpp"
st0:
cs = 0;
	goto _out;
tr1:
#line 11 "test2.rl"
	{ CT(0) }
#line 7 "test2.rl"
	{ (*succ)++; }
	goto st2;
st2:
#line 10 "test2.rl"
	{ ST(0) }
#line 8 "test2.rl"
	{ STATE(2); return; }
	( dummy) += 1;
case 2:
#line 59 "../src/test2.cpp"
	if ( ( nextSymbol) == 0 )
		goto tr1;
	goto tr0;
	}

	if ( ( dummy) == eof )
	{
	switch ( cs ) {
	case 1: 
#line 6 "test2.rl"
	{ (*reset)++; STATE(foo_start); RT return; }
	break;
#line 72 "../src/test2.cpp"
	}
	}

	_out: {}
	}

#line 25 "test2.rl"


return; 

}

Test2::Test2() {
  dimCount = 1;
  clockCount = 1;
}
