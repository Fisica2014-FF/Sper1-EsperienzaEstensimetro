#!/usr/bin/perl
use strict;
use warnings;
use Data::Dumper; # Package per testare gli hash vari
use File::Basename;
use 5.010;

# An anonymous array in perl is constructed using square brackets [ ].
# Array di array

# Cosa voglio:
# ./InterfacciaFitGnuplot ./CartellaFileTemplate ./CartellaFileDati
# Dati una serie di file di dati .fdat, voglio un sistema coerente e consistente per effettuare operazioni
# identiche (nel senso che la variabilità dipende solo da info nei file) su di essi, dove
# con operazione si intende una funzione f(file_fdat, template, oracolo) => file_di_output che crea un file dove
# le variabili di template, indicate __COSI__, oppure __@COSI__ sono sostituite con il loro valore

# Ci sono 3 argomenti: file_fdat, template, e oracolo.
# Il programma agirà su un file di fdat (primo argomento), usando le informazioni in esso e
# fornite eventualmente dall'oracolo (in programma che stampa sullo standard output) contenute per
# riempire il template (secondo argomento) e stamperà il risultato sullo standard output

#die "Errore: Troppi pochi argomenti"if $#ARGV < 1;

#Apri il file di dati in sola lettura
open FILEDATI, "<", $ARGV[0] or die "[Errore]: Errore nell'apertura del file di dati";
open FILETEMPLATE, "<", $ARGV[1] or die "[Errore]: Errore nell'apertura del file di template";

# se ./ciao/Darth.fener allora $name = Dart, $path = ./ciao/, $suffix = vader
my ($named,$pathd,$suffixd) = fileparse($ARGV[0],qr/\.[^.]*/); #File dei dati
my ($namet,$patht,$suffixt) = fileparse($ARGV[1],qr/\.[^.]*/); #FIle del template

my $nomesuffissod = $named.$suffixd;
my $nomesuffissot = $namet.$suffixt;

my $pathnomed = $pathd.$named;
my $pathnomet = $patht.$namet;

my @lines = <FILEDATI>;
my @risposteoracolo = <STDIN>;
my %metadati = ();

#Costruisci l'hash dei metadati
CICLODATI:
foreach my $linea (@lines) {
	# Se linea contiene la regex, salva l'hash
	# Regex: linea che inizia con #%, poi ha una parola e poi un numero TODO eventualmente permettere stringhe come valori
	# la x indica che permettiamo spazi e commenti
	#next CICLODATI if (/^#[^%]/); #Salta le righe coi commenti, che iniziano con # seguito da qualsiasi carattere diverso da %
    # Altrimenti siamo nel caso sotto
	if ($linea =~ /^\#\% (\w+)  \:  (\-? \d+ \.? \d*) /x) {
		#                ^^^^^      ^^^^^^^^^^^^^^^^
		#                 $1               $2
		# Memorizza il primo gruppo di cattura come chiave dell'hash, e associaci il valore del secondo
		# gruppo
		$metadati { $1 } = $2;
	}
}

#Guarda nelle risposte dell'oracolo
foreach my $linea (@risposteoracolo) {
	# Se linea contiene la regex, salva l'hash
	# Regex: linea che inizia con #%, poi ha una parola e poi un numero TODO eventualmente permettere stringhe come valori
	# la x indica che permettiamo spazi e commenti
	if ($linea =~ /^\#\% (\w+)  \:  (\-? \d+ \.? \d*) /x) {
		#                ^^^^^      ^^^^^^^^^^^^^^^^
		#                 $1               $2
		# Memorizza il primo gruppo di cattura come chiave dell'hash, e associaci il valore del secondo
		# gruppo
		$metadati { $1 } = $2;
	}
}


# TEST
#say $metadati{"LUNGHEZZA"};
#say $pathnomed;
#say Dumper(%metadati);


@lines = <FILETEMPLATE>;

#Per ogni linea del file di template, 
CICLOTEMPLATE:
foreach my $linea (@lines) {

	#next CICLOTEMPLATE if (/^#/); #Salta le righe coi commenti, che iniziano con # seguito da qualsiasi carattere diverso da %

	#Per ogni caso, una sostituzione appropriata
	#Qui, i tag speciali, che iniziano con @, vengono sostituiti
	
	# Metti le robe dei file di dati in sè
	$linea =~ s/__\@FILE_DATI__/$ARGV[0]/g;
	$linea =~ s/__\@PATH_DATI__/$pathd/g;
	$linea =~ s/__\@NOME_DATI__/$named/g;
	$linea =~ s/__\@NOMESUFFISSO_DATI__/$nomesuffissod/g;
	$linea =~ s/__\@PATHNOME_DATI__/$pathnomed/g;
	
	
	# Metti le robe del file di template
	$linea =~ s/__\@FILE_TEMPLATE__/$ARGV[1]/g;
	$linea =~ s/__\@PATH_TEMPLATE__/$patht/g;
	$linea =~ s/__\@NOME_TEMPLATE__/$namet/g;
	$linea =~ s/__\@NOMESUFFISSO_TEMPLATE__/$nomesuffissot/g;
	$linea =~ s/__\@PATHNOME_TEMPLATE__/$pathnomet/g;
	
	
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
