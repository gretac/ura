#include "automaton.h"
#include <fstream>
//#include <iostream>

bool anyEqual(vector<int> v){

  sort(v.begin(), v.end());
  for (int x=0; x < v.size() - 1; x++){
    if (v[x] == v[x+1]){
      return true;
    }
  }

  return false;
}

/*The below function generates next permutation for a given timed regex
  using the given possible elements of alphabets and dimension of the
  timed automaton.

  Arguments:
  counter: Pointer to a vector, which maintains possible values for different
  dimensions of a timed automaton
  base: The number of elements in a alphabet set */

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
                  SEXP automaton) {

    // Instantiate Correct Automaton
  Rcpp::XPtr< Automaton > a(automaton);
  a->initIntervals();
  //unique_ptr<Automaton> a = automatonFactory(automaton);

  int dimCount = a->dimCount;
  int clockCount = a->clockCount;

  // Input Checking
  if (traceTimes.length() != traceEvents.length()) {
      stop("tracesTimes length not equal to traceEvents length");
  }

  if(clockCount != 0){

    if (a->startInterval.length() != a->endInterval.length()) {
      stop("number of start intervals not equal to number of end intervals");
    }
    if (a->startInterval.length() != clockCount) {
      stop("Number of supplied time intervals does not match number of clocks");
    }
    if((a->startInterval)[0]== -1 || (a->endInterval)[0] == -1){
      stop("Number of supplied time intervals does not match number of clocks");
    }

  }
  if (alphabetLength < dimCount) {
    stop("alphabetLength is less than number of dimensions in automaton");
  }

  //Total possible permutations =  alphabetlength P dimcount
  int permCount = (int) pow(alphabetLength, dimCount);



  // Initialize state storage
  IntegerVector symbols(permCount);
  fill(symbols.begin(), symbols.end(), a->getStartState());

  // Initialize time storage
  vector< vector<double> > times(permCount, vector<double>(a->startInterval.length(), 0.0));

  // Initialize success and reset counters
  IntegerVector succ(permCount);
  IntegerVector reset(permCount);
  fill(succ.begin(), succ.end(), 0);
  fill(reset.begin(), reset.end(), 0);

  // Initialize map
  // Pair is perm, alpha placement
  vector<vector<pair<int, int> > > permMap (alphabetLength);
  #ifdef DEBUG
    ofstream debugFile;
    debugFile.open("debugOut.txt");
  #endif
  // Fill map
  vector<int> perm (dimCount, 0);
  for (int i=0; i < permCount; i++) {

    if (anyEqual(perm)) {
      /* We should not process permutations where the values of
         distinct dimensions of timed automata match with each other
      */
      symbols(i) = NA_INTEGER;
      succ(i) = NA_INTEGER;
      reset(i) = NA_INTEGER;
    } else {

//       #ifdef DEBUG
//         for (int x=0; x < dimCount; x++) {
//           std::cout<<perm[x]<<" ";
//         }
//         std::cout<<std::endl;
//       #endif
      for (int x=0; x < dimCount; x++) {
        permMap[perm[x]].push_back(make_pair(i, x));
        /*#ifdef DEBUG
          std::cout<<x<<"="<<perm[x] << ":"<<i<<" "<<std::endl;
        #endif*/
      }
    }

    incrementPermCounter(&perm, alphabetLength);
  }


  int iLoc;
  double iTime;

  for(int i=0; i< traceTimes.length(); i++) {

    // Since trace alphabet seems to start from 1 instead of 0
    iLoc = traceEvents(i) - 1;
    // iLoc is the current event

    iTime= traceTimes(i);

//     if(iLoc < alphabetLength){
//       for(int x=0; x < permMap[iLoc].size(); x++) {
//
//         //Update automata states and 'success/reset' counters
//         //for permutations which contain event marked with `iloc'
//           a->computeNextState(&(symbols(permMap[iLoc][x].first)),
//                            &(times[permMap[iLoc][x].first]),
//                            &(succ(permMap[iLoc][x].first)),
//                            &(reset(permMap[iLoc][x].first)),
//                            permMap[iLoc][x].second, iTime);
// #ifdef DEBUG
//   std::cerr<<permMap[iLoc][x].first<<",succ="
//            <<succ(permMap[iLoc][x].first)<<",reset="
//            <<reset(permMap[iLoc][x].first)<<",dimension="
//            <<permMap[iLoc][x].second << ",event="
//            <<iLoc+1<< std::endl;
// #endif
//       }
// #ifdef DEBUG
//   std::cerr<<"*************************"<< std::endl;
// #endif
//     }else
    for(int i = 0; i < permMap.size(); i++){
      for(int j = 0 ; j < permMap.at(i).size(); j++){
        if(i == iLoc){
          a->computeNextState(&(symbols(permMap[i][j].first)),
                              &(times[permMap[i][j].first]),
                              &(succ(permMap[i][j].first)),
                              &(reset(permMap[i][j].first)),
                              permMap[i][j].second, iTime);
          #ifdef DEBUG
            debugFile<<permMap[i][j].first<<",succ="
                     <<succ(permMap[i][j].first)<<",reset="
                     <<reset(permMap[i][j].first)<<",dimension="
                     <<permMap[i][j].second<< ",event*="
                     <<iLoc+1 << std::endl;
            debugFile<<"*************************"<< std::endl;
          #endif
        }else{
            a->computeNextState(&(symbols(permMap[i][j].first)),
                                &(times[permMap[i][j].first]),
                                &(succ(permMap[i][j].first)),
                                &(reset(permMap[i][j].first)),
                                dimCount, iTime);
            #ifdef DEBUG
                debugFile<<permMap[i][j].first<<",succ="
                         <<succ(permMap[i][j].first)<<",reset="
                         <<reset(permMap[i][j].first)<<",dimension="
                         <<dimCount<< ",event="
                         <<iLoc+1 << std::endl;
                debugFile<<"*************************"<< std::endl;
            #endif
        }
      }
    }
    #ifdef DEBUG
      debugFile<<"++++++++++++++++++++++++++"<< std::endl;
      debugFile<<"                          "<< std::endl;
    #endif
  }
  #ifdef DEBUG
    debugFile.close();
  #endif
  IntegerVector dims(dimCount, alphabetLength);
  succ.attr("dim") = dims;
  reset.attr("dim") = dims;

  return List::create(Rcpp::Named("success") = succ,
                      Rcpp::Named("reset")   = reset);
}
