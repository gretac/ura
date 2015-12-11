
#line 1 "test7.rl"
#include "automaton.h"

void Test7::computeNextState(int *currentState, vector<double> *currentTimes, int *succ, int *reset, const int nextSymbol, const double newTime, const NumericVector &startInterval, const NumericVector &endInterval) {
#line 7 "../src/test7.cpp"
static const int foo_start = 1;
static const int foo_first_final = 4;
static const int foo_error = 0;

static const int foo_en_main = 1;


#line 17 "test7.rl"


int cs = *currentState, dummy = 0, eof = -1;


#line 21 "../src/test7.cpp"
	{
	}

#line 25 "../src/test7.cpp"
	{
	switch ( cs )
	{
#line 10 "test7.rl"
	{ ST(0) }
#line 8 "test7.rl"
	{ STATE(1); return; }
case 1:
#line 34 "../src/test7.cpp"
	if ( ( nextSymbol) == 2 )
		goto st2;
	goto tr0;
tr0:
#line 6 "test7.rl"
	{ (*reset)++; STATE(foo_start); RT return; }
	goto st0;
#line 42 "../src/test7.cpp"
st0:
cs = 0;
	goto _out;
st2:
#line 8 "test7.rl"
	{ STATE(2); return; }
	( dummy) += 1;
case 2:
#line 51 "../src/test7.cpp"
	if ( ( nextSymbol) == 1 )
		goto st3;
	goto tr0;
st3:
#line 8 "test7.rl"
	{ STATE(3); return; }
	( dummy) += 1;
case 3:
#line 60 "../src/test7.cpp"
	switch( ( nextSymbol) ) {
		case 0: goto tr3;
		case 1: goto st3;
	}
	goto tr0;
tr3:
#line 11 "test7.rl"
	{ CT(0) }
#line 7 "test7.rl"
	{ (*succ)++; }
	goto st4;
st4:
#line 10 "test7.rl"
	{ ST(0) }
#line 8 "test7.rl"
	{ STATE(4); return; }
	( dummy) += 1;
case 4:
#line 79 "../src/test7.cpp"
	if ( ( nextSymbol) == 2 )
		goto st2;
	goto tr0;
	}

	if ( ( dummy) == eof )
	{
	switch ( cs ) {
	case 1: 
	case 2: 
	case 3: 
#line 6 "test7.rl"
	{ (*reset)++; STATE(foo_start); RT return; }
	break;
#line 94 "../src/test7.cpp"
	}
	}

	_out: {}
	}

#line 25 "test7.rl"


return; 

}

Test7::Test7() {
   dimCount = 3;
   clockCount = 1;
}
