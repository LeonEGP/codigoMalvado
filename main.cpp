#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void espacio(){
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

void encontrarPrefijo(string patron, int m, int prefijos[]){
	int longitud = 0;
	prefijos[0] = 0;

	for(int i = 1; i < m; i++){
		if(patron[i] == patron[longitud]){
			longitud++;
			prefijos[i] = longitud;
		} else {
			if (longitud != 0){
				longitud = prefijos[longitud-1];
				i--;
			} else{
				prefijos[i ]= 0;
			}
		}
	}
}

void buscarEnTransmisiones(string transmission, string mcode){
	int localizaciones[transmission.size()];
	int indice;
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