
#line 1 "test6.rl"
#include "automaton.h"

void Test6::computeNextState(int *currentState, vector<double> *currentTimes, int *succ, int *reset, const int nextSymbol, const double newTime, const NumericVector &startInterval, const NumericVector &endInterval) {
#line 7 "../src/test6.cpp"
static const int foo_start = 1;
static const int foo_first_final = 4;
static const int foo_error = 0;

static const int foo_en_main = 1;


#line 17 "test6.rl"


int cs = *currentState, dummy = 0, eof = -1;


#line 21 "../src/test6.cpp"
	{
	}

#line 25 "../src/test6.cpp"
	{
	switch ( cs )
	{
#line 8 "test6.rl"
	{ STATE(1); return; }
case 1:
#line 32 "../src/test6.cpp"
	if ( ( nextSymbol) == 0 )
		goto st2;
	goto tr0;
tr0:
#line 6 "test6.rl"
	{ (*reset)++; STATE(foo_start); RT return; }
	goto st0;
#line 40 "../src/test6.cpp"
st0:
cs = 0;
	goto _out;
st2:
#line 10 "test6.rl"
	{ ST(0) }
#line 8 "test6.rl"
	{ STATE(2); return; }
	( dummy) += 1;
case 2:
#line 51 "../src/test6.cpp"
	if ( ( nextSymbol) == 1 )
		goto tr2;
	goto tr0;
tr2:
#line 11 "test6.rl"
	{ CT(0) }
	goto st3;
st3:
#line 8 "test6.rl"
	{ STATE(3); return; }
	( dummy) += 1;
case 3:
#line 64 "../src/test6.cpp"
	switch( ( nextSymbol) ) {
		case 1: goto tr2;
		case 2: goto tr3;
	}
	goto tr0;
tr3:
#line 7 "test6.rl"
	{ (*succ)++; }
	goto st4;
st4:
#line 8 "test6.rl"
	{ STATE(4); return; }
	( dummy) += 1;
case 4:
#line 79 "../src/test6.cpp"
	goto tr0;
	}

	if ( ( dummy) == eof )
	{
	switch ( cs ) {
	case 1: 
	case 2: 
	case 3: 
#line 6 "test6.rl"
	{ (*reset)++; STATE(foo_start); RT return; }
	break;
#line 92 "../src/test6.cpp"
	}
	}

	_out: {}
	}

#line 25 "test6.rl"


return; 

}

Test6::Test6() {
   dimCount = 3;
   clockCount = 1;
}
