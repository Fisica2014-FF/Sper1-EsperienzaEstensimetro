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

	system("clear");
	cout << "\n";
	cout << "Programma per analizzare i dati della guidovia, versione: " << VERSIONE << endl;
	//Ricordarsi che con 0 gradi l'intervallo era di 20!
	const int NUM_FILE = 7;// 7 file (7 intervalli) per 15, 30, 45 gradi
	const int NUM_FILE_0GRADI = 6; //  file per 60,70,80,90,100,110
	const int NUM_DATIPERFILE = 5;// 5 dati in ogni file
	const int ANGOLI_NUM = 3;//15, 30, 45 0 e 45 li facciamo a parte
	//const auto INTERVALLO = VarStat<double>(0.1, 0.001 / sqrt(6));//Distribuzione triangolare

	try {
		//stringstream ss;
		string nf;//Nome file da aprire
		//FileStream
		ofstream FileMedie;//FileStream
		ofstream FileRiassunto;
		using namespace mions::dataAnalisi;
		vector<VarStat<double> > arrayRiassunti;//Contiene le informazioni come la deviazione standard, etc
		vector<VarStat<double> > arrayTempi;
		arrayRiassunti.reserve(NUM_FILE);
		const auto INTERVALLO_PV = VarStat<double>(0.1, 0.001 / sqrt(6));//Distribuzione triangolare

//		vector<double> v1 = {1,1,1,100000,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,3,4,2,1,3,2};
//
//		vector<double> v2 = {3,4,7,8};
//		vector<double> v3 = {1,2,5,6};
//		VarStat<double> var2(v2,true);
//		VarStat<double> var3(v3,true);
//
//		VarStat<double> AnDat(v2,true);
//		//Sorting_VarStat<double> var2(std::move(v3));//Non usare più v1
//		//cout << "MEDIANA " <<var2.getMediana() << "\n";
//		AnDat = (AnDat-var2)/(AnDat*3*var2);
//		cout << "var2: \n" << var2 << endl;
//		cout << "var3: \n" << var3 << endl;
//		cout << "somma elementi: \n" << VarStat<double>({4,6,12,14}) << endl;
//		cout << "somma variabili: \n" << (var2+var3) << endl;
//
//		return 0;


//Prima esperianza, guidovia inclinata a 15, 30 e 45 gradi senza peso
///////////////////////////////////////////////////////////////////////////////////////////////////
		{

		//stringstream ss;
		string nf;//Nome file da aprire
		//FileStream
		ofstream FileMedie;//FileStream
		ofstream FileRiassunto;
		ofstream FileVelocita;
		using namespace mions::dataAnalisi;
		vector<VarStat<double> > arrayRiassunti;//Contiene le informazioni come la deviazione standard, etc
		vector<VarStat<double> > arrayTempi;

		arrayRiassunti.reserve(NUM_FILE);
		string nomeoutputfile;
		string nomefilemedie;
		string nomefilevelocita;
		string nomeoutputvelocita;//Per tenere temporaneamente la variabile ed evitare il self assignment

		/* Vari casi:
		 * 	1. nè peso nè alluminio
		 */
		string tipodati;
				nomeoutputfile = "./Risultati/normale_dati.txt";
				//tipodati = "d";
				nomefilemedie = "arrayTempi_PrimaVolta_normale.txt";
				nomefilevelocita = "velocita_PV_normale.txt";//PV = prima volta

		FileRiassunto.open(nomeoutputfile.c_str());

		for (int angoli = 1; angoli <= ANGOLI_NUM; angoli++) {
			//TODO aggiunto zero all'inizio
			arrayTempi.emplace_back(0.0);

			for (int intervallo = 1; intervallo <= NUM_FILE; intervallo++) {

				stringstream ss;
				ifstream FileImputDati;//File di imput
				ss << "./DatiFormattati/DatiStandardizzati/";
				ss << "d";//Tipo dei dati contenuti nel file: d, cd
				ss << intervallo*10 + 40;
				ss << "_";
				ss << angoli*15;
				ss >> nf;
				//ss.flush();


				clog << nf << endl;
				FileImputDati.open(nf.c_str());//Apro il file indicato nell'argomento dato via shell
				if (!FileImputDati.is_open())
					throw "Errore: file non aperto";

				vector<double> tempVect(5);// Vector che contiene i dati di un file solo, da cui ricavare il tempo medio
				tempVect.reserve(NUM_DATIPERFILE);

				clog << tempVect.size() << endl;
				for (unsigned int i = 0; i < tempVect.size(); i++) {
					FileImputDati >> tempVect[i];
					clog << "Pos " << i << ": " << tempVect[i] << endl;
				}
				clog << "Dati letti. Analizzo..." << endl << endl;

				arrayRiassunti.emplace_back(tempVect,true);// Forwarda gli argomenti a un oggetto costruito DIRETTAMENTE nel vettore (cioè, manda gli argomenti VarStat dentro al vettore)

				cout << endl;
				cout << "Nome file: " << nf << endl;
				cout << arrayRiassunti.back();

				FileRiassunto << endl;
				FileRiassunto << "Nome file: " << nf << endl;
				FileRiassunto << arrayRiassunti.back() << endl;

				arrayTempi.emplace_back(arrayRiassunti.back());

				ss.clear();
				FileImputDati.close();
			}//Intervalli


			switch (angoli) {
				case 1:
					//Ricicliamo nomeoutputfile per indicare i file di uscita
					nomeoutputfile = string("./Risultati/MetaDati/15/") + nomefilemedie;
					nomeoutputvelocita = string("./Risultati/MetaDati/15/") + nomefilevelocita;
					FileMedie.open(nomeoutputfile.c_str());
					FileVelocita.open(nomeoutputvelocita.c_str());
					//const auto intervallo = VarStat<double>(0.1, 0.1 / sqrt(6));
					for (int i = 0; i < NUM_FILE; i++)
					{
						FileMedie << ((arrayTempi[i+1]+arrayTempi[i])/2).getMedia() << endl;//sette medie di cinque tempi ciascuns
						FileVelocita << (INTERVALLO_PV / (arrayTempi[i+1] - arrayTempi[i]) ).getMedia() << " "
								<< (INTERVALLO_PV / (arrayTempi[i+1] - arrayTempi[i]) ).getDeviazioneStandardPop() << endl;//10 cm di intervallo/cinque_tempi_media << endl;//10 cm di intervallo
					}
					FileMedie.close();
					FileVelocita.close();
					break;
				case 2:
					//Ricicliamo nomeoutputfile per indicare i file di uscita
					nomeoutputfile = string("./Risultati/MetaDati/30/") + nomefilemedie;
					nomeoutputvelocita = string("./Risultati/MetaDati/30/") + nomefilevelocita;
					FileMedie.open(nomeoutputfile.c_str());
					FileVelocita.open(nomeoutputvelocita.c_str());
					for (int i = 0; i < NUM_FILE; i++)
					{
						FileMedie << ( (arrayTempi[i+1] + arrayTempi[i]) / 2 ).getMedia() << endl;//sette medie di cinque tempi ciascuns
						FileVelocita << (INTERVALLO_PV / (arrayTempi[i+1] - arrayTempi[i]) ).getMedia() << " "
								<< (INTERVALLO_PV / (arrayTempi[i+1] - arrayTempi[i]) ).getDeviazioneStandardPop() << endl;//10 cm di intervallo/cinque_tempi_media << endl;//10 cm di intervallo
					}
					FileMedie.close();
					FileVelocita.close();
					break;
				case 3:
					//Ricicliamo nomeoutputfile per indicare i file di uscita
					nomeoutputfile = string("./Risultati/MetaDati/45/") + nomefilemedie;
					nomeoutputvelocita = string("./Risultati/MetaDati/45/") + nomefilevelocita;
					FileMedie.open(nomeoutputfile.c_str());
					FileVelocita.open(nomeoutputvelocita.c_str());
					for (int i = 0; i < NUM_FILE; i++)
					{
						FileMedie << ((arrayTempi[i+1]+arrayTempi[i])/2).getMedia() << endl;//sette medie di cinque tempi ciascuns
						FileVelocita << (INTERVALLO_PV / (arrayTempi[i+1] - arrayTempi[i]) ).getMedia() << " "
								<< (INTERVALLO_PV / (arrayTempi[i+1] - arrayTempi[i]) ).getDeviazioneStandardPop() << endl;//10 cm di intervallo/cinque_tempi_media << endl;//10 cm di intervallo
					}
					FileMedie.close();
					FileVelocita.close();
					break;
				default:
					throw "Errore: numero casi angoli sbagliato";
					break;
			}//switch
			arrayTempi.clear();
		}//Angoli

		FileRiassunto.close();
		arrayRiassunti.clear();
	  }//Blocco prima esperienza senza peso
///////////////////////////////////////////////////////////////////////////////////////////////////










//Prima esperianza, guidovia inclinata a 45 con peso
///////////////////////////////////////////////////////////////////////////////////////////////////
		/*
		 * Vari casi:
		 * 	1. nè peso nè alluminio
		 * 	2. peso
		 */
//for (int varicasi = 1; varicasi <= 2; varicasi++)
		{

			string nf;						// Nome file
			ofstream FileMedie;				// File con le medie dei tempi
			ofstream FileRiassunto;			// File con le informazioni sulle cinquine di dati
			ofstream FileVelocita;
			using namespace mions::dataAnalisi;
			vector<VarStat<double> > arrayRiassunti;//Contiene le informazioni come la deviazione standard, etc
			vector<VarStat<double> > arrayTempi;
			//TODO aggiunto zero all'inizio
			arrayTempi.emplace_back(0.0);

			arrayRiassunti.reserve(NUM_FILE);
			string nomeoutputfile;
			string nomefilemedie;
			string nomefilevelocita;
			string nomeoutputvelocita;


				string tipodati;
				nomeoutputfile = "./Risultati/peso_dati.txt";
				tipodati = "cd";
				nomefilemedie = "arrayTempi_PrimaVolta_peso.txt";
				nomefilevelocita = "velocita_PV_peso.txt";


			//string nomeoutputfile = "./Risultati/nopeso_dati.txt";
			FileRiassunto.open(nomeoutputfile.c_str());
				for (int intervallo = 1; intervallo <= NUM_FILE; intervallo++) {

					stringstream ss;
					ifstream FileImputDati;					//File di imput
					ss << "./DatiFormattati/DatiStandardizzati/";
					ss << tipodati;	//Tipo dei dati contenuti nel file: d, cd
					ss << intervallo * 10 + 40;
					ss << "_";
					ss << "45";
					ss >> nf;
					//ss.flush();

					clog << nf << endl;
					FileImputDati.open(nf.c_str());	//Apro il file indicato nell'argomento dato via shell
					if (!FileImputDati.is_open())
						throw "Errore: file non aperto";

					vector<double> tempVect(5);	// Vector che contiene i dati di un file solo, da cui ricavare il tempo medio
					tempVect.reserve(NUM_DATIPERFILE);

					clog << tempVect.size() << endl;
					for (unsigned int i = 0; i < tempVect.size(); i++) {
						FileImputDati >> tempVect[i];
						clog << "Pos " << i << ": " << tempVect[i] << endl;
					}
					clog << "Dati letti. Analizzo..." << endl << endl;

					arrayRiassunti.emplace_back(tempVect, true);// Forwarda gli argomenti a un oggetto costruito DIRETTAMENTE nel vettore (cioè, manda gli argomenti VarStat dentro al vettore)

					cout << endl;
					cout << "Nome file: " << nf << endl;
					cout << arrayRiassunti.back();

					FileRiassunto << endl;
					FileRiassunto << "Nome file: " << nf << endl;
					FileRiassunto << arrayRiassunti.back() << endl;

					arrayTempi.emplace_back(arrayRiassunti.back());

					ss.clear();
					FileImputDati.close();
				}//Intervalli

				//Ex switch
					//Ricicliamo nomeoutputfile per indicare i file di uscita
					nomeoutputfile = string("./Risultati/MetaDati/45/")
							+ nomefilemedie;
					nomeoutputvelocita = string("./Risultati/MetaDati/45/")
							+ nomefilevelocita;
					FileMedie.open(nomeoutputfile.c_str());
					FileVelocita.open(nomeoutputvelocita.c_str());
					for (int i = 0; i < NUM_FILE; i++)
					{
						FileMedie << ((arrayTempi[i+1]+arrayTempi[i])/2).getMedia() << endl;//sette medie di cinque tempi ciascuns
						FileVelocita << (INTERVALLO_PV / (arrayTempi[i+1] - arrayTempi[i]) ).getMedia() << " "
								<< (INTERVALLO_PV / (arrayTempi[i+1] - arrayTempi[i]) ).getDeviazioneStandardPop() << endl;//10 cm di intervallo/cinque_tempi_media << endl;//10 cm di intervallo
					}
					FileMedie.close();
					FileVelocita.close();

			arrayTempi.clear();

			FileRiassunto.close();
			arrayRiassunti.clear();
		}					//Blocco prima esperienza 45 con peso
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////















//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Seconda giornata %
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//Seconda esperienza, 0 gradi con alluminio e peso
		/* Vari casi:
		 * 	1. nè peso nè alluminio (file "d...")
		 * 	2. peso (file "cd...")
		 * 	4. alluminio
		 * 	3. peso e alluminio ("cad...")
		 */
		for (int varicasi = 1; varicasi <= 4; varicasi++)
		{
			string nf;						//Nome file da aprire
			ofstream FileMedie;				//File per le medie
			ofstream FileRiassunto;
			ofstream FileVelocita;
			using namespace mions::dataAnalisi;
			vector<VarStat<double> > arrayRiassunti;//Contiene le informazioni come la deviazione standard, etc
			vector<VarStat<double> > arrayTempi;//Niente zero perchè non devo dividere per la differenza
			arrayRiassunti.reserve(NUM_FILE);
			string nomeoutputfile;
			string nomefilemedie;
			string nomefilevelocita;
			string nomeoutputvelocita;
			const auto INTERVALLO_SV = VarStat<double>(0.2, 0.001 / sqrt(6));//Distribuzione triangolare


			/* Vari casi:
			 * 	1. nè peso nè alluminio (file "d...")
			 * 	2. peso (file "cd...")
			 * 	4. alluminio
			 * 	3. peso e alluminio ("cad...")
			 */
			string tipodati;
			switch (varicasi) {
				case 1: // normale
					nomeoutputfile = "./Risultati/normale_0gradi_dati.txt";
					tipodati = "d";
					nomefilemedie = "arrayTempi_0gradi_normale.txt";
					nomefilevelocita = "velocita_0gradi_normale.txt";
					break;
				case 2: // peso
					nomeoutputfile = "./Risultati/peso_0gradi_dati.txt";
					tipodati = "cd";
					nomefilemedie = "arrayTempi_0gradi_peso.txt";
					nomefilevelocita = "velocita_0gradi_peso.txt";
					break;
				case 3: // alluminio
					nomeoutputfile = "./Risultati/alluminio_0gradi_dati.txt";
					tipodati = "ad";
					nomefilemedie = "arrayTempi_0gradi_alluminio.txt";
					nomefilevelocita = "velocita_0gradi_alluminio.txt";
					break;
				case 4: // normale
					nomeoutputfile = "./Risultati/pesoalluminio_0gradi_dati.txt";
					tipodati = "cad";
					nomefilemedie = "arrayTempi_0gradi_pesoalluminio.txt";
					nomefilevelocita = "velocita_0gradi_pesoalluminio.txt";
					break;
				default:
					throw "Errore: Seconda esperienza: variante non nota";
					break;
			}

			FileRiassunto.open(nomeoutputfile.c_str());

			for (int intervallo = 1; intervallo <=  NUM_FILE_0GRADI; intervallo++) {
				stringstream ss;
				ifstream FileImputDati;					//File di input
				ss << "./DatiFormattati/DatiStandardizzati/";
				ss << tipodati;	//Tipo dei dati contenuti nel file: d, cd, ad, cad
				ss << intervallo * 10 + 50;
				ss << "_";
				ss << "0";
				ss >> nf;
				//ss.flush();

				clog << nf << endl;
				FileImputDati.open(nf.c_str());	//Apro il file indicato nell'argomento dato via shell
				if (!FileImputDati.is_open())
					throw "Errore: file non aperto";

				vector<double> tempVect(5);	// Vector che contiene i dati di un file solo, da cui ricavare il tempo medio
				tempVect.reserve(NUM_DATIPERFILE);

				clog << tempVect.size() << endl;
				for (unsigned int i = 0; i < tempVect.size(); i++) {
					FileImputDati >> tempVect[i];
					clog << "Pos " << i << ": " << tempVect[i] << endl;
				}
				clog << "Dati letti. Analizzo..." << endl << endl;

				arrayRiassunti.emplace_back(tempVect, true);// Forwarda gli argomenti a un oggetto costruito DIRETTAMENTE nel vettore (cioè, manda gli argomenti VarStat dentro al vettore)

				cout << endl;
				cout << "Nome file: " << nf << endl;
				cout << arrayRiassunti.back();

				FileRiassunto << endl;
				FileRiassunto << "Nome file: " << nf << endl;
				FileRiassunto << arrayRiassunti.back() << endl;

				arrayTempi.emplace_back(arrayRiassunti.back());

				ss.clear();
				FileImputDati.close();
			}					//Intervalli

			//Ex switch
				//Ricicliamo nomeoutputfile per indicare i file di uscita
				nomeoutputfile = string("./Risultati/MetaDati/0/")
						+ nomefilemedie;//Nomefilemedie scelto all'inizio nello switch
				nomeoutputvelocita = string("./Risultati/MetaDati/0/")
						+ nomefilevelocita;//Idem per nomefilevelocita
				FileMedie.open(nomeoutputfile.c_str());
				FileVelocita.open(nomeoutputvelocita.c_str());
				for (int i = 0; i < NUM_FILE_0GRADI; i++)
				{
					FileMedie << ((arrayTempi[i+1]+arrayTempi[i])/2).getMedia() << endl;//sette medie di cinque tempi ciascuns
					FileVelocita << (INTERVALLO_SV / arrayTempi[i]).getMedia() << " "
							<< (INTERVALLO_SV / arrayTempi[i]).getDeviazioneStandardPop() << endl;//10 cm di intervallo/cinque_tempi_media << endl;//10 cm di intervallo
				}
				FileMedie.close();
				FileVelocita.close();

		arrayTempi.clear();
		FileRiassunto.close();
		arrayRiassunti.clear();

		}
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////










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



