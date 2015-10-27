library(automatonR)
context("Automaton Testing")

test_that("Regex: (1.<0+>)+ ", {

  traceTimes = c(0, 2, 2, 4, 12, 13, 18, 20, 23)
  traceEvents = c(1, 2, 2, 2, 3, 2, 3, 3, 2)
  alphabetLength = 3
  startIntervals = c(2)
  endIntervals = c(5)
  intervals = list("start" = startIntervals, "end" = endIntervals)

  r = processTrace(traceTimes, traceEvents, alphabetLength, intervals, 1)

  e_success = array(c(NA, 3, 0, 0, NA, 1, 0, 0, NA), c(3, 3))
  e_reset = array(c(NA, 2, 3, 3, NA, 3, 2, 6, NA), c(3, 3))

  expect_equal(e_success, r$success)
  expect_equal(e_reset, r$reset)
})


test_that("Regex: <0>+ ", {

  traceTimes = c(0, 2, 5, 10, 12, 15, 16, 18, 20)
  traceEvents = c(1, 2, 1, 2, 3, 3, 1, 3, 4)
  alphabetLength = 4
  startIntervals = c(2)
  endIntervals = c(5)
  intervals = list("start" = startIntervals, "end" = endIntervals)

  r = processTrace(traceTimes, traceEvents, alphabetLength, intervals, 2)

  e_success = array(c(1, 1, 2, 0))
  e_reset = array(c(2, 1, 1, 1))

  expect_equal(e_success, r$success)
  expect_equal(e_reset, r$reset)
})

test_that("Regex: <0.<1.2>+> ", {

  traceTimes = c(0, 1, 3, 4, 6)
  traceEvents = c(1, 2, 3, 2, 3)
  alphabetLength = 3
  startIntervals = c(0, 0)
  endIntervals = c(5, 4)
  intervals = list("start" = startIntervals, "end" = endIntervals)

  r = processTrace(traceTimes, traceEvents, alphabetLength, intervals, 3)

  e_success = array(c(NA, NA, NA, NA, NA, 0, NA, 0, NA, NA, NA, 0, NA, NA, NA, 0, NA, NA, NA, 0, NA, 1, NA, NA, NA, NA, NA), dim = c(3,3,3))
  e_reset = array(c(NA, NA, NA, NA, NA, 3, NA, 3, NA, NA, NA, 3, NA, NA, NA, 4, NA, NA, NA, 3, NA, 1, NA, NA, NA, NA, NA), dim = c(3,3,3))

  expect_equal(e_success, r$success)
  expect_equal(e_reset, r$reset)
})

test_that("Regex: (<0.1> | <1.0>)+ ", {

  traceTimes = c(0, 2, 3, 5, 7)
  traceEvents = c(1, 2, 2, 1, 2)
  alphabetLength = 2
  startIntervals = c(0, 0)
  endIntervals = c(2, 3)
  intervals = list("start" = startIntervals, "end" = endIntervals)

  r = processTrace(traceTimes, traceEvents, alphabetLength, intervals, 4)

  e_success = array(c(NA, 1, 2, NA), dim = c(2, 2))
  e_reset = array(c(NA, 1, 0, NA), dim = c(2, 2))

  expect_equal(e_success, r$success)
  expect_equal(e_reset, r$reset)
})
