//============================================================================
// Name        : Misure.cpp
// Author      : Francesco Forcher
// Version     : 0.1
// Description : Programma per analizzare i dati sul pendolo raccolti in laboratorio
//============================================================================

// VERSIONE PER I COMPAGNI DEL GRUPPO!!! NON CONSEGNARE QUESTA!!!!

/////////////////////////////////////////////////////////////////////////////////////
//Librerie
#include <iostream>//cin e cout
#include <fstream>//FileStream
#include <exception>//Eccezioni
#include <string>
#include <cstdlib>//system(clear)
#include <algorithm>//Sort?
#include <sstream>//StringStream
//#include <map>
#include <vector>

/////////////////////////////////////////////////////////////////////////////////////
//le mie classi
#include "mylib/AnalisiDati/VarStat.h"//Le mie classi Template per l'analisi dati
#include "mylib/AnalisiDati/SortingVarStat.h"//Le mie classi Template per l'analisi dati
#include "mylib/utils/NomeDiFile.h"//Le mie classi Template per l'analisi dati


#define VERSIONE 1.0

/////////////////////////////////////////////////////////////////////////////////////
//Prototipi

/////////////////////////////////////////////////////////////////////////////////////
//Il primo argomento è la cartella dei dati
int main(int numParam, char* args[]) {
using namespace std;
	try{
//		const int DATO = 0;
//		const int INDICE = 1;
//
//		using FileDati = mions::dataAnalisi::File_Fdat<double>;
//		FileDati fileDati("./DatiFormattati/cancellami");
//
//		//Stampa i metadati
//		cout << "Stampa i metadati:\n";
//		for(pair<string,double> meta : fileDati.MetaDatiGenerici){
//			cout << meta.first << " = " << meta.second << endl;
//		}
//
//		cout << "\nStampa i dati:\n";
//		for(vector<double> riga : fileDati.vColDati){
//			for (double dato : riga) {
//				cout << dato << " ";
//			}
//			cout << endl;
//		}
//
//		cout << "\nTest Vari:\n";
//		cout << "fileDati[3][DATO]: " << fileDati[3][DATO] << endl;
//		cout << "fileDati[3][INDICE]: " << fileDati[3][INDICE] << endl;
//		cout << "fileDati[DIAMETRO]: " << fileDati["DIAMETRO"] << endl;
//		cout << "fileDati[indice che non esiste]: " << fileDati["ciao"];

		//TEST NomeDiFile






		//
		const int ACCIAIO   = 	1;
		const int TUNGSTENO = 	2;
		const int OTTONE    = 	3;

		//int materiali[] = {ACCIAIO,TUNGSTENO,OTTONE};


		cout << numParam;
		string stringaNomeFileDiDati;
		//map<string,> ciao;

		fstream ListaFileDiDati;
		ListaFileDiDati.open("./Altro/ListaFileDiDati.txt");


		using FileDati = mions::dataAnalisi::File_Fdat<double>;
		using vs = mions::dataAnalisi::VarStat<double>;
		//Dovrebbe essere un varstat
		FileDati kDegliEstensimetri(string("./Risultati/YoungEstensimetriGnuplot"));



		while(getline(ListaFileDiDati,stringaNomeFileDiDati)) {

			FileDati fileDati(stringaNomeFileDiDati.c_str());
			vector<vs> youngacciaio;
			vector<vs> youngtungsteno;
			vector<vs> youngottone;

			//Es da E13_andata.fdat ottengo "E13"
			string nomeEstensimetro = stringaNomeFileDiDati.substr(0,10);
			clog << "nomeEstensimetro: " << nomeEstensimetro;
			const vs kappaEstensimetro = vs(kDegliEstensimetri[nomeEstensimetro] , kDegliEstensimetri[string("ERR_") +
			                                                                                          nomeEstensimetro]);

			const vs LUNGHEZZA = vs( fileDati["LUNGHEZZA"], fileDati["ERR_LUNGHEZZA"] );
			const vs AREA = vs( pow(fileDati["DIAMETRO"],2) * M_PI / 4, fileDati["DIAMETRO"] * (M_PI / 4) * fileDati["ERR_DIAMETRO"] );

			switch ( int(fileDati["MATERIALE"]) ) {
				case ACCIAIO:
					//x0 / (A*k2) | k2 = Dx / Df <= beta delle rette
					youngacciaio.push_back( LUNGHEZZA / (AREA * kappaEstensimetro ) );

					break;
				case TUNGSTENO:
					youngtungsteno.push_back( LUNGHEZZA / (AREA * kappaEstensimetro ) );

					break;
				case OTTONE:
					youngottone.push_back( LUNGHEZZA / (AREA * kappaEstensimetro ) );

					break;
				default:
					throw "Errore nello switch";
					break;
			}

			vs somma(0);
			for (auto myoung : youngacciaio)
				somma += myoung;
			cout << "Media acciaio" << somma * (1.0 / double(youngacciaio.size()));

		}

	} catch (exception &e) {
		cout << e.what() << endl;
		return -1;
	} catch (string &e) {
		cout << e << endl;
		return -2;
	} catch (const char* e) {
		cout << e << endl;
		return -3;
	}

	//cout << "\n";
	return 0;
}



