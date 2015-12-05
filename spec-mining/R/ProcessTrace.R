require(Rcpp)
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
#' @param automatonStr the timed-regular expression template
#'
#' @return List of two nd-arrays.
#' Success and Reset are counters values for each alphabet configuration.
processTrace = function(traceTimes, traceEvents, alphabetLength, intervals, automatonStr) {

  trlfile<-paste("\"",tempfile("automaton",fileext = ".rl"),"\"", sep = "")
  tcppfile<-tempfile("automaton",fileext = ".cpp")
  tregex<-paste("\"",automatonStr,"\"",sep = "")

  headerLoc<-paste(find.package("automatonR"),"/exec/automaton.h",sep = "")
  pyscript<-paste(find.package("automatonR"), "/exec/parse.py",sep = "")
  try(system(paste("python",pyscript, tregex, trlfile,tcppfile, headerLoc), ignore.stdout = TRUE))
  sourceCpp(tcppfile)
  automatonPtr<-getAutomatonPointer()

  result = processTrace_rcpp(traceTimes, traceEvents, alphabetLength, intervals, automatonPtr)

  # Transpose to make indicies more intuitive
  success = aperm(result$success, c(length(dim(result$success)):1))
  reset = aperm(result$reset, c(length(dim(result$reset)):1))
  unlink(trlfile)
  unlink(tcppfile)
  return (list("success"=success,"reset"=reset))

}
