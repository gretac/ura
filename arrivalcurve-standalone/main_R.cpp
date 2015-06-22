#include<Rcpp.h>
using namespace Rcpp;

#include "arrival_curve.c"


int bla(int i) {
  return i+5;
}


Rcpp::List computer_arrival_curve_rwrapper(Rcpp::NumericVector e, float min_window_size, float max_window_size) {
   vector<step> max_vec, min_vec;

   vector<float> ex = Rcpp::as<std::vector<float> >(e);
  
//   computer_arrival_curve(ex, min_window_size, max_window_size, max_vec, min_vec);

   return Rcpp::List::create (
                              Rcpp::Named("max_vec") = max_vec, 
                              Rcpp::Named("min_vec") = min_vec
                              );
 }

RCPP_MODULE(mod) {
  function( "bla",         &bla );
}
