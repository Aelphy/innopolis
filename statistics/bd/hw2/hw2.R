library("MASS")
library("robust")

data <- read.csv("Desktop/innopolis/statistics/bd/hw2/Growth.csv")

n = length(data$growth)

rlm(X, Y)
predictions = predict(rlm(data$growth ~ data$tradeshare))

b0 = lm(data$growth ~ data$tradeshare)$coefficients[1]
b1 = lm(data$growth ~ data$tradeshare)$coefficients[2]

b0_1 = rlm(data$growth ~ data$tradeshare)$coefficients[1]
b1_1 = rlm(data$growth ~ data$tradeshare)$coefficients[2]

b0_2 = rlm(data$growth[0:64] ~ data$tradeshare[0:64])$coefficients[1]
b1_2 = rlm(data$growth[0:64] ~ data$tradeshare[0:64])$coefficients[2]

plot(data$tradeshare, data$growth, xlim = c(-1, 3), ylim=c(-5, 10))
par(new=TRUE)
curve(b0_1 + b1_1 * x, xlim = c(-1, 3), ylim=c(-5, 10), ann=FALSE, xlab=NULL, ylab=NULL,  lty=1, lwd = 3, add=FALSE)
legend("topleft", c("Regression line"), bty='n', cex=.75, lty = c(1), lwd = c(3))

plot(data$tradeshare, data$growth, xlim = c(0, 2.2), ylim=c(-5, 7), main = "Regressions")
par(new=TRUE)
curve(b0_1 + b1_1 * x, xlim = c(0, 2.2), ylim=c(-5, 7), ann=FALSE, xlab=NULL, ylab=NULL,  lty=1, lwd = 3, add=FALSE, col="red")
par(new=TRUE)
curve(b0 + b1 * x, xlim = c(0, 2.2), ylim=c(-5, 7), ann=FALSE, xlab=NULL, ylab=NULL,  lty=1, lwd = 3, add=FALSE, col="blue")
par(new=TRUE)
curve(b0_2 + b1_2 * x, xlim = c(0, 2.2), ylim=c(-5, 7), ann=FALSE, xlab=NULL, ylab=NULL,  lty=1, lwd = 3, add=FALSE)
par(new=TRUE)
legend(1, -1, c("Regression line without robust"), col="blue", bty='n', cex=.75, lty = c(1), lwd = c(3))
par(new=TRUE)
legend(1, -2, c("Regression line with robust"), col="red", bty='n', cex=.75, lty = c(1), lwd = c(3))
par(new=TRUE)
legend(1, -3, c("Regression line with robust and without outlier"), bty='n', cex=.75, lty = c(1), lwd = c(3))

ESS = sum((predictions  - mean(data$growth))^2)
TSS = sum((data$growth  - mean(data$growth))^2)

r_sq = ESS/TSS

cor(data$growth, data$tradeshare)

u_e = Y - rpred

sd(u_e)

X_1 = X[1:64]
Y_1 = Y[1:64]

plot(X_1, Y_1, xlim = c(-1, 3), ylim=c(-5, 10))
par(new=TRUE)
curve(b0_1 + b1_1 * x, xlim = c(0, 3), ylim=c(-5, 10), ann=FALSE, xlab=NULL, ylab=NULL,  lty=1, lwd = 3, add=FALSE)

sterr_b1 = sqrt(sum((data$tradeshare - mean(data$tradeshare))^2*(predictions-data$growth)^2) / (n-2)^2) / (sum((data$tradeshare-mean(data$tradeshare))^2)/n)

t = b1_1 / sterr_b1

R_sq = sum(predictions-mean(data))

data$lorgdp60 = 0

for(i in 1:n) { if(data$rgdp60[i] <= quantile(data$rgdp60)[2]){ data$lorgdp60[i] = 1 } }

rlm(growth ~ lorgdp60, data=data)
lm(growth ~ lorgdp60, data=data)

(mean(neg_lorgdp60$growth) - mean(poslorgdp60$growth))/sqrt(sd(neg_lorgdp60$growth)^2/length(neg_lorgdp60$growth) + sd(poslorgdp60$growth)^2/length(poslorgdp60$growth))

