/*
 * NomeDiFile.cpp
 *
 *  Created on: Mar 22, 2014
 *      Author: francesco
 */

#include "NomeDiFile.h"
#include <string>
#include <iostream>

namespace mions {

namespace utils {


// Ideal
NomeDiFile::NomeDiFile(const std::string stringanomefile) {
	using std::string;

	if (stringanomefile.empty())
		throw "[Errore]: Nome File non valido: stringa vuota";

	// TODO: idealmente se il file viene passato come nome semplice (es "ciao.txt") si presume
	// che riesca a capirlo e metterlo come ./ciao.txt
	if (stringanomefile.substr(0,2) == "./" or stringanomefile.substr(0,1) == "/")
		pathTotale = stringanomefile;
	else
		pathTotale = string("./") + stringanomefile;

	//Dividi la cartella dal nome
	unsigned slash = pathTotale.find_last_of("/");
	nomeCartella = pathTotale.substr(0,slash);
	nomePiuEstensione = pathTotale.substr(slash+1);

	auto punto = nomePiuEstensione.find_last_of(".");

	//Controlla se ha estensione (se ha il punto)
	if (punto != nomePiuEstensione.npos) {
		nome = nomePiuEstensione.substr(0,punto);
		estensione = nomePiuEstensione.substr(punto+1);
		if (nome.empty()) {
			throw string("[Errore]: Probabilmente usato file nascosto: ") + stringanomefile;
		}
	} else {
		std::clog << "[Warning]: Usato file senza estensione: " << stringanomefile << std::endl;

		nome = nomePiuEstensione;
		estensione = "";
	}

}

//Stampa i vari componenti del nome del file, utile per il debug
std::ostream& operator <<(std::ostream& os, const NomeDiFile& rhs) {
	//Se il nome di file passato al costruttore è ./ciao/Darth.vader
	os << "pathTotale: " 		<< rhs.pathTotale 			 << std::endl;  // questo è ./ciao/Darth.vader
	os << "nomeCartella: "  	<< rhs.nomeCartella 		 << std::endl;	// questo è ./ciao
	os << "nome: " 				<< rhs.nome 				 << std::endl; 	// questo è Darth
	os << "estensione: "		<< rhs.estensione 			 << std::endl; 	// questo è vader
	os << "nomePiuEstensione: " << rhs.nomePiuEstensione 	 << std::endl;	// questo è Dart.vader
	return os;
};

}

}


