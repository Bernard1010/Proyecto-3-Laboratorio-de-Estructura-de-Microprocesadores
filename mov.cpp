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
string ls("ls ");								//comando para ver archivos del directorio en que se este dentro
string dir1("Descargas");						//directorio
string dir2("Documentos/rar");					//directorio + nombre de archivo de salida
string destino(">");							//signo para crear un archivo de texto

	string fun=ls + dir1 + destino + dir2;
	char *cstr = new char[fun.length() + 1];
	strcpy(cstr, fun.c_str());
	system(cstr);
*/


////---------------------------VARIABLES------------------


char varusb[60];											//variable del nombre del dispositivo de almacenamiento usb fuente
string dirbase("cd /home/berni && ");
string dirusbs(" /media/berni/");
string ls(" ls ");											//comando para ver archivos del directorio en que se este dentro
string dir1("Descargas");									//directorio
string comando;
string archivofuente("/archivosfuente");
string destino(">");
string Documentos("/home/berni/Documentos");


//--------------------------------FUNCIONES------------------------
void DetectarUSBFuente(char *var)
{
	FILE *doc;
	char varaux[40];
	system("cd /home/berni && ls /media/berni> /home/berni/Escritorio/USB/manejo_ficheros/usbconectadas");					//Usando el comando ls de linux, se crea un archivo donde se guarda el nombre de los dispositivos USB conectados(aparecen dentro del directorio /media/ususario/), el archivo se guarda en  la direccion luego del simbolo >
	doc = fopen("/home/berni/Escritorio/USB/manejo_ficheros/usbconectadas","r");											//abre el archivo desde la direccion
   
	int c=0;
	while(true)																												//entra en el ciclo infinito de comprobacion
	{	
		c++;
		sleep(1);																											// tiempo de refrescamiento
		system("cd /home/berni && ls /media/berni> /home/berni/Escritorio/USB/manejo_ficheros/usbconectadas");				//refresca los dato del directorio de las usb conectadas
				
		fseek( doc, 0, SEEK_END );																							//posiciona el cursor al final de archivo
		if (ftell( doc ) == 0 )																								//si es 0 esta vacio el archivo-no usb conectadas
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
				
		
		else{break;}																										//si no esta vacio rompe el ciclo 
	}
   
   rewind(doc);
   int f=0;																											//se rebobina el archivo y se coloca el cursor al inicio
   while(!feof(doc))																								//ciclo hasta encontrar el final de linea
   {	
		if(f==0)
		{
			fscanf(doc,"%s",var);
			fscanf(doc,"%s",varaux);																				//adquiere los datos del archivo linea por linea
			strcpy(varaux, "");																						//limpia la ariable de lectura
		}
		else
		{
			fscanf(doc,"%s",varaux);																				//adquiere los datos del archivo linea por linea
			strcpy(varaux, "");	
			
		}
		f++;
	
	}
    
    fclose(doc);																									//cierra el archivo
	
}




int main() 
{	
	
	
	DetectarUSBFuente(varusb);
	system("clear");
	printf("Nuevo Dispositivo: %s \n",varusb);
	printf("\n");
	printf("Archivos de: %s \n",varusb);
	
	comando=ls+dirusbs+varusb;
	char *cstr = new char[100];
	strcpy(cstr, comando.c_str());
	system(cstr);
	
	comando=ls+dirusbs+varusb+destino+Documentos+archivofuente;
	strcpy(cstr, comando.c_str());
	system(cstr);
	
	
	printf("PRESIONE ENTER \n");
	cin.get();
	
	
	return 0;
}
