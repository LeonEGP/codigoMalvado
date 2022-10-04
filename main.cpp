//Programa que: Implementa diferentes algoritmos sobre strings: KMP, LPS, LCS.
//Programadores: León Emiliano García Pérez [A00573074] y Carla Morales López [A01639225].
//Fecha de entrega: Martes 04 de Octubre de 2022.

//Inclusión de librerías.
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

//Ajste a estandar.
using namespace std;

//Función que imprime un espacio en consola, no recibe valores, no tiene valor de retorno.
void espacio() { //Complejidad Computacional: O(1), es ejecución una lineal del contenido de la función. 
	cout << endl;
}

//Función que convierte un archivo de texto a un string, recibe el string con el nombre del archivo, retorna el string del contenido.
string archivoAString(string archivoTXT) { //Complejidad Computacional: O(n), siendo n la longitud del archivo a analizar.
	string line;
	string resultado = "";

	ifstream archivo(archivoTXT);
	while (getline(archivo, line)) { //Complejidad Computacional: O(n), siendo n la longitud del archivo a analizar.
		resultado += line;
	}
	archivo.close();

	return resultado;
}

//Función auxiliar del Algoritmo KMP que ayuda a encontrar un Prefijo, recibe el patrón en string, su tamaño en un entero m, y un arreglo de entero con los prefijos, no tiene valor de retorno.
void encontrarPrefijo(string patron, int m, int prefijos[]) { //Complejidad Computacional: O(m-1), que pasa a ser O(m), siendo m el tamaño del substring que se pasa por parámetro. [Siendo este string el patrón a buscar con KMP].
	int longitud = 0;
	prefijos[0] = 0;

	for (int i = 1; i < m; i++) { //Complejidad Computacional: O(m-1) [Que pasa a ser O(m)], siendo m el tamaño del substring que se pasa por parámetro.
		if (patron[i] == patron[longitud]) {
			longitud++;
			prefijos[i] = longitud;
		}
		else {
			if (longitud != 0) {
				longitud = prefijos[longitud - 1];
				i--;
			}
			else {
				prefijos[i] = 0;
			}
		}
	}
}

//Función que implementa el algoritmo KMP, recibe el string base, el string de búsqueda, un entero apuntado que puede recibir el arreglo de localizaciones, y un entero referenciado, no tiene valor de retorno.
void kmp(string cadena, string patron, int* arregloLocalizaciones, int& localizacion) { //Complejidad Computacional: O(m(n-m+1)), semejante a O(m(n-m)), y con Complejidad de Bibliografía simplificada pasa a O(n), siendo el tamaño del string base.
	int n;
	int m;
	int i;
	int j;
	n = cadena.size();
	m = patron.size();
	i = 0;
	j = 0;
	int prefijos[m];

	encontrarPrefijo(patron, m, prefijos); //Complejidad Computacional: O(m), siendo m el tamaño del substring que se pasa por parámetro. [Siendo este string el patrón a buscar con KMP].

	localizacion = 0;

	while (i < n) { //Complejidad Computacional: O(n), siendo n el tamaño del string base.
		if (cadena[i] == patron[j]) {
			i++;
			j++;
		}

		if (j == m) {
			arregloLocalizaciones[localizacion] = i - j;
			localizacion++;
			j = prefijos[j - 1];
		}
		else if (i < n && patron[j] != cadena[i]) {
			if (j != 0) {
				j = prefijos[j - 1];
			}
			else {
				i++;
			}
		}
	}
}

//Función auxiliar del Algoritmo LPS que crea un substring, recibe el string base, el índice entero menor, y el índice entero mayor. Retorna el string con el substring.
string crearSubstring(string cadena, int menor, int mayor) { //Complejidad Computacional O(m-n), siendo n el entero mayor y n el entero menor.
	string resultado;
	resultado = "";
	for (int i = menor; i <= mayor; ++i) { //Complejidad Computacional O(m-n), siendo n el entero mayor y n el entero menor.
		resultado += cadena[i];
	}
	return resultado;
}

