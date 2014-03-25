#!/bin/bash
# Script che da n file .fdat e m file di template, produce n*m file generati
# Primo argomento: cartella dei dati
# secondo argomento: cartella dei template
# Terzo argomento. cartella dei risultati
# Ambedue senza / alla fine!! ./ciao/ SBAGLIATO, ./ciao GIUSTO!!!
for filedati in ../DatiFormattati/*.fdat
do
	for template in ../GnuPlot/*.templatescript
	do
		echo "filedati: $filedati"
		echo "template: $template"
		echo '' | ./InterfacciaFitGnuplot.pl $filedati $template | gnuplot -p
	done
done
exit 0
