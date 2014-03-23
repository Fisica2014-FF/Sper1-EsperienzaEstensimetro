#!/usr/bin/perl
use strict;
use warnings;
use Data::Dumper; # Package per testare gli hash vari
use 5.010;

# An anonymous array in perl is constructed using square brackets [ ].
# Array di array

# Cosa voglio:
# ./InterfacciaFitGnuplot ./CartellaFileTemplate ./CartellaFileDati
# Dati una serie di file di dati .fdat, voglio un sistema coerente e consistente per effettuare operazioni
# identiche (nel senso che la variabilità dipende solo da info nei file) su di essi, dove
# con operazione si intende una funzione f(file_fdat, template, cartella dell'output) => file_di_output che crea un file dove
# le variabili di template, indicate __COSI__, oppure __@COSI__ sono sostituite con il loro valore

# Ci sono 3 argomenti: file_fdat, template e cartella dell'output
# Il programma agirà su un file di fdat (primo argomento), usando le informazioni in esso contenute per
# riempire il template e salverà il risultato

#die "Errore: Troppi pochi argomenti"if $#ARGV < 1;

#Apri il file di dati in sola lettura
open FILEDATI, "<", $ARGV[0] or die "[Errore]: Errore nell'apertura del file di dati";
open FILETEMPLATE, "<", $ARGV[1] or die "[Errore]: Errore nell'apertura del file di template";

my @lines = <FILEDATI>;
my %metadati = ();

#Costruisci l'hash dei metadati
CICLODATI:
foreach my $linea (@lines) {
	# Se linea contiene la regex, salva l'hash
	# Regex: linea che inizia con #%, poi ha una parola e poi un numero TODO eventualmente permettere stringhe come valori
	# la x indica che permettiamo spazi e commenti
	#next CICLODATI if (/^#[^%]/); #Salta le righe coi commenti, che iniziano con # seguito da qualsiasi carattere diverso da %
							  # Altrimenti siamo nel caso sotto
	if ($linea =~ /^\#\% (\w+)  \:  (\d+ \.? \d*) /x) {
		#                ^^^^^      ^^^^^
		#                 $1          $2
		# Memorizza il primo gruppo di cattura come chiave dell'hash, e associaci il valore del secondo
		# gruppo
		$metadati { $1 } = $2;
	}
}

# TEST
say $metadati{"LUNGHEZZA"};
say Dumper(%metadati);




@lines = <FILETEMPLATE>;

#Per ogni linea del file di template, 
CICLOTEMPLATE:
foreach my $linea (@lines) {

	#next CICLOTEMPLATE if (/^#/); #Salta le righe coi commenti, che iniziano con # seguito da qualsiasi carattere diverso da %
							  		  # Altrimenti siamo nel caso sotto
	# TODO: Sostituire il nome del file
	if ($linea =~ s/__\@NOME_DATI__/$ARGV[0]/g){
		print $linea;
		next CICLOTEMPLATE;
	}
	
	$linea =~ s/__\@NOME_TEMPLATE__/$ARGV[1]/g {
		print $linea;
		next CICLOTEMPLATE;
	}
	
	# Se la riga contiene un tag, sostituiscilo secondo le regole dello standard					  		  	
	$linea =~ s/__(\w+)__/$metadati{$1}/g; 
		#         ^^^^^
		#          $1
	if (defined $1) {
		die "[Errore]: La chiave non esiste: $1" unless exists $metadati{$1};
	}
	# Sostituisci il tag del template con il corrispondente valore nell'hash
	print $linea;
}
