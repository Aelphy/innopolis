data = read.csv("Documents/innopolis/statistics/bd/R01235.csv")

improved_data = data$DATA.D[as.numeric(as.Date(data$DATA.D, '%d.%m.%y')) > as.numeric(as.Date('21.11.2013', '%d.%m.%Y'))]
improved_cours = data$CURS.N.38.5[as.numeric(as.Date(data$DATA.D, '%d.%m.%y')) > as.numeric(as.Date('21.11.2013', '%d.%m.%Y'))]

plot(as.Date(improved_data, '%d.%m.%y'), improved_cours, type='l', col='Red')

volatility = {}

for (k in 1:(length(improved_cours) - 1)) {
  volatility[k] = (improved_cours[k + 1] - improved_cours[k])
}

plot(as.Date(improved_data[1:(length(improved_data) -1)], '%d.%m.%y'), volatility, type='l', col='Red')

garchFit(formula = ~ garch(1, 1), volatility)
