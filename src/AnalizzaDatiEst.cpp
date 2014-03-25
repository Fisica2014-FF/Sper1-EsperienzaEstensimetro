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


//		NomeDiFile testnomefile1("./ciao/Darth.vader");
//		cout << testnomefile1 << endl;
//
//		NomeDiFile testnomefile2("./ciao/Darth");
//		cout << testnomefile2 << endl;
//
//		NomeDiFile testnomefile3("Darth.vader");
//		cout << testnomefile3 << endl;
//
//		NomeDiFile testnomefile4("/ciao/vader");
//		cout << testnomefile4 << endl;
//
//		return 0;
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


		using mions::utils::NomeDiFile;
		using FileDati = mions::dataAnalisi::File_Fdat<double>;
		using vs = mions::dataAnalisi::VarStat<double>;
		//Dovrebbe essere un varstat
		FileDati kDegliEstensimetri(NomeDiFile("./Risultati/YoungEstensimetriGnuplot"));


		/*  In realtà, i dati in sè nei file non servono a molto, perchè vengono analizzati da gnuplot
		 *  Qui contano solo i metadati dei file
		 *
		 *  Prendi un file dalla lista ed estraine le informazioni.
		 */
		while(getline(ListaFileDiDati,stringaNomeFileDiDati)) {

			NomeDiFile nomeDelFileDati(stringaNomeFileDiDati);
			FileDati fileDati(nomeDelFileDati.pathTotale);
			vector<vs> youngacciaio;
			vector<vs> youngtungsteno;
			vector<vs> youngottone;

			//Es da E13_andata.fdat ottengo "E13_andata"
			string nomeEstensimetro = nomeDelFileDati.nome;
			clog << "nomeEstensimetro: " << nomeEstensimetro;
			/*
6.96504311887864 0.0309247031765164
6.98009252738489 0.0381502469618036
4.76664376697682 0.0250656266056032
4.74646140835764 0.0169320622949162
3.91259086359153 0.00987732686648944
3.92183446349384 0.0117728434393252
5.18436398979338 0.0129817798787139
5.19129601775153 0.0143078721525871
5.39413914372792 0.0148159872453062
5.31560751873617 0.0825033158833009
4.47254766407479 0.0153204644390845
4.49111281223576 0.0237828290956587
			 *
			 */

			const vs kappaEstensimetro = vs(kDegliEstensimetri[nomeEstensimetro] , kDegliEstensimetri[string("ERR_") +
			                                                                                          nomeEstensimetro]);

			const vs LUNGHEZZA = vs( fileDati["LUNGHEZZA"], fileDati["ERR_LUNGHEZZA"] );
			const vs AREA = vs( pow(fileDati["DIAMETRO"],2) * M_PI / 4, fileDati["DIAMETRO"] * (M_PI / 4) * fileDati["ERR_DIAMETRO"] );

			switch ( int(fileDati["MATERIALE"]) ) {
				case ACCIAIO:
					//x0 / (A*k2) | k2 = Dx / Df <= beta delle rette
					youngacciaio.push_back( 10e4 * LUNGHEZZA / (AREA * kappaEstensimetro ) );

					break;
				case TUNGSTENO:
					youngtungsteno.push_back( 10e4 * LUNGHEZZA / (AREA * kappaEstensimetro ) );

					break;
				case OTTONE:
					youngottone.push_back( 10e4 * LUNGHEZZA / (AREA * kappaEstensimetro ) );

					break;
				default:
					throw "[Errore]: Errore nello switch";
					break;
			}

			//TODO: L'me par giusto...
			vs sommaacc(0);
			vs sommatung(0);
			vs sommaott(0);
			for (auto myoung : youngacciaio){
				cout << "ACCIAIO myyoung: " << myoung << "";
				sommaacc += myoung;
			}
			cout << "Media acciaio: \n" << sommaacc * (1.0 / 8);
			for (auto myoung : youngtungsteno)
				sommatung += myoung;
			cout << "Media tungsteno: \n" << sommatung * (1.0 / 2);
			for (auto myoung : youngottone)
				sommaott += myoung;
			cout << "Media ottone: \n" << sommaott * (1.0 / 2);
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



