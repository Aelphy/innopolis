library('fGarch')

make_the_diff <- function (serie) {
  vol = {}
  
  for (k in 1:(length(serie) - 1)) {
    vol[k] = serie[k + 1] - serie[k]
  }
  
  return(vol)
}

data = read.csv("Documents/innopolis/statistics/bd/research_paper/R01235.csv")

current_crisis = data$DATA.D[as.numeric(as.Date(data$DATA.D, '%d.%m.%y')) > as.numeric(as.Date('21.11.2013', '%d.%m.%Y'))]
current_cours = data$CURS.N.38.5[as.numeric(as.Date(data$DATA.D, '%d.%m.%y')) > as.numeric(as.Date('21.11.2013', '%d.%m.%Y'))]
current_volatility = {}

world_finance_crisis = data$DATA.D[as.numeric(as.Date(data$DATA.D, '%d.%m.%y')) < as.numeric(as.Date('31.12.2011', '%d.%m.%Y')) & as.numeric(as.Date(data$DATA.D, '%d.%m.%y')) > as.numeric(as.Date('1.1.2008', '%d.%m.%Y'))]
world_finance_cours = data$CURS.N.38.5[as.numeric(as.Date(data$DATA.D, '%d.%m.%y')) < as.numeric(as.Date('31.12.2011', '%d.%m.%Y')) & as.numeric(as.Date(data$DATA.D, '%d.%m.%y')) > as.numeric(as.Date('1.1.2008', '%d.%m.%Y'))]
world_finance_volatility = {}

current_volatility <- make_the_diff(current_cours)
world_finance_volatility <- make_the_diff(world_finance_cours)

plot(as.Date(current_crisis, '%d.%m.%y'), current_cours, type='l', col='Red')

plot(as.Date(current_crisis[1:(length(current_crisis) -1)], '%d.%m.%y'), current_volatility, type='l', col='Red')
plot(as.Date(current_crisis[1:(length(world_finance_crisis) -1)], '%d.%m.%y'), world_finance_volatility, type='l', col='Red')


garchFit(formula = ~ garch(1, 1), current_volatility)
garchFit(formula = ~ garch(1, 1), world_finance_volatility)
