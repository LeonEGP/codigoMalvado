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

int main() {

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