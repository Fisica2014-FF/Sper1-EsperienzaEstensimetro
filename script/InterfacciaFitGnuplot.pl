#!/usr/bin/perl
use strict;
use warnings;

# An anonymous array in perl is constructed using square brackets [ ].
# Array di array

# Cosa voglio:
# ./InterfacciaFitGnuplot ./CartellaFileTemplate ./CartellaFileDati
# Dati una serie di file di dati .fdat, voglio un sistema coerente e consistente per effettuare operazioni
# identiche (nel senso che la variabilità dipende solo da info nei file) su di essi, dove
# con operazione si intende una funzione f(file_fdat, template) => file_di_output che crea un file dove
# le variabili di template, indicate __COSI__, oppure __@COSI__ sono sostituite con il loro valore

# Il programma agirà su un file di d