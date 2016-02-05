require(Rcpp)

#' Create Automaton from timed-regex
#'
#'
#' @param create Timed-automaton from timed-regular expressions
#' @return Nothing

createTimedAutomaton = function(timedRegEx) {
  trlfile<-paste("\"",tempfile("automaton",fileext = ".rl"),"\"", sep = "")
  tcppfile<-tempfile("automaton",fileext = ".cpp")
  tregex<-paste("\"",timedRegEx,"\"",sep = "")

  # Generate the timed automaton for the timed regular expression
  headerLoc<-paste(find.package("automatonR"),"/exec/automaton.h",sep = "")
  pyscript<-paste(find.package("automatonR"), "/exec/parse.py",sep = "")
  try(system(paste("python",pyscript, tregex, trlfile,tcppfile, headerLoc), ignore.stdout = FALSE))

  cat(trlfile,tcppfile,sep = ",")
}
#' Process timed regex
#'
#' Processes the trace on a given timed regex, returning number of successes and resets
#'
#'
#' @param traceTimes Numeric vector of timestamps.
#' @param traceEvents Integer vector of corresponding events.
#' @param alphabetLength Integer greater than zero indicating number of unique events.
#' @param timedRegEx the timed-regular expression template
#' @return a List
#' Success and Reset are counters values for each alphabet configuration.
processTrace = function(traceTimes, traceEvents, alphabetLength, timedRegEx, TREClass = 1) {
  options("scipen" = 12)
  trlfile<-paste("\"",tempfile("automaton",fileext = ".rl"),"\"", sep = "")
  tcppfile<-tempfile("automaton",fileext = ".cpp")
  tregex<-paste("\"",timedRegEx,"\"",sep = "")

  # Generate the timed automaton for the timed regular expression
  headerLoc<-paste(find.package("automatonR"),"/exec/automaton.h",sep = "")
  pyscript<-paste(find.package("automatonR"), "/exec/parse.py",sep = "")
  try(system(paste("python",pyscript, tregex, trlfile,tcppfile, headerLoc), ignore.stdout = FALSE))

#   if(is.null(intervals$start)){
#     intervals["start"] = c(-1)
#   }
#   if(is.null(intervals$end)){
#     intervals["end"] = c(-1)
#   }
  # Compile the cpp code for the generated automaton
  sourceCpp(tcppfile)

  # Extract the automaton
  automatonPtr<-getAutomatonPointer()

  result = processTrace_rcpp(traceTimes, traceEvents, alphabetLength, automatonPtr,TREClass)

  # Transpose to make indicies more intuitive
  success = aperm(result$success, c(length(dim(result$success)):1))
  reset = aperm(result$reset, c(length(dim(result$reset)):1))
  unlink(trlfile)
  unlink(tcppfile)
  return (list("success"=success,"reset"=reset, "time" = result$time))

}
#' Find a set of sequences of traceEvents which match the given timed regular expression
#' and the required probability threshold
#'
#' @param a List returned by processTrace
#' @param threshold probability to select mined timed-regular expressions
#' @return List whose elements represent mined events

getMinedSpecifications = function(resultList, confidence = 0.9, support = 1) {
  resultList$success = apply(resultList$success, 1:2, function(v) if(!is.na(v) && v >= support){return(v)} else{ return(0)})
  prob = resultList$success / ( resultList$success + resultList$reset)
  prob[is.nan(prob)] <- 0
  prob[is.na(prob)] <- 0
  probBool = apply(prob, 1:2, function(x) x >= confidence)
  specList = which(probBool!= FALSE, arr.ind=TRUE)
  return(list("treInstances"=specList, "treInstanceCount"=nrow(specList)))
}

