#include "automaton.h"

bool anyEqual(vector<int> v){

  sort(v.begin(), v.end());
  for (int x=0; x < v.size() - 1; x++){
    if (v[x] == v[x+1]){
      return true;
    }
  }

  return false;
}

void incrementPermCounter(vector<int>* counter, int base){

  int digit = counter->size() - 1;
  (*counter)[digit]++;
  while ((*counter)[digit] >= base && digit > 0){
    (*counter)[digit] = (*counter)[digit] - base;
    (*counter)[--digit]++;
  }

}


// [[Rcpp::export]]
List processTrace_rcpp(const NumericVector traceTimes,
                  const IntegerVector traceEvents,
                  const int alphabetLength,
                  const List intervals,
                  const int automaton) {

    // Instantiate Correct Automaton
  unique_ptr<Automaton> a = automatonFactory(automaton);
  int dimCount = a->dimCount;
  int clockCount = a->clockCount;

  // Unpack Time Intervals
  NumericVector startInterval = intervals["start"];
  NumericVector endInterval = intervals["end"];

  // Input Checking
  if (traceTimes.length() != traceEvents.length()) {
    stop("tracesTimes length not equal to traceEvents length");
  }
  if (startInterval.length() != endInterval.length()) {
    stop("number of start intervals not equal to number of end intervals");
  }
  if (startInterval.length() != clockCount) {
    stop("Number of supplied time intervals does not match number of clocks");
  }
  if (alphabetLength < dimCount) {
    stop("alphabetLength is less than number of dimensions in automaton");
  }


  int permCount = (int) pow(alphabetLength, dimCount);

  // Initialize state storage
  IntegerVector symbols(permCount);
  fill(symbols.begin(), symbols.end(), 1);

  // Initialize time storage
  vector< vector<double> > times(permCount, vector<double>(startInterval.length(), 0.0));

  // Initialize success and reset counters
  IntegerVector succ(permCount);
  IntegerVector reset(permCount);

  // Initialize map
  // Pair is perm, alpha placement
  vector<vector<pair<int, int> > > permMap (alphabetLength);

  // Fill map
  vector<int> perm (dimCount, 0);
  for (int i=0; i < permCount; i++) {

    if (anyEqual(perm)) {
      symbols(i) = NA_INTEGER;
      succ(i) = NA_INTEGER;
      reset(i) = NA_INTEGER;
    } else {
      for (int x=0; x < dimCount; x++) {
        permMap[perm[x]].push_back(make_pair(i, x));
      }
    }

    incrementPermCounter(&perm, alphabetLength);
  }


  int iLoc;
  double iTime;

  for(int i=0; i< traceTimes.length(); i++) {

    // Since trace alphabet seems to start from 1 instead of 0
    iLoc = traceEvents(i) - 1;
    iTime= traceTimes(i);

    for(int x=0; x < permMap[iLoc].size(); x++) {

      a->computeNextState(&(symbols(permMap[iLoc][x].first)),
                       &(times[permMap[iLoc][x].first]),
                       &(succ(permMap[iLoc][x].first)),
                       &(reset(permMap[iLoc][x].first)),
                       permMap[iLoc][x].second, iTime,
                       startInterval, endInterval);
    }

  }

  IntegerVector dims(dimCount, alphabetLength);
  succ.attr("dim") = dims;
  reset.attr("dim") = dims;

  return List::create(Rcpp::Named("success") = succ,
                      Rcpp::Named("reset")   = reset);
}
