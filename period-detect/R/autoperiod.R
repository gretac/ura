period_hints <- function(data) {
  k <- 100  # number of permutations
  max_power <- foreach::foreach(i = 1:k, .combine = "c") %do% {
    s <- sample(data)
    periodogram <- spec.pgram(s, taper = 0, fast = FALSE, detrend = FALSE, log = "no")
    max(periodogram$spec)
  }
  percentile <- 99
  max_power_sorted <- sort(max_power)
  p_threshold <- max_power_sorted[length(max_power) * (percentile / 100)]
  
  # with actual data
  periodogram <- spec.pgram(data, taper = 0, fast = FALSE, detrend = FALSE, log = "no")
  freq <- periodogram$freq
  power <- periodogram$spec
  acceptable_power_index <- sapply(power, function(x) x > p_threshold)
  hint_freq <- freq[acceptable_power_index]
  
  # period trimming
  hint_periods <- 1 / hint_freq
  N <- length(data)
  valid_hint_period_index <- sapply(hint_periods, function(x) x < N / 2 || x >= 2)
  valid_hint_periods <- hint_periods[valid_hint_period_index]
  
  return(valid_hint_periods)
} 

cacf <- function(data) {
  fft <- fft(data)
  periodogram <- abs(fft) ^ 2
  return(Re(fft(periodogram, inverse = TRUE)))
} 

autoperiod <- function(data) {
    hint_periods <- period_hints(data)
    cacf <- cacf(data)
    result <- 0
    plot(cacf, type = "l")
    index <- 1
    for (hint in hint_periods) {
        period_index <- floor(hint)
        abline(v = period_index, col = index)
        if (cacf[period_index - 1] < cacf[period_index]) {
            # already the peak  
            if (cacf[period_index] > cacf[period_index + 1]) {
                result[index] <- period_index    
            } else {
                hill <- TRUE
                while (hill) {
                    if (cacf[period_index] < cacf[period_index + 1]) {
                        period_index <- period_index + 1
                    } else {
                        hill <- FALSE
                    }
                }
                result[index] <- period_index  
            }
        } 
        index <- index + 1  
    }
    return(result)
}