
#line 1 "automaton.rl"
#include "automaton.h"

void ParserAutomaton::computeNextState(int *currentState, vector<double> *currentTimes, int *succ, int *reset, const int nextSymbol, const double newTime, const NumericVector &startInterval, const NumericVector &endInterval) {
#line 7 "../src/automaton.cpp"
static const int foo_start = 1;
static const int foo_first_final = 2;
static const int foo_error = 0;

static const int foo_en_main = 1;


#line 17 "automaton.rl"


int cs = *currentState, dummy = 0, eof = -1;


#line 21 "automaton.cpp"
	{
	}

#line 25 "automaton.cpp"
	{
	switch ( cs )
	{
#line 10 "automaton.rl"
	{ ST(0) }
#line 8 "automaton.rl"
	{ STATE(1); return; }
case 1:
#line 34 "automaton.cpp"
	if ( ( nextSymbol) == 0 )
		goto tr1;
	goto tr0;
tr0:
#line 6 "automaton.rl"
	{ (*reset)++; STATE(foo_start); RT return; }
	goto st0;
#line 42 "automaton.cpp"
st0:
cs = 0;
	goto _out;
tr1:
#line 11 "automaton.rl"
	{ CT(0) }
#line 7 "automaton.rl"
	{ (*succ)++; }
	goto st2;
st2:
#line 8 "automaton.rl"
	{ STATE(2); return; }
	( dummy) += 1;
case 2:
#line 57 "automaton.cpp"
	if ( ( nextSymbol) == 0 )
		goto tr1;
	goto tr0;
	}

	if ( ( dummy) == eof )
	{
	switch ( cs ) {
	case 1: 
#line 6 "automaton.rl"
	{ (*reset)++; STATE(foo_start); RT return; }
	break;
#line 70 "automaton.cpp"
	}
	}

	_out: {}
	}

#line 25 "automaton.rl"


return; 

}

ParserAutomaton::ParserAutomaton() {
   dimCount = 1;
   clockCount = 1;
}

// [[Rcpp::export]]
Rcpp::XPtr<Automaton> getAutomatonPointer(){
	Automaton *ptr = new ParserAutomaton();
	Rcpp::XPtr< Automaton > p(ptr, true);
	return p;	
}
