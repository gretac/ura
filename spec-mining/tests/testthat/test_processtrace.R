library(automatonR)

context("Automaton Testing")
# test_that("Regex: (0.0.^(0).^(0))", {
#   traceTimes = c(0, 2, 4, 5)
#   traceEvents = c(1, 1 , 2, 2)
#   alphabetLength = 2
#   r = processTrace(traceTimes, traceEvents, alphabetLength, "(0.0.^(0).^(0))")
#   e_success = array(c(1))
#   e_reset = array(c(0))
#   expect_equal(e_success, r$success)
#   expect_equal(e_reset, r$reset)
# })
# test_that("Regex: (1.0)+ ", {
#
#   traceTimes = c(0, 2, 2, 6, 12, 13, 18, 20, 23, 26)
#   traceEvents = c(1, 2, 2, 2, 3, 2, 3, 3, 2, 2)
#   alphabetLength = 3
#
#   r = processTrace(traceTimes, traceEvents, alphabetLength, "(1.0)+")
#
#   e_success = array(c(NA, 1, 1, 0, NA, 2, 0 ,1 , NA), c(3, 3))
#   e_reset = array(c(NA, 5, 2, 4, NA, 3, 2, 6, NA), c(3, 3))
#
#   expect_equal(e_success, r$success)
#   expect_equal(e_reset, r$reset)
# })

test_that("Regex: (1.<0+>)+ ", {

  traceTimes = c(0, 2, 3, 6, 12, 13, 18, 20, 23, 24)
  traceEvents = c(1, 2, 2, 2, 3, 2, 3, 3, 2, 2)
  alphabetLength = 3

  r = processTrace(traceTimes, traceEvents, alphabetLength, "(1.<0+>[2,5])+")

  e_success = array(c(NA, 2, 0, 0, NA, 1, 0, 0, NA), c(3, 3))
  e_reset = array(c(NA, 4, 3, 4, NA, 4, 2, 7, NA), c(3, 3))

  expect_equal(e_success, r$success)
  expect_equal(e_reset, r$reset)
})


test_that("Regex: <0>+ ", {

  traceTimes = c(0, 2, 5, 10, 12, 15, 16, 18, 20, 22)
  traceEvents = c(1, 2, 1, 2, 3, 3, 1, 3, 4, 4)
  alphabetLength = 4

  r = processTrace(traceTimes, traceEvents, alphabetLength, "(<0>[2,5])+")

  e_success = array(c(1, 1, 2, 1))
  e_reset = array(c(2, 1, 1, 1))

  expect_equal(e_success, r$success)
  expect_equal(e_reset, r$reset)
})

test_that("Regex: <0.<1.2>+> ", {

  traceTimes = c(0, 1, 3, 4, 6)
  traceEvents = c(1, 2, 3, 2, 3)
  alphabetLength = 3

  r = processTrace(traceTimes, traceEvents, alphabetLength, "<0.(<1.2>[0,5])+>[0,4]")

  e_success = array(c(NA, NA, NA, NA, NA, 0, NA, 0, NA, NA, NA, 0, NA, NA, NA, 0, NA, NA, NA, 0, NA, 1, NA, NA, NA, NA, NA), dim = c(3,3,3))
  e_reset = array(c(NA, NA, NA, NA, NA, 3, NA, 3, NA, NA, NA, 3, NA, NA, NA, 4, NA, NA, NA, 3, NA, 1, NA, NA, NA, NA, NA), dim = c(3,3,3))

  expect_equal(e_success, r$success)
  expect_equal(e_reset, r$reset)
})

test_that("Regex: (<0.1> | <1.0>)+ ", {

  traceTimes = c(0, 2, 3, 5, 7)
  traceEvents = c(1, 2, 2, 1, 2)
  alphabetLength = 2

  r = processTrace(traceTimes, traceEvents, alphabetLength, "(<0.1>[0,2] | <1.0>[0,3])+")

  e_success = array(c(NA, 1, 2, NA), dim = c(2, 2))
  e_reset = array(c(NA, 1, 0, NA), dim = c(2, 2))

  expect_equal(e_success, r$success)
  expect_equal(e_reset, r$reset)
})

