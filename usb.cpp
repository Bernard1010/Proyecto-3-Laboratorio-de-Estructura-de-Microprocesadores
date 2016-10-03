# include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;


/*
Usando la funcion de la libreria stdlib.h, system("comando de linux"), se utilizan los comandos de la terminal de 
* Linux para realizar cualquier tipo de manipulacion de archivos, por ende se necesitan crear strings con las direcciones,
*comandos y nombres de archivos para luego concatenar el comando completo y ejecutarlo realizando la funcion completa.
comando de compilacion: g++ nombre.cpp -o nombreout 

*/

//CONCATENAR STRINGS Y CONVERTIR A CHAR
/*
string ls("ls ");					        //comando para ver archivos del directorio en que se este dentro
string dir1("Descargas");				        //directorio
string dir2("Documentos/rar");					//directorio + nombre de archivo de salida
string destino(">");							//signo para crear un archivo de texto

	string fun=ls + dir1 + destino + dir2;
	char *cstr = new char[fun.length() + 1];
	strcpy(cstr, fun.c_str());
	system(cstr);
*/


////---------------------------VARIABLES------------------

FILE *archer;
char aux[40];
char varusb[60];																		//variable del nombre del dispositivo de almacenamiento usb fuente
string dirbase("cd /home/berni && ");													//ruta a directorios base
string dirusbs(" /media/berni/");														//ruta a directorio de los dispositivos usb conectados
string ls(" ls ");																		//comando para ver archivos del directorio en que se este dentro
string dir1("/Proyecto_3");																//directorio de archivos para el proyecto*** Carpeta necesaria dentro de documentos
string comando;																			//variable de comando de ejecucion 
string usbconectadas("/usbconectadas");													//nombre de archivo con nombre de usb conectada
string archivofuente("/archivosfuente");												//nombre de archivo con nombre de archivos dentro del usb fuente
string destino(">");																	//signo de comando para crear un archivo
string Documentos("/home/berni/Documentos");											//ruta a directorio de documentos

int numarchivos=0;																		//Cantidad de archivos dentro del usb fuente
typedef char Lista[50];


//--------------------------------FUNCIONES------------------------
void DetectarUSBFuente(char *var)
{
	FILE *doc;
	char varaux[40];
	
	comando = dirbase+ls+dirusbs+destino+Documentos+dir1+usbconectadas;
	char *cstr1 = new char[comando.length() + 1];
	strcpy(cstr1, comando.c_str());
	system(cstr1);																		//Usando el comando ls de linux, se crea un archivo donde se guarda el nombre de los dispositivos USB conectados(aparecen dentro del directorio /media/ususario/), el archivo se guarda en  la direccion luego del simbolo >		
	
	
	comando = Documentos+dir1+usbconectadas;
	char *cstr2 = new char[comando.length() + 1];
	strcpy(cstr2, comando.c_str());
	doc = fopen(cstr2,"r");																//abre el archivo desde la direccion
	
	int c=0;
	while(true)																			//entra en el ciclo infinito de comprobacion
	{	
		c++;
		sleep(1);																		// tiempo de refrescamiento
		system(cstr1);																	//refresca los dato del directorio de las usb conectadas
					
		fseek( doc, 0, SEEK_END );														//posiciona el cursor al final de archivo
		if (ftell( doc ) == 0 )															//si es 0 esta vacio el archivo-no usb conectadas
		{	
			if(c==1)
			{
				system("clear");
				printf("ESPERANDO. \n");
			}
			else if(c==2)
			{
				system("clear");
				printf("ESPERANDO.. \n");
			}
			else if(c==3)
			{
				system("clear");
				printf("ESPERANDO... \n");
				c=0;
			}
		
		
		}
				
		
		else{break;}																	//si no esta vacio rompe el ciclo 
	}
   
   rewind(doc);																			//rebobina el archivon con el nombre del usb fuente conectado
   fscanf(doc,"%s",var);																//se adquiere el nombre del usb fuente conectado
   fclose(doc);																			//cierra el archivo																								
	
}


int main() 
{	
	
	DetectarUSBFuente(varusb);															//Se espera el usb fuente
	system("clear");
	printf("Nuevo Dispositivo: %s \n",varusb);
	printf("\n");
	printf("Archivos de: %s \n",varusb);
	
	comando=ls+dirusbs+varusb;															//Por medio del comando ls, se muestra el contenido del usb fuente
	char *cstr = new char[100];
	strcpy(cstr, comando.c_str());
	system(cstr);
	
	comando=ls+dirusbs+varusb+destino+Documentos+archivofuente;							//Se crea en la ruta de documentos el archivo con el nombre de los archivos contenidos dentro del usb fuente
	strcpy(cstr, comando.c_str());
	system(cstr);																		//Se ejecuta el comando
	
	
	comando = Documentos+archivofuente;													//Se busca la ruta hacia el archivo con los nombres de los archivos del usb fuente
	strcpy(cstr, comando.c_str());
	archer = fopen(cstr,"r");															//abre el archivo desde la direccion
   																									
   while(!feof(archer))																	//ciclo hasta encontrar el final de linea
   {	
		numarchivos++;																	//Cantidad de lineas leidas
		fscanf(archer,"%[^\n]\n",aux);													//adquiere los datos del archivo linea por linea
		
	}
	rewind(archer);																		//se rebobina el archivo y se coloca el cursor al inicio
	Lista ListaNombresArchvios[numarchivos]; 											//se crea una lista del tamano de archivos del usb fuente
	
	
	int f=0;																										
   while(!feof(archer))																	//ciclo hasta encontrar el final de linea
   {	
		fscanf(archer,"%[^\n]\n",ListaNombresArchvios[f]);								//Se guarda en la lista los nombres de los archivos del usb fuente
		f++;		
	}
	
	printf("Cantida de archivos: %d \n",numarchivos );									//Imprime la cantidad de archivos
	for(int i =0;i<numarchivos;i++)														//ciclo para mostrar el nombre de los archivos almacenados en la lista
	{
	printf("%s \n",ListaNombresArchvios[i]);
	}
    fclose(archer);	
    
	printf("PRESIONE ENTER \n");														
	cin.get();
	
	
	return 0;
}
