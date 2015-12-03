
#line 1 "test5.rl"
#include "automaton.h"

void Test5::computeNextState(int *currentState, vector<double> *currentTimes, int *succ, int *reset, const int nextSymbol, const double newTime, const NumericVector &startInterval, const NumericVector &endInterval) {
#line 7 "../src/test5.cpp"
static const int foo_start = 1;
static const int foo_first_final = 4;
static const int foo_error = 0;

static const int foo_en_main = 1;


#line 21 "test5.rl"


int cs = *currentState, dummy = 0, eof = -1;


#line 21 "../src/test5.cpp"
	{
	}

#line 25 "../src/test5.cpp"
	{
	switch ( cs )
	{
#line 10 "test5.rl"
	{ ST(0) }
#line 8 "test5.rl"
	{ STATE(1); return; }
case 1:
#line 34 "../src/test5.cpp"
	if ( ( nextSymbol) == 0 )
		goto tr1;
	goto tr0;
tr0:
#line 6 "test5.rl"
	{ (*reset)++; STATE(foo_start); RT return; }
	goto st0;
#line 42 "../src/test5.cpp"
st0:
cs = 0;
	goto _out;
tr1:
#line 11 "test5.rl"
	{ CT(0) }
	goto st2;
st2:
#line 12 "test5.rl"
	{ ST(1) }
#line 8 "test5.rl"
	{ STATE(2); return; }
	( dummy) += 1;
case 2:
#line 57 "../src/test5.cpp"
	switch( ( nextSymbol) ) {
		case 0: goto tr1;
		case 1: goto tr2;
	}
	goto tr0;
tr2:
#line 13 "test5.rl"
	{ CT(1) }
	goto st3;
st3:
#line 14 "test5.rl"
	{ ST(2) }
#line 8 "test5.rl"
	{ STATE(3); return; }
	( dummy) += 1;
case 3:
#line 74 "../src/test5.cpp"
	switch( ( nextSymbol) ) {
		case 1: goto tr2;
		case 2: goto tr3;
	}
	goto tr0;
tr3:
#line 15 "test5.rl"
	{ CT(2) }
#line 7 "test5.rl"
	{ (*succ)++; }
	goto st4;
st4:
#line 8 "test5.rl"
	{ STATE(4); return; }
	( dummy) += 1;
case 4:
#line 91 "../src/test5.cpp"
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
#line 6 "test5.rl"
	{ (*reset)++; STATE(foo_start); RT return; }
	break;
#line 106 "../src/test5.cpp"
	}
	}

	_out: {}
	}

#line 29 "test5.rl"


return; 

}

Test5::Test5() {
   dimCount = 3;
   clockCount = 3;
}