test_that("Regex: <0+><1+><2+> ", {

  traceTimes = c(0, 2, 3, 5, 7)
  traceEvents = c(1, 2, 3, 1, 2)
  alphabetLength = 3

  r = processTrace(traceTimes, traceEvents, alphabetLength, "<0+>[0,2]<1+>[0,4]<2+>[0,6]" )

  e_success = array(c(NA, NA, NA, NA, NA, 0, NA, 1, NA, NA, NA, 1, NA, NA, NA, 0, NA, NA, NA, 0, NA, 1, NA, NA, NA, NA, NA), dim = c(3, 3, 3))
  e_reset = array(c(NA, NA, NA, NA, NA, 4, NA, 2, NA, NA, NA, 2, NA, NA, NA, 3, NA, NA, NA, 3, NA, 2, NA, NA, NA, NA, NA), dim = c(3, 3, 3))

  expect_equal(e_success, r$success)
  expect_equal(e_reset, r$reset)
})
test_that("Regex: (0.<1+>.2) ", {

  traceTimes = c(0, 2, 3, 5, 6)
  traceEvents = c(1, 2, 3, 1, 1)
  alphabetLength = 3

  r = processTrace(traceTimes, traceEvents, alphabetLength, "(0.<1+>[0,2].2)")

  e_success = array(c(NA, NA, NA, NA, NA, 0, NA, 1, NA, NA, NA, 0, NA, NA, NA, 0, NA, NA, NA, 0, NA, 1, NA, NA, NA, NA, NA), dim = c(3, 3, 3))
  e_reset = array(c(NA, NA, NA, NA, NA, 4, NA, 2, NA, NA, NA, 3, NA, NA, NA, 3, NA, NA, NA, 4, NA, 1, NA, NA, NA, NA, NA), dim = c(3, 3, 3))

  expect_equal(e_success, r$success)
  expect_equal(e_reset, r$reset)
})
test_that("Regex: (<2.(1)+.0>)+ ", {

  traceTimes = c(0, 1, 2, 3, 4, 6, 8)
  traceEvents = c(1, 2, 2, 3, 3, 1, 1)
  alphabetLength = 3

  r = processTrace(traceTimes, traceEvents, alphabetLength, "(<2.(1)+.0>[0,3])+")

  e_success = array(c(NA, NA, NA, NA, NA, 1, NA, 0, NA, NA, NA, 0, NA, NA, NA, 0, NA, NA, NA, 0, NA, 0, NA, NA, NA, NA, NA), dim = c(3, 3, 3))
  e_reset = array(c(NA, NA, NA, NA, NA, 2, NA, 5, NA, NA, NA, 6, NA, NA, NA, 6, NA, NA, NA, 6, NA, 6, NA, NA, NA, NA, NA), dim = c(3, 3, 3))

  expect_equal(e_success, r$success)
  expect_equal(e_reset, r$reset)
})
test_that("Regex: <0.1.2.3> ", {

  traceTimes = c(0, 1, 2, 3, 4, 6, 8)
  traceEvents = c(1, 2, 3, 4, 1, 2, 3)
  alphabetLength = 4

  r = processTrace(traceTimes, traceEvents, alphabetLength, "<0.1.2.3>[1,4]")

  e_success = array(c(NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, 0, NA, NA, 0, NA, NA, NA, NA, NA, NA, NA, NA, 0, NA, NA, NA, NA, NA, 0, NA, NA, NA, NA, NA, NA, NA, NA, 0, NA, NA, 1, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, 0, NA, NA, 0, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, 0, NA, NA, NA, NA, NA, NA, NA, NA, 0, NA, NA, NA, NA, NA, 0, NA, NA, NA, NA, NA, 0, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, 0, NA, NA, NA, NA, NA, 0, NA, NA, NA, NA, NA, 0, NA, NA, NA, NA, NA, NA, NA, NA, 0, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, 0, NA, NA, 0, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, 0, NA, NA, 0, NA, NA, NA, NA, NA, NA, NA, NA, 0, NA, NA, NA, NA, NA, 0, NA, NA, NA, NA, NA, NA, NA, NA, 0, NA, NA, 1, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA), dim = c(4, 4, 4, 4))
  e_reset = array(c(NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, 6, NA, NA, 4, NA, NA, NA, NA, NA, NA, NA, NA, 6, NA, NA, NA, NA, NA, 5, NA, NA, NA, NA, NA, NA, NA, NA, 5, NA, NA, 3, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, 6, NA, NA, 3, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, 5, NA, NA, NA, NA, NA, NA, NA, NA, 5, NA, NA, NA, NA, NA, 5, NA, NA, NA, NA, NA, 5, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, 6, NA, NA, NA, NA, NA, 5, NA, NA, NA, NA, NA, 4, NA, NA, NA, NA, NA, NA, NA, NA, 5, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, 5, NA, NA, 3, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, 5, NA, NA, 3, NA, NA, NA, NA, NA, NA, NA, NA, 5, NA, NA, NA, NA, NA, 5, NA, NA, NA, NA, NA, NA, NA, NA, 5, NA, NA, 3, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA, NA), dim = c(4, 4, 4, 4))

  expect_equal(e_success, r$success)
  expect_equal(e_reset, r$reset)
})
