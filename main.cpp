#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void espacio() {
	cout << endl;
}

string archivoAString(string archivoTXT) {
	string line;
	string resultado = "";

	ifstream archivo(archivoTXT);
	while (getline(archivo, line)) {
		resultado += line;
	}
	archivo.close();

	return resultado;
}

void encontrarPrefijo(string patron, int m, int prefijos[]) {
	int longitud = 0;
	prefijos[0] = 0;

	for (int i = 1; i < m; i++) {
		if (patron[i] == patron[longitud]) {
			longitud++;
			prefijos[i] = longitud;
		} else {
			if (longitud != 0) {
				longitud = prefijos[longitud - 1];
				i--;
			} else {
				prefijos[i] = 0;
			}
		}
	}
}

void kmp(
	string cadena,
	string patron,
	int *arregloLocalizaciones,
	int &localizacion) {
	int n;
	int m;
	int i;
	int j;
	n = cadena.size();
	m = patron.size();
	i = 0;
	j = 0;
	int prefijos[m];

	encontrarPrefijo(patron, m, prefijos);

	localizacion = 0;

	while (i < n) {
		if (cadena[i] == patron[j]) {
			i++;
			j++;
		}

		if (j == m) {
			arregloLocalizaciones[localizacion] = i - j;
			localizacion++;
			j = prefijos[j - 1];
		} else if (i < n && patron[j] != cadena[i]) {
			if (j != 0) {
				j = prefijos[j - 1];
			} else {
				i++;
			}
		}
	}
}

string crearSubstring(string cadena, int menor, int mayor) {
	string resultado;
	resultado = "";
	for (int i = menor; i <= mayor; ++i) {
		resultado += cadena[i];
	}
	return resultado;
}

vector<int> lps(string transmission) {
	int n;
	int longitudMaxima;
	int inicio;
	n = transmission.size();
	bool tabla[n][n];

	memset(tabla, 0, sizeof(tabla));

	longitudMaxima = 1;

	for (int i = 0; i < n; ++i) {
		tabla[i][i] = true;
	}

	inicio = 0;

	for (int j = 0; j < n - 1; j++) {
		if (transmission[j] == transmission[j + 1]) {
			tabla[j][j + 1] = true;
			inicio = j;
			longitudMaxima = 2;
		}
	}

	for (int k = 3; k <= n; ++k) {
		for (int i = 0; i < n - k + 1; ++i) {
			int j = i + k - 1;
			if (tabla[i + 1][j - 1] && transmission[i] == transmission[j]) {
				tabla[i][j] = true;
				if (k > longitudMaxima) {
					inicio = i;
					longitudMaxima = k;
				}
			}
		}
	}

	vector<int> vectorDatos;
	vectorDatos.push_back(inicio);
	vectorDatos.push_back(inicio + longitudMaxima - 1);
	return vectorDatos;
}

vector<int> lcs(string transmission1, string transmission2) {
	int n;
	int m;
	int resultado;
	int terminacion;
	int filaActual;
	vector<int> vectorDatos;
	n = transmission1.length();
	m = transmission2.length();
	resultado = 0;
	int filas[2][n + 1];
	filaActual = 0;

	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= n; j++) {
			if (i == 0 || j == 0) {
				filas[filaActual][j] = 0;
			} else if (transmission1[i - 1] == transmission2[j - 1]) {
				filas[filaActual][j] = filas[1 - filaActual][j - 1] + 1;
				if (filas[filaActual][j] > resultado) {
					resultado = filas[filaActual][j];
					terminacion = i - 1;
				}
			} else {
				filas[filaActual][j] = 0;
			}
		}
		filaActual = 1 - filaActual;
	}

	if (resultado == 0) {
		vectorDatos.push_back(-1);
		return vectorDatos;
	}

	vectorDatos.push_back(terminacion - resultado + 1);
	vectorDatos.push_back(resultado);
	return vectorDatos;
}

