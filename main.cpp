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

void buscarEnTransmisiones(string transmission, string mcode) {
	string cadena = transmission;
	string patron = mcode;
	int localizaciones[cadena.size()];
	int indice;

	kmp(cadena, patron, localizaciones, indice);

	if (indice == 0) {
		cout << "FALSE" << " / " << transmission << " NO CONTIENE EL CODIGO DE " << mcode << " EN NINGUNA POSICION." << endl;
	} else if (indice == 1) {
		cout << "TRUE" << " / " << transmission << " CONTIENE EL CODIGO DE " << mcode << " EN LA POSICION " << localizaciones[0] << "." << endl;
	} else {
		cout << "TRUE" << " / " << transmission << " CONTIENE EL CODIGO DE " << mcode << " EN LAS POSICIONES ";

		for (int i = 0; i < indice; i++) {
			if ((i+1) < indice) {
				cout << localizaciones[i] << " ";
			} else {
        cout << localizaciones[i] << "." << endl;
      }
		}
	}
}

int main() {

	string transmission1 = archivoAString("transmission1.txt");
	string transmission2 = archivoAString("transmission2.txt");
	string mcode1 = archivoAString("mcode1.txt");
	string mcode2 = archivoAString("mcode2.txt");
	string mcode3 = archivoAString("mcode3.txt");

	cout << "INICIA PROGRAMA" << endl;
	espacio();
	cout << "Busqueda de codigo malicioso en transmisiones: " << endl;
	espacio();
	cout << "Posible codigo malicioso en cada transmision: " << endl;
	espacio();
	cout << "Datos comunes en transmisiones: " << endl;
	espacio();
	cout << "TERMINA PROGRAMA" << endl;
	return 0;
}