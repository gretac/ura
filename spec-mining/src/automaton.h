// [[Rcpp::plugins(cpp11)]]
#ifndef AUTOMATON_H
#define AUTOMATON_H

#include <vector>
#include <string>
#include <memory>
#include <Rcpp.h>
#include <stdio.h>
#include <cmath>

using namespace Rcpp;
using namespace std;



// Macros for computeNextState
#define STATE(x)  *currentState = x;
#define AERROR     stop("Unsupported symbol");

#define RT   for (int i = 0; i < (*currentTimes).size(); i++) { \
  (*currentTimes)[i] = newTime;                                  \
}                                                               \

#define ST(x) (*currentTimes)[x] = newTime;
#define CT(x)   if((newTime - (*currentTimes)[x]  > endInterval(x)) || (newTime - (*currentTimes)[x] < startInterval(x))) { \
    (*reset)++;                                                        \
    STATE(foo_start);                                                  \
    RT                                                                 \
    return;                                                            \
  }                                                                    \


// Automaton Ids (Ids > 0 are test automatons)
const short int PARSER_AUTOMATON = 0;
const short int TEST1_AUTOMATON = 1;
const short int TEST2_AUTOMATON = 2;
const short int TEST3_AUTOMATON = 3;
const short int TEST4_AUTOMATON = 4;
const short int TEST5_AUTOMATON = 5;
// Automaton Super Class
class Automaton {
  public:
    int dimCount;
    int clockCount;
    virtual void computeNextState(int *currentState,
                      vector<double> *currentTimes,
                      int *succ, int *reset,
                      const int nextSymbol, const double newTime,
                      const NumericVector &startInterval,
                      const NumericVector &endInterval)=0;
};

// Automaton Factory
unique_ptr<Automaton> automatonFactory(const int automaton);

// Parser Automaton
class ParserAutomaton: public Automaton {
public:
  ParserAutomaton();
  void computeNextState(int *currentState,
                      vector<double> *currentTimes,
                      int *succ, int *reset,
                      const int nextSymbol, const double newTime,
                      const NumericVector &startInterval,
                      const NumericVector &endInterval);
};

// Test Automatons
class Test1: public Automaton {
public:
  Test1();
  void computeNextState(int *currentState,
                      vector<double> *currentTimes,
                      int *succ, int *reset,
                      const int nextSymbol, const double newTime,
                      const NumericVector &startInterval,
                      const NumericVector &endInterval);
};

class Test2: public Automaton {
public:
  Test2();
  void computeNextState(int *currentState,
                        vector<double> *currentTimes,
                        int *succ, int *reset,
                        const int nextSymbol, const double newTime,
                        const NumericVector &startInterval,
                        const NumericVector &endInterval);
};

class Test3: public Automaton {
public:
  Test3();
  void computeNextState(int *currentState,
                        vector<double> *currentTimes,
                        int *succ, int *reset,
                        const int nextSymbol, const double newTime,
                        const NumericVector &startInterval,
                        const NumericVector &endInterval);
};

class Test4: public Automaton {
public:
  Test4();
  void computeNextState(int *currentState,
                        vector<double> *currentTimes,
                        int *succ, int *reset,
                        const int nextSymbol, const double newTime,
                        const NumericVector &startInterval,
                        const NumericVector &endInterval);
};

class Test5: public Automaton {
public:
  Test5();
  void computeNextState(int *currentState,
                        vector<double> *currentTimes,
                        int *succ, int *reset,
                        const int nextSymbol, const double newTime,
                        const NumericVector &startInterval,
                        const NumericVector &endInterval);
};
// Helpers
bool anyEqual(vector<int> v);
void incrementPermCounter(vector<int>* counter, int base);

// Process Trace Functions
List processTrace_rcpp(const NumericVector traceTimes,
                  const IntegerVector traceEvents,
                  const int alphabetLength,
                  const IntegerVector intervals,
                  const int automaton);

#endif

