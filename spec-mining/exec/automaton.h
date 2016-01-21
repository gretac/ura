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

#define PRINTSUCC std::cerr<<"Incr Succ"<<std::endl;

#define ST(x) (*currentTimes)[x] = newTime;
//Do a automaton reset if an event does not meet the interval timelines
#define CT(x)   if((newTime - (*currentTimes)[x]  > endInterval(x)) || (newTime - (*currentTimes)[x] < startInterval(x))) { \
    (*reset)++;                                                        \
    STATE(foo_start);                                                  \
    (*currentTimes)[x] = newTime;                                                                     \
    return;                                                            \
  }                                                                    \


// Automaton Ids (Ids > 0 are test automatons)
const short int PARSER_AUTOMATON = 0;
const short int TEST1_AUTOMATON = 1;
const short int TEST2_AUTOMATON = 2;
const short int TEST3_AUTOMATON = 3;
const short int TEST4_AUTOMATON = 4;
const short int TEST5_AUTOMATON = 5;
const short int TEST6_AUTOMATON = 6;
const short int TEST7_AUTOMATON = 7;
const short int TEST8_AUTOMATON = 8;
const short int TEST9_AUTOMATON = 9;
const short int TEST10_AUTOMATON = 10;
const short int TEST11_AUTOMATON = 11;
const short int TEST12_AUTOMATON = 12;
const short int TEST13_AUTOMATON = 13;
const short int TEST14_AUTOMATON = 14;
const short int TEST15_AUTOMATON = 15;
// Automaton Super Class
class Automaton {
  public:
    int dimCount;
    int clockCount;
    NumericVector startInterval, endInterval;
    Automaton(){
    }
    virtual void initIntervals() = 0;
    virtual int getStartState() = 0;
    virtual void computeNextState(int *currentState,
                      vector<double> *currentTimes,
                      int *succ, int *reset,
                      const int nextSymbol, const double newTime)=0;
    virtual ~Automaton(){}
};

// Automaton Factory
unique_ptr<Automaton> automatonFactory(const int automaton);

// Parser Automaton
class ParserAutomaton: public Automaton {
public:
  int startState;
  ParserAutomaton();
  void computeNextState(int *currentState,
                      vector<double> *currentTimes,
                      int *succ, int *reset,
                      const int nextSymbol, const double newTime);
  void initIntervals();
  int  getStartState();
  virtual ~ParserAutomaton(){
  }
};

/* Test Automatons
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
class Test6: public Automaton {
public:
  Test6();
  void computeNextState(int *currentState,
                        vector<double> *currentTimes,
                        int *succ, int *reset,
                        const int nextSymbol, const double newTime,
                        const NumericVector &startInterval,
                        const NumericVector &endInterval);
};
class Test7: public Automaton {
public:
  Test7();
  void computeNextState(int *currentState,
                        vector<double> *currentTimes,
                        int *succ, int *reset,
                        const int nextSymbol, const double newTime,
                        const NumericVector &startInterval,
                        const NumericVector &endInterval);
};
class Test8: public Automaton {
public:
  Test8();
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
*/
#endif
