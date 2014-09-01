p = 1 - prod(c(343:365)) / (365^23)
pa = 0.5
pb = 0.75
ppab = 0.5

p4 = 0.99*0.05 / (0.01*0.92+0.05*0.99)

unif_data <- runif(10000, min=0, max=1)
data = - log(1 - unif_data)

hist(data, breaks=100)
par(new=TRUE)
curve(exp(-x), ann=FALSE, axes=FALSE, xlim=c(0,8), col="red")

hist(sqrt(data), breaks=100)
par(new=TRUE)
curve(2*x*exp(-x^2), ann=FALSE, axes=FALSE, xlim=c(0,3), col="red")
