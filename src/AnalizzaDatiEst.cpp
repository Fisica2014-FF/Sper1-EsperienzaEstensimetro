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

/////////////////////////////////////////////////////////////////////////////////////
//le mie classi
#include "mylib/AnalisiDati/VarStat.h"//Le mie classi Template per l'analisi dati
#include "mylib/AnalisiDati/SortingVarStat.h"//Le mie classi Template per l'analisi dati

#define VERSIONE 1.0

/////////////////////////////////////////////////////////////////////////////////////
//Prototipi

/////////////////////////////////////////////////////////////////////////////////////
//Il primo argomento è la cartella dei dati
int main(int numParam, char* args[]) {
using namespace std;
	try{
		const int DATO = 0;

		using FileDati = mions::dataAnalisi::File_Fdat<double>;
		FileDati fileDati("./DatiFormattati/E13_andata.fdat");

		//Stampa i metadati
		cout << "Stampa i metadati:\n";
		for(pair<string,double> meta : fileDati.MetaDatiGenerici){
			cout << meta.first << " = " << meta.second << endl;
		}

		cout << "\nStampa i dati:\n";
		for(vector<double> riga : fileDati.vColDati){
			for (double dato : riga) {
				cout << dato << " ";
			}
			cout << endl;
		}

		cout << "\nTest Vari:\n";
		cout << "fileDati[3]: " << fileDati[3][DATO] << endl;
		cout << "fileDati[DIAMETRO]: " << fileDati["DIAMETRO"] << endl;
		cout << "fileDati[indice che non esiste]: " << fileDati["ciao"];

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



