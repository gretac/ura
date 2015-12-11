
#line 1 "test1.rl"
#include "automaton.h"

void Test1::computeNextState(int *currentState, vector<double> *currentTimes, int *succ, int *reset, const int nextSymbol, const double newTime, const NumericVector &startInterval, const NumericVector &endInterval) {
#line 7 "../src/test1.cpp"
static const int foo_start = 1;
static const int foo_first_final = 3;
static const int foo_error = 0;

static const int foo_en_main = 1;


#line 17 "test1.rl"


int cs = *currentState, dummy = 0, eof = -1;


#line 21 "../src/test1.cpp"
	{
	}

#line 25 "../src/test1.cpp"
	{
	switch ( cs )
	{
#line 8 "test1.rl"
	{ STATE(1); return; }
case 1:
#line 32 "../src/test1.cpp"
	if ( ( nextSymbol) == 1 )
		goto st2;
	goto tr0;
tr0:
#line 6 "test1.rl"
	{ (*reset)++; STATE(foo_start); RT return; }
	goto st0;
#line 40 "../src/test1.cpp"
st0:
cs = 0;
	goto _out;
st2:
#line 10 "test1.rl"
	{ ST(0) }
#line 8 "test1.rl"
	{ STATE(2); return; }
	( dummy) += 1;
case 2:
#line 51 "../src/test1.cpp"
	if ( ( nextSymbol) == 0 )
		goto tr2;
	goto tr0;
tr2:
#line 11 "test1.rl"
	{ CT(0) }
#line 7 "test1.rl"
	{ (*succ)++; }
	goto st3;
st3:
#line 8 "test1.rl"
	{ STATE(3); return; }
	( dummy) += 1;
case 3:
#line 66 "../src/test1.cpp"
	switch( ( nextSymbol) ) {
		case 0: goto tr2;
		case 1: goto st2;
	}
	goto tr0;
	}

	if ( ( dummy) == eof )
	{
	switch ( cs ) {
	case 1: 
	case 2: 
#line 6 "test1.rl"
	{ (*reset)++; STATE(foo_start); RT return; }
	break;
#line 82 "../src/test1.cpp"
	}
	}

	_out: {}
	}

#line 25 "test1.rl"


return; 

}

Test1::Test1() {
  dimCount = 2;
  clockCount = 1;
}
