## ------------------------------------------------------------------------
library(automatonR)
library(Rcpp)
traceTimes = c(0, 2, 3, 5, 7)
traceEvents = c(1, 2, 2, 1, 2)
alphabetLength = 2
startIntervals = c(0, 0)
endIntervals = c(2, 3)
intervals = list("start" = startIntervals, "end" = endIntervals)

# The last parameter here is used for the hard coded automaton: (<0.1> | <1.0>)+
# If using the parser generated automaton, leave parameter blank
result = processTrace(traceTimes, traceEvents, alphabetLength, intervals, "(<0.1> | <1.0>)+")
result

## ------------------------------------------------------------------------
result$success[1,2]