void buscarEnTransmisiones(string transmission, string mcode) {
	string cadena = archivoAString(transmission);
	string patron = archivoAString(mcode);
	int localizaciones[cadena.size()];
	int indice;

	kmp(cadena, patron, localizaciones, indice);

	if (indice == 0) {
		cout << "FALSE" << " / " << transmission << " NO CONTIENE EL CODIGO DE " << mcode << " EN NINGUNA POSICION." << endl;
	} else if (indice == 1) {
		cout << "TRUE" << " / " << transmission << " CONTIENE EL CODIGO DE " << mcode << " EN LA POSICION " << localizaciones[0] << " [INICIANDO CONTEO DESDE CERO]." << endl;
	} else {
		cout << "TRUE" << " / " << transmission << " CONTIENE EL CODIGO DE " << mcode << " EN LAS POSICIONES ";

		for (int i = 0; i < indice; i++) {
			if ((i + 1) < indice) {
				cout << localizaciones[i] << " ";
			} else {
				cout << localizaciones[i] << " [INICIANDO CONTEO DESDE CERO]."
					 << endl;
			}
		}
	}
}

void posibleCodigoMalicioso(string transmission) {
	string cadena;
	string malicioso;
	vector<int> datosLPS;
	cadena = archivoAString(transmission);
	malicioso = "";
	datosLPS = lps(cadena);

	if (cadena != "") {
		malicioso = crearSubstring(cadena, datosLPS[0], datosLPS[1]);
	}

	if (malicioso == "" || (malicioso.length()) == 1) {
		cout << "EN " << transmission
			 << " NO SE PRESENTA CODIGO MALICIOSO." << endl;
	} else {
		cout << "DE " << datosLPS[0] + 1 << " A " << datosLPS[1] + 1
			 << " [INICIANDO CONTEO DESDE UNO] EN " << transmission
			 << " SE ENCUENTRA CODIGO MALICIOSO." << endl;
	}
}

void buscarDatosComunes(string transmission1, string transmission2) {
	string cadena1;
	string cadena2;
	string resultado;
	string archivoDominante;
	string archivoSecundario;
	vector<int> datosLCS;
	cadena1 = archivoAString(transmission1);
	cadena2 = archivoAString(transmission2);

	if ((cadena1.size()) > (cadena2.size())) {
		datosLCS = lcs(cadena1, cadena2);
		resultado = cadena1.substr(datosLCS[0], datosLCS[1]);
		archivoDominante = transmission1;
		archivoSecundario = transmission2;
	} else if ((cadena1.size()) < (cadena2.size())) {
		datosLCS = lcs(cadena2, cadena1);
		resultado = cadena2.substr(datosLCS[0], datosLCS[1]);
		archivoDominante = transmission2;
		archivoSecundario = transmission1;
	} else {
		datosLCS = lcs(cadena1, cadena2);
		resultado = cadena1.substr(datosLCS[0], datosLCS[1]);
		archivoDominante = transmission1;
		archivoSecundario = transmission2;
	}

	if (datosLCS[0] == -1) {
		cout << "ENTRE " << archivoDominante << " Y " << archivoSecundario << " NO SE ENCUENTRAN DATOS COMUNES." << endl;
	} else {
		cout << "DE " << datosLCS[0] + 1 << " A " << datosLCS[1] + datosLCS[0] << " DE " << archivoDominante << " [INICIANDO CONTEO DESDE UNO], EXISTE TAMBIEN EN " << archivoSecundario << ", TENIENDO DATOS EN COMUN." << endl;
	}
}

int main() {

	cout << "---------- INICIA PROGRAMA ----------" << endl;
	espacio();
	cout << "---------- Busqueda de codigo malicioso en transmisiones: ----------" << endl;
	espacio();
	/*
	buscarEnTransmisiones("transmission1.txt","mcode1.txt");
	buscarEnTransmisiones("transmission1.txt","mcode2.txt");
	buscarEnTransmisiones("transmission1.txt","mcode3.txt");
	buscarEnTransmisiones("transmission2.txt","mcode1.txt");
	buscarEnTransmisiones("transmission2.txt","mcode2.txt");
	buscarEnTransmisiones("transmission2.txt","mcode3.txt");
	*/
	buscarEnTransmisiones("input.txt", "mc1.txt"); //Prueba 1
	espacio();
	cout << "---------- Posible codigo malicioso en cada transmision: ----------" << endl;
	espacio();
	/*
	posibleCodigoMalicioso("transmission1.txt");
	posibleCodigoMalicioso("transmission2.txt");
	*/
	posibleCodigoMalicioso("in1.txt"); //Prueba 2
	espacio();
	cout << "---------- Datos comunes en transmisiones: ----------" << endl;
	espacio();
	/*
	buscarDatosComunes("transmission1.txt","transmission2.txt");
	*/
	buscarDatosComunes("ip1.txt", "ip2.txt"); //Prueba 3
	espacio();
	cout << "---------- TERMINA PROGRAMA ----------" << endl;
	return 0;
}