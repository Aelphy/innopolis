x = runif(10000)
z = rexp(10000)

y = sqrt(12)*(x - 0.5)
w = z - 1

length(w[w > 1.96 ]) / length(w)
length(w[w < - 1.96 ]) / length(w)

length(y[y > 1.96 ]) / length(y)
length(y[y < - 1.96 ]) / length(y)

gen_y <- function(n) { y = sqrt(12/n)*sum(runif(n) - 0.5) }

y_series <- function(n,k) {
  data = vector(length=k)
  for(i in 1:length(data)) {
    data[i] = gen_y(n)
  }

  data
}

gen_w <- function(n) { w = sum(rexp(n) - 1)/sqrt(n) }

w_series <- function(n,k) {
  data = vector(length=k)
  for(i in 1:length(data)) {
    data[i] = gen_w(n)
  }
  
  data
}

y1 = y_series(2, 10000)
length(y1[y1 > 1.96 ]) / length(y1)
length(y1[y1 < - 1.96 ]) / length(y1)

y2 = y_series(5, 10000)
length(y2[y2 > 1.96 ]) / length(y2)
length(y2[y2 < - 1.96 ]) / length(y2)

y3 = y_series(100, 10000)
length(y3[y3 > 1.96 ]) / length(y3)
length(y3[y3 < - 1.96 ]) / length(y3)

hist(y, breaks = 100)

hist(y1, breaks = 100)

hist(y2, breaks = 100)

hist(y3, breaks = 100)

w1 = w_series(2, 10000)
length(w1[w1 > 1.96 ]) / length(w1)
length(w1[w1 < - 1.96 ]) / length(w1)

w2 = w_series(5, 10000)
length(w2[w2 > 1.96 ]) / length(w2)
length(w2[w2 < - 1.96 ]) / length(w2)

w3 = w_series(100, 10000)
length(w3[w3 > 1.96 ]) / length(w3)
length(w3[w3 < - 1.96 ]) / length(w3)

hist(w, breaks = 100)

hist(w1, breaks = 100)

hist(w2, breaks = 100)

hist(w3, breaks = 100)

sqrt(215/400 * (1-215/400)/400)

(215/400 - 0.5)/0.02492959


