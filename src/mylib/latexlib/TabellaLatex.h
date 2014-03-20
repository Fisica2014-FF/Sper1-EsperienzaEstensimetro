/*
 * TabellaLatex.h
 *
 *  Created on: Mar 17, 2014
 *      Author: francesco
 */
#include <string>

#ifndef TABELLALATEX_H_
#define TABELLALATEX_H_

//Il mio namespace
namespace mions {

namespace latexlib{

//Classe base
class TabellaLatex {
	using std::string;

	string formatoVerticale; // Esempio: |l|r|r|r|r|r|r|r|
	string titolo; //Titolo della tabella, idealmente dovrebbe decidere lei dove e come metterlo
	string caption; //Casomai dovessimo differenziare

	virtual ~TabellaLatex();
};

class TabRighellataCentrata : TabellaLatex {

};


// Classe che mette insieme nella stessa tabella più colonne di dati, perchè appartengono allo stesso
// gruppo di misure, es guidovia erano i dati per una stessa inclinazione, l'estensimetro uno stesso estensimetro, etc
class TabGruppoDati : TabRighellataCentrata {

};

}

}

#endif /* TABELLALATEX_H_ */
