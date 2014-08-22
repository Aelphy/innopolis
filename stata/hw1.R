data <- read.csv('Desktop/innopolis/stata/data.csv')

n = length(data$X)

mean_x = sum(data$X) / n
mean_y = sum(data$Y) / n
div_x = sqrt(sum((data$X - mean_x)^2) / (n - 1))
div_y = sqrt(sum((data$Y - mean_y)^2) / (n - 1))
r = sum((data$X - mean_x) * (data$Y - mean_y)) / (div_x * div_y * n)

mean(data$X)
mean(data$Y)
sd(data$X)
sd(data$Y)
cor(data$X,data$Y)
