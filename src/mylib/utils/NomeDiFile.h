/*
 * NomeDiFile.h
 *
 *  Created on: Mar 22, 2014
 *      Author: francesco
 */
#include <string>

#ifndef NOMEDIFILE_H_
#define NOMEDIFILE_H_

namespace mions {

namespace utils {

class NomeDiFile {

	//Se il nome di file passato al costruttore è ./ciao/Darth.vader
	std::string PathTotale;  		// questo è ./ciao/Darth.vader
	std::string nomeCartella;		// questo è ./ciao
	std::string nome; 				// questo è Darth
	std::string estensione; 		// questo è vader
	std::string nomePiuEstensione;	// questo è Dart.vader
	NomeDiFile(const std::string& stringanomefile);
	//NomeDiFile(const char* charnomefile);
	std::ostream& operator <<(std::ostream& os, const NomeDiFile& rhs);
};

}

}

#endif /* NOMEDIFILE_H_ */
