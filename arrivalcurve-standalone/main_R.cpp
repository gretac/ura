#include<Rcpp.h>

#include "arrival_curve.h"

using namespace std;

// [[Rcpp::export]]
Rcpp::List computer_arrival_curve_rwrapper(Rcpp::NumericVector e, float max_event, float min_window_size, float max_window_size, float res) {

   vector<float> ex = Rcpp::as<std::vector<float> >(e);

   vector<float> max_events, max_left, max_right, min_events, min_left, min_right;

   float count = compute_arrival_curve(ex, min_window_size, max_window_size, res, max_event, max_events, max_left, max_right, min_events, min_left, min_right);

   return Rcpp::List::create (
                              Rcpp::Named("max_events") = max_events,
                              Rcpp::Named("max_left")   = max_left,
                              Rcpp::Named("max_right")  = max_right,

                              Rcpp::Named("min_events") = min_events,
                              Rcpp::Named("min_left")   = min_left,
                              Rcpp::Named("min_right")  = min_right,
                              Rcpp::Named("count")      = count
                              );
}
