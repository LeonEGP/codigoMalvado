#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
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
  vectorDatos.push_back(inicio+longitudMaxima-1);
	return vectorDatos;
}

void buscarEnTransmisiones(string transmission, string mcode) {
	string cadena = archivoAString(transmission);
	string patron = archivoAString(mcode);
	int localizaciones[cadena.size()];
	int indice;

	kmp(cadena, patron, localizaciones, indice);

	if (indice == 0) {
		cout << "FALSE"
			 << " / " << transmission << " NO CONTIENE EL CODIGO DE " << mcode
			 << " EN NINGUNA POSICION." << endl;
	} else if (indice == 1) {
		cout << "TRUE"
			 << " / " << transmission << " CONTIENE EL CODIGO DE " << mcode
			 << " EN LA POSICION " << localizaciones[0] << "." << endl;
	} else {
		cout << "TRUE"
			 << " / " << transmission << " CONTIENE EL CODIGO DE " << mcode
			 << " EN LAS POSICIONES ";

		for (int i = 0; i < indice; i++) {
			if ((i + 1) < indice) {
				cout << localizaciones[i] << " ";
			} else {
				cout << localizaciones[i] << "." << endl;
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

  if (cadena != ""){
    malicioso = crearSubstring(cadena, datosLPS[0], datosLPS[1]);  
  }

  if(malicioso == "" || (malicioso.length())==1){
    cout << "EN " << transmission << " NO SE PRESENTA POSIBLE CODIGO MALICIOSO."<< endl;
  } else {
    cout << "DE " << datosLPS[0]+1 << " A " << datosLPS[1]+1 << " [INICIANDO CONTEO DESDE UNO] EN " << transmission << " SE ENCUENTRA POSIBLE CODIGO MALICIOSO."<< endl;
  }
  
}

int main() {

	cout << "---------- INICIA PROGRAMA ----------" << endl;
	espacio();
	cout << "---------- Busqueda de codigo malicioso en transmisiones: ----------" << endl;
	espacio();
	buscarEnTransmisiones("transmission1.txt","mcode1.txt");
	buscarEnTransmisiones("transmission1.txt","mcode2.txt");
	buscarEnTransmisiones("transmission1.txt","mcode3.txt");
	buscarEnTransmisiones("transmission2.txt","mcode1.txt");
	buscarEnTransmisiones("transmission2.txt","mcode2.txt");
	buscarEnTransmisiones("transmission2.txt","mcode3.txt");
	espacio();
	cout << "---------- Posible codigo malicioso en cada transmision: ----------" << endl;
	espacio();
	posibleCodigoMalicioso("transmission1.txt");
	posibleCodigoMalicioso("transmission2.txt");
	espacio();
	cout << "---------- Datos comunes en transmisiones: ----------" << endl;
	espacio();
	espacio();
	cout << "---------- TERMINA PROGRAMA ----------" << endl;
	return 0;
}