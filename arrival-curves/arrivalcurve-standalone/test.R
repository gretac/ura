library("Rcpp")

sourceCpp("main_R.cpp")

computer_arrival_curve_rwrapper(1:100, 100, 1, 4)
