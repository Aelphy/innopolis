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
