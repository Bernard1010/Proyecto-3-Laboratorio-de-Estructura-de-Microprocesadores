#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <libusb-1.0/libusb.h>

using namespace std;


/*
Usando la funcion de la libreria stdlib.h, system("comando de linux"), se utilizan los comandos de la terminal de 
* Linux para realizar cualquier tipo de manipulacion de archivos, por ende se necesitan crear strings con las direcciones,
*comandos y nombres de archivos para luego concatenar el comando completo y ejecutarlo realizando la funcion completa.
comando de compilacion: g++ nombre.cpp -o nombreout 

*/

string ls("ls ");								//comando para ver archivos del directorio en que se este dentro
string dir1("Descargas");						//directorio
string dir2("Documentos/rar");					//directorio + nombre de archivo de salida
string destino(">");							//signo para crear un archivo de texto



int main() 
{

	
	string fun=ls + dir1 + destino + dir2;
	char *cstr = new char[fun.length() + 1];
	strcpy(cstr, fun.c_str());
	system(cstr);
	cout<<"\n";
	cin.get();
	return 0;
}