//Algoritmo que implementa el Algoritmo LPS, recibe un string a analizar, y retorna un vector de enteros con el indice inicial y final del string con LPS.
vector<int> lps(string transmission) { //Complejidad Computacional O(n^2) [Fundamentándose en Bibliografía], siendo n el tamaño del string.
	int n;
	int longitudMaxima;
	int inicio;
	n = transmission.size();
	bool tabla[n][n];

	memset(tabla, 0, sizeof(tabla));
	longitudMaxima = 1;

	for (int i = 0; i < n; ++i) { //Complejidad Computacional O(n), siendo n el tamaño del string.
		tabla[i][i] = true;
	}

	inicio = 0;

	for (int j = 0; j < n - 1; j++) { //Complejidad Computacional O(n-1) [Que pasa a ser O(n)], siendo n el tamaño del string.
		if (transmission[j] == transmission[j + 1]) {
			tabla[j][j + 1] = true;
			inicio = j;
			longitudMaxima = 2;
		}
	}

	for (int k = 3; k <= n; ++k) { //Complejidad Computacional O(n-2) [Que pasa a ser O(n)], siendo n el tamaño del string.
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

//Algoritmo que implementa el Algoritmo LCS, recibe un string a analizar y otro string para comparar, retorna un vector de enteros con el índice inicial y final del string con LCS.
vector<int> lcs(string transmission1, string transmission2) { //Complejidad Computacional: O(nm), siendo n y m las longitudes de ambos strings.  
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

	for (int i = 0; i <= m; i++) { //Complejidad Computacional: O(m), siendo m el tamaño del segundo string.
		for (int j = 0; j <= n; j++) { //Complejidad Computacional: O(n), siendo n el tamaño del primer string.
			if (i == 0 || j == 0) {
				filas[filaActual][j] = 0;
			}
			else if (transmission1[i - 1] == transmission2[j - 1]) {
				filas[filaActual][j] = filas[1 - filaActual][j - 1] + 1;
				if (filas[filaActual][j] > resultado) {
					resultado = filas[filaActual][j];
					terminacion = i - 1;
				}
			}
			else {
				filas[filaActual][j] = 0;
			}
		}
		filaActual = 1 - filaActual;
	}

	if (resultado == 0) {
		vectorDatos.push_back(-1);
		vectorDatos.push_back(-1);
		return vectorDatos;
	}

	vectorDatos.push_back(terminacion - resultado + 1);
	vectorDatos.push_back(resultado);
	return vectorDatos;
}

//Función que busca en un string de transmisión un string malicioso [Fundamentado en KMP], recibe ambos strings y no tiene valor de retorno.
void buscarEnTransmisiones(string transmission, string mcode) { //Complejidad Computacional: O(1), es ejecución una lineal del contenido de la función. 
	string cadena = archivoAString(transmission);
	string patron = archivoAString(mcode);
	int localizaciones[cadena.size()];
	int indice;

	kmp(cadena, patron, localizaciones, indice);

	if (indice == 0) {
		cout << "FALSE" << " / " << transmission << " NO CONTIENE EL CODIGO DE " << mcode << " EN NINGUNA POSICION." << endl;
	}
	else if (indice == 1) {
		cout << "TRUE" << " / " << transmission << " CONTIENE EL CODIGO DE " << mcode << " EN LA POSICION " << localizaciones[0] << " [INICIANDO CONTEO DESDE CERO]." << endl;
	}
	else {
		cout << "TRUE" << " / " << transmission << " CONTIENE EL CODIGO DE " << mcode << " EN LAS POSICIONES ";

		for (int i = 0; i < indice; i++) {
			if ((i + 1) < indice) {
				cout << localizaciones[i] << " ";
			}
			else {
				cout << localizaciones[i] << " [INICIANDO CONTEO DESDE CERO]."
					<< endl;
			}
		}
	}
}

//Función que busca en un string de transmisión un posible código palindrómico malicioso [Fundamentado en LPS], recibe dicho string, no tiene valor de retorno.
void posibleCodigoMalicioso(string transmission) { //Complejidad Computacional: O(1), es ejecución una lineal del contenido de la función. 
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
	}
	else {
		cout << "DE " << datosLPS[0] + 1 << " A " << datosLPS[1] + 1
			<< " [INICIANDO CONTEO DESDE UNO] EN " << transmission
			<< " SE ENCUENTRA CODIGO MALICIOSO." << endl;
	}
}

//Función que busca similutudes entre dos strings de tranmisión [Fundamentado en LCS], recibe ambos strings, no tiene valor de retorno.
void buscarDatosComunes(string transmission1, string transmission2) { //Complejidad Computacional: O(1), es ejecución una lineal del contenido de la función. 
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
	}
	else if ((cadena1.size()) < (cadena2.size())) {
		datosLCS = lcs(cadena2, cadena1);
		resultado = cadena2.substr(datosLCS[0], datosLCS[1]);
		archivoDominante = transmission2;
		archivoSecundario = transmission1;
	}
	else {
		datosLCS = lcs(cadena1, cadena2);
		resultado = cadena1.substr(datosLCS[0], datosLCS[1]);
		archivoDominante = transmission1;
		archivoSecundario = transmission2;
	}

	if (datosLCS[0] == -1) {
		cout << "ENTRE " << archivoDominante << " Y " << archivoSecundario << " NO SE ENCUENTRAN DATOS COMUNES." << endl;
	}
	else {
		cout << "DE " << datosLCS[0] + 1 << " A " << datosLCS[1] + datosLCS[0] << " DE " << archivoDominante << " [INICIANDO CONTEO DESDE UNO], EXISTE TAMBIEN EN " << archivoSecundario << ", TENIENDO DATOS EN COMUN." << endl;
	}
}

//Función main de ejecución del programa, no recibe valores, retorna un valor 0 al finalizar la ejecución.
int main() { //Complejidad Computacional: O(1), es ejecución una lineal del contenido de la función. 

	cout << "---------- ¡¡¡INICIA PROGRAMA!!! ----------" << endl;
	espacio();
	cout << "---------- BUSQUEDA DE CIERTOS CODIGOS MALICIOSO EN TRANSMISIONES : ----------" << endl;
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
	cout << "---------- CODIGO MALICIOSO PALINDROMICO EN LAS TRANSMISIONES: ----------" << endl;
	espacio();
	/*
	posibleCodigoMalicioso("transmission1.txt");
	posibleCodigoMalicioso("transmission2.txt");
	*/
	posibleCodigoMalicioso("in1.txt"); //Prueba 2
	espacio();
	cout << "---------- SEMEJANZA ENTRE TRANSMISIONES: ----------" << endl;
	espacio();
	/*
	buscarDatosComunes("transmission1.txt","transmission2.txt");
	*/
	buscarDatosComunes("ip1.txt", "ip2.txt"); //Prueba 3
	espacio();
	cout << "---------- ¡¡¡TERMINA PROGRAMA!!! ----------" << endl;
	return 0;
}