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
processTrace = function(traceTimes, traceEvents, alphabetLength, timedRegEx) {
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

  result = processTrace_rcpp(traceTimes, traceEvents, alphabetLength, automatonPtr)

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
  return(which(prob == TRUE, arr.ind=TRUE))
}
runSyntheticExperiment = function(dirPath){
  #Setup 1
  Sys.setenv("PKG_CXXFLAGS"="-std=c++0x")
  tLengths = seq(from = 10000,to = 40000, by = 10000)
  uniqEvents = 4
  noOfTraces = 2
  pyscript = "/home/y2joshi/workspace/TRETraceGenerator/test/traceCreate.py"
  for(tLength in tLengths){
    dirArg = paste("/home/y2joshi/",setup, tLength, sep = "")
    print(dirArg)
    try(system(paste("python", pyscript, tLength, uniqEvents, noOfTraces,dirArg), ignore.stdout = FALSE))
    traceFiles = list.files(dirArg,pattern = "trace*")
    #print(traceFiles)
    for(j in 1:noOfTraces){
      t1 = proc.time()
      for(aTrace in traceFiles){
          fullTracePath = paste(dirArg,"/",aTrace,sep="")

          traceData = read.csv(file=fullTracePath, header=TRUE, sep=",")
          traceEvents = traceData$traceEvents
          traceTimes = traceData$traceTimes
          alphabetLength = uniqEvents
#         print(length(traceTimes))
#         print(length(traceEvents))
#         print(alphabetLength)
          print(fullTracePath)
          processTrace(traceTimes, traceEvents, alphabetLength, "(^(0)*).((<0.^(1)*.1>[0,2000]).(^(0)*))+")
          print(paste(fullTracePath, " done", sep = ""))
  #     r2 = processTrace(traceTimes, traceEvents, alphabetLength, "(^(0|1)*).((<0.^(0|1)*.1.^(0|1)*>[0,2000]))+")
  #     r3 = processTrace(traceTimes, traceEvents, alphabetLength, "(^(0|1)*).((<0.^(0|1)*.1.^(0)*>[0,2000]))+")
  #     r4 = processTrace(traceTimes, traceEvents, alphabetLength, "(^(0|1)*).((<0.^(1)*.1.^(0|1)*>[0,2000]))+")
        }
        t2 = proc.time()

#       ts = (t2-t1)['elapsed']
#       resultValues = paste(j,tLength, sep=",")
#       cat(paste(resultValues, "\n", sep=""),file = outputFile, append = TRUE)
#       print(resultValues)
    }
  }
}
