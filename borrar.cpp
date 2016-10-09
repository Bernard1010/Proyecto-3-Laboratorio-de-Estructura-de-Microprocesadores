#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>


using namespace std;


FILE *archer;																		//variable del nombre del dispositivo de almacenamiento usb fuente
string dirbase("cd /home/sergio && ");													//ruta a directorios base												
string ls(" ls ");		
string rm (" rm -R ");	   														    //comando para eliminar carpeta
string dir1("/prueba");																//directorio de archivos para el proyecto*** Carpeta necesaria dentro de documentos
string comando;
string comando2;																			//variable de comando de ejecucion 												
string Documentos("/home/sergio/Documentos");											//ruta a directorio de documentos
char  Documentoss[50]="/home/sergio/Documentos";

//--------------------------------FUNCIONES------------------------

int borrar() 
{	

	comando = dirbase+ls;
	char *cstr1 = new char[comando.length() + 1];
	strcpy(cstr1, comando.c_str());
	system(cstr1);	
	
	comando2 = rm+Documentos+dir1;
	char *cstr2 = new char[comando.length() + 1];
	strcpy(cstr2, comando2.c_str());
	system(cstr2);
	
	system(cstr1);	
	
	return 0;
}


int main ()
{
	borrar();
	printf("se borro la carpeta con exito");
	return 0;
}
