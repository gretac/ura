
#line 1 "test4.rl"
#include "automaton.h"

void Test4::computeNextState(int *currentState, vector<double> *currentTimes, int *succ, int *reset, const int nextSymbol, const double newTime, const NumericVector &startInterval, const NumericVector &endInterval) {
#line 7 "../src/test4.cpp"
static const int foo_start = 1;
static const int foo_first_final = 4;
static const int foo_error = 0;

static const int foo_en_main = 1;


#line 19 "test4.rl"


int cs = *currentState, dummy = 0, eof = -1;


#line 21 "../src/test4.cpp"
	{
	}

#line 25 "../src/test4.cpp"
	{
	switch ( cs )
	{
#line 10 "test4.rl"
	{ ST(0) }
#line 12 "test4.rl"
	{ ST(1) }
#line 8 "test4.rl"
	{ STATE(1); return; }
case 1:
#line 36 "../src/test4.cpp"
	switch( ( nextSymbol) ) {
		case 0: goto st2;
		case 1: goto st3;
	}
	goto tr0;
tr0:
#line 6 "test4.rl"
	{ (*reset)++; STATE(foo_start); RT return; }
	goto st0;
#line 46 "../src/test4.cpp"
st0:
cs = 0;
	goto _out;
st2:
#line 8 "test4.rl"
	{ STATE(2); return; }
	( dummy) += 1;
case 2:
#line 55 "../src/test4.cpp"
	if ( ( nextSymbol) == 1 )
		goto tr3;
	goto tr0;
tr3:
#line 11 "test4.rl"
	{ CT(0) }
#line 7 "test4.rl"
	{ (*succ)++; }
	goto st4;
tr4:
#line 13 "test4.rl"
	{ CT(1) }
#line 7 "test4.rl"
	{ (*succ)++; }
	goto st4;
st4:
#line 10 "test4.rl"
	{ ST(0) }
#line 12 "test4.rl"
	{ ST(1) }
#line 8 "test4.rl"
	{ STATE(4); return; }
	( dummy) += 1;
case 4:
#line 80 "../src/test4.cpp"
	switch( ( nextSymbol) ) {
		case 0: goto st2;
		case 1: goto st3;
	}
	goto tr0;
st3:
#line 8 "test4.rl"
	{ STATE(3); return; }
	( dummy) += 1;
case 3:
#line 91 "../src/test4.cpp"
	if ( ( nextSymbol) == 0 )
		goto tr4;
	goto tr0;
	}

	if ( ( dummy) == eof )
	{
	switch ( cs ) {
	case 1: 
	case 2: 
	case 3: 
#line 6 "test4.rl"
	{ (*reset)++; STATE(foo_start); RT return; }
	break;
#line 106 "../src/test4.cpp"
	}
	}

	_out: {}
	}

#line 27 "test4.rl"


return; 

}

Test4::Test4() {
   dimCount = 2;
   clockCount = 2;
}
