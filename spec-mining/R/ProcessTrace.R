#' Process timed regex
#'
#' Processes the trace on a given timed regex, returning number of successes and resets
#'
#'
#' @param traceTimes Numeric vector of timestamps.
#' @param traceEvents Integer vector of corresponding events.
#' @param alphabetLength Integer greater than zero indicating number of unique events.
#' @param intervals DataFrame with two columns, start and end,
#'  corresponding to the intervals used in the regular expression.
#' @param automaton Integer id of automaton being used. Should be 0 for parser generated automaton.
#'  Ids greater than 0 are used mainly for testing.
#'
#' @return List of two nd-arrays.
#' Success and Reset are counters values for each alphabet configuration.
processTrace = function(traceTimes, traceEvents, alphabetLength, intervals, automaton=0) {

  result = processTrace_rcpp(traceTimes, traceEvents, alphabetLength, intervals, automaton)

  # Transpose to make indicies more intuitive
  success = aperm(result$success, c(length(dim(result$success)):1))
  reset = aperm(result$reset, c(length(dim(result$reset)):1))

  return (list("success"=success,"reset"=reset))

}
