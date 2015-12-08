Sys.setenv("R_TESTS" = "")
library(testthat)
library(Rcpp)
library(automatonR)

test_check("automatonR")
