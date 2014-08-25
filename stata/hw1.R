data <- read.csv('Desktop/innopolis/stata/data.csv')

n = length(data$X)

mean_x = sum(data$X) / n
mean_y = sum(data$Y) / n
div_x = sqrt(sum((data$X - mean_x)^2) / (n - 1))
div_y = sqrt(sum((data$Y - mean_y)^2) / (n - 1))
r = sum((data$X - mean_x) * (data$Y - mean_y)) / (div_x * div_y * (n - 1))
beta1 = sum((data$X - mean_x) * (data$Y - mean_y)) / sum((data$X - mean_x)^2)
beta0 = mean_y - beta1 * mean_x
Y_e = beta0 + beta1 * data$X
u_e = data$Y - Y_e

mean(data$X)
mean(data$Y)
sd(data$X)
sd(data$Y)
cor(data$X,data$Y)
lm(data$Y ~ data$X)
predict(lm(data$Y ~ data$X))

# set up the plot
plot(data$X, data$Y, xlab = "Cigarettes consumed per capita in 1930 (X)", ylab = "Lung cancer deaths per million people in 1950 (Y)", xlim = c(0, 1300), ylim=c(0, 500), main = "Regression of Lung cancer deaths on Cigarettes consumed per capita\nY = 28.3966 + 0.3364X")
par(new=TRUE)
curve(beta0 + beta1 * x, col="red", ann = FALSE,  xlim = c(0, 1300), ylim=c(0, 500), lty=1, lwd = 3)
text(data$X, data$Y, data$Country, cex=0.7, pos=3, col="black")
legend("topleft", c("Regression line"), col = ("red"), bty='n', cex=.75, lty = c(1), lwd = c(3))