library(foreach)
library(autoperiod)
context("Autoperiod")

x = seq(0,2*2*pi, 0.1)
data1 <- sin(2*x)
data2 <- sin(2*x) + runif(length(x), -0.5, 0.5)
data3 <- sin(x) + 0.2*sin(10*x)
data4 <- sin(x) + cos(3*x)

test_that("period_hints returns the correct period hint", {
  expect_equal(period_hints(data1), 31.5)
  expect_equal(period_hints(data2), 31.5)
  expect_equal(period_hints(data3), 63)
  expect_equal(period_hints(data4), c(63, 21))
})

test_that("autoperiod returns the correct period", {
  expect_equal(autoperiod(data1), 32)
  expect_equal(autoperiod(data2), 32)
  expect_equal(autoperiod(data3), 64)
  expect_equal(autoperiod(data4), c(64, 21))
})