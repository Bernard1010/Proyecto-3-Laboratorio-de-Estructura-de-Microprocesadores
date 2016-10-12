#include <allegro.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <unistd.h>



using namespace std;

////---------------------------VARIABLES------------------

FILE *archer;																			//puntero a archivo con el nombre de los archivos del usb fuente
FILE *docaux;																			//puntero auxuliar para saber si es directorio o archivo
char aux[100];
char varusb[60];																		//variable del nombre del dispositivo de almacenamiento usb fuente
string dirbase("cd /home/berni && ");													//ruta a directorios base
string dirusbs("/media/berni/");														//ruta a directorio de los dispositivos usb conectados
string dirusb0("cd /media/berni/");														//ruta a directorio de los dispositivos usb conectados
string ls(" ls ");																		//comando para ver archivos del directorio en que se este dentro
string dir1("/Proyecto_3");																//directorio de archivos para el proyecto*** Carpeta necesaria dentro de documentos
string comando;																			//variable de comando de ejecucion 
string usbconectadas("/usbconectadas");													//nombre de archivo con nombre de usb conectada
string archivofuente("/archivosfuente");												//nombre de archivo con nombre de archivos dentro del usb fuente
string archivoARCDIR("/arcdir");														//nombre de archivo donde se determina si es archivo o directorio
string destino(">");																	//signo de comando para crear un archivo
string Documentos("/home/berni/Documentos");											//ruta a directorio de documentos

string file("file ");
string cp(" cp -r ");																	//Comando para copiar archivos
string mkdir(" mkdir ");																//Comando para crear directorio
string copiar;
string nuevodir;
string bufferm("/buffer_mem");															//Nombre de directorio donde se guardara la copia temporal de la llave
string findpath(" find ");
string nombre(" -name ");
string archivoPATH("/archivoPath");




int numarchivos=0;																		//Cantidad de archivos dentro del usb fuente
typedef char Lista[100];

char *cstr = new char[100];																//Variable char para almacenar comandos
BITMAP *buffer;																			//buffer de almacenamiento de todos los sprites
BITMAP *fondo;																			//variable para guardar imagen del fondo
BITMAP *duplicador;																		//variable para guardar imagen del titulo
BITMAP *press;																			//variable para guardar imagen de presione enter
BITMAP *usbs;																			//variable para guardar imagen de simbolo de usb fuente
BITMAP *caja;																			//variable para guardar imagen de caja para seleccion
BITMAP *sobrecaja;																		//variable para guardar imagen de sobre caja en seleccion
BITMAP *marcacaja;																		//variable para guardar imagen de marcA caja en seleccion


int x=0;
int sizescreen_x=700;																	//tamano horizontal de la ventana de juego
int sizescreen_y=300;																	//Tamano vertical de la ventana de juego

int scroll=0;																			//variable para subir o bajar a traves de la lista

///////////////----------FUNCIONES-----------////////////////


void pantalla()
{
     blit(buffer,screen,0,0,0,0,sizescreen_x,sizescreen_y);     
} 


void init_allegro()																		//Funcion de inicializacion de la libreria Allegro
{
		allegro_init();
		install_keyboard();
	    set_color_depth(32);
        set_gfx_mode(GFX_AUTODETECT_WINDOWED, sizescreen_x,sizescreen_y,0,0);
	
}


void cargasprites()
{
		buffer=create_bitmap(sizescreen_x,sizescreen_y);			//Creacion de espacio de juego
        fondo = load_bitmap("fondo.bmp",NULL);						//^
		duplicador = load_bitmap("duplicador.bmp",NULL);			//^
		press = load_bitmap("press.bmp",NULL);						//^
		usbs = load_bitmap("usbs.bmp",NULL);						//^
		caja= load_bitmap("caja.bmp",NULL);							//^
		sobrecaja= load_bitmap("sobrecaja.bmp",NULL);				//^
		marcacaja= load_bitmap("marcacaja.bmp",NULL);				//^
        		
}

void DetectarUSBFuente(char *var)
{
	FILE *doc;
	char varaux[100];
	
	comando = dirbase+ls+dirusbs+destino+Documentos+dir1+usbconectadas;					//Usando el comando ls de linux, se crea un archivo donde se guarda el nombre de los dispositivos USB conectados(aparecen dentro del directorio /media/ususario/), el archivo se guarda en  la direccion luego del simbolo >
	char *cstr1 = new char[comando.length() + 1];
	strcpy(cstr1, comando.c_str());
	system(cstr1);																				
	
	
	comando = Documentos+dir1+usbconectadas;
	char *cstr2 = new char[comando.length() + 1];
	strcpy(cstr2, comando.c_str());
	doc = fopen(cstr2,"r");																//abre el archivo desde la direccion
	
	while(true)																			//entra en el ciclo infinito de comprobacion
	{	
		system(cstr1);																	//refresca los dato del directorio de las usb conectadas
		fseek( doc, 0, SEEK_END );														//posiciona el cursor al final de archivo
		if (ftell( doc ) == 0 )															//si es 0 esta vacio el archivo-no usb conectadas
		{	
			
		}
		else{break;}																	//si no esta vacio rompe el ciclo 
	}
   
   	 
	rewind(doc);																		//rebobina el archivon con el nombre del usb fuente conectado
	fscanf(doc,"%s",var);																//se adquiere el nombre del usb fuente conectado
	fclose(doc);																		//cierra el archivo																								
	
	clear(buffer);
	draw_sprite(buffer,fondo,0,0);
	textout_ex(buffer,font, "NUEVO DISPOSITIVO", 400, 20, makecol(0,255,0), -1);	
	textout_ex(buffer,font, var, 400, 30, makecol(0,255,0), -1);
	
	pantalla();
}


bool ArchivoODirectorio(Lista nomarch)
{
	
	FILE *pathaux;
	char direccion[200];
	
	comando=findpath+Documentos+dir1+bufferm+nombre+"\""+nomarch+"\""+destino+Documentos+archivoPATH;
	char *cstr6 = new char[comando.length() + 1];
	strcpy(cstr6, comando.c_str());
	system(cstr6);	
	
	comando=Documentos+archivoPATH;	
	char *cstr7 = new char[comando.length() + 1];
	strcpy(cstr7, comando.c_str());
	pathaux=fopen(cstr7,"r");
	
	fscanf(pathaux,"%[^\n]\n",direccion);	
	fclose(pathaux);
	
	
	
	
	comando=file+"\""+direccion+"\""+destino+Documentos+archivoARCDIR;		//comando que guarda archivo con caracteristica del elemento nomarch	
	strcpy(cstr, comando.c_str());
	system(cstr);																		//ejecuta comando					

	comando=Documentos+archivoARCDIR;													//carga en comando la direccion del archivo archivoARCDIR
	strcpy(cstr, comando.c_str());
	docaux=fopen(cstr,"r");																//abre archivo archivoARCDIR
		
	char dato[200];																		//variable para almacenar carateristicas de elementos
	char *ptrToken;																		
	char linea[140];
		
	fgets(linea, 200, docaux);															//se lee el documento con las caractersiticas
	ptrToken = strtok(linea, ":");														//corta la linea cuando vea un :
	strcpy(dato, ptrToken);
					
	ptrToken = strtok(NULL,	 "\n");														//corta la linea cuando vea un final de linea
	strcpy(dato, ptrToken);																//carga la caracteristica del elemento en dato
	
	fclose(docaux);
	if(strcmp(dato," directory")!=0)													//compara el contenido en dato
	{
		strcpy(dato, "");
		return true;																	//Devuelve que es un archivo
		
	}
	else
	{
		strcpy(dato, ""); 	
		return false;																	//devuelve que es un directorio
		
	}
	
}

void NuevoDirectorio()
{
	nuevodir = mkdir+Documentos+dir1+bufferm;
	char *cstr3 = new char[nuevodir.length() + 1];
	strcpy(cstr3, nuevodir.c_str());
	system(cstr3);
}

void CopiarArchivos(Lista archivo)
{
	copiar = cp+"\""+dirusbs+varusb+"/"+archivo+"\""+(" ")+Documentos+dir1+bufferm;
	char *cstr3 = new char[copiar.length() + 1];
	strcpy(cstr3, copiar.c_str());
	system(cstr3);
	
}





int main() 
{
		//Muestra la primera parte del programa
		init_allegro();
		cargasprites();     
		
		draw_sprite(buffer,fondo,0,0);
		draw_sprite(buffer,duplicador,50,50);
		draw_sprite(buffer,press,150,200);
		pantalla();
		
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		while(true)																			//Se espera el enter para pasar a la busqueda del usb fuente
		{
			if(key[KEY_ENTER])
			{
				break;
			}
		}
		
		clear(buffer);
		draw_sprite(buffer,fondo,0,0);
		draw_sprite(buffer,usbs,180,100);
		pantalla();
		sleep(1);
		
		
		DetectarUSBFuente(varusb);															//Funcion para detectar usb fuente
		sleep(1);																			//espera mientras se establece la comunicacion con el usb fuente
		
		comando=dirbase+ls+dirusbs+varusb+destino+Documentos+archivofuente;					//Se crea en la ruta de documentos el archivo con el nombre de los archivos contenidos dentro del usb fuente
		strcpy(cstr, comando.c_str());
		system(cstr);																		//Se ejecuta el comando
		
		comando = Documentos+archivofuente;													//Se busca la ruta hacia el archivo con los nombres de los archivos del usb fuente
		strcpy(cstr, comando.c_str());
		archer = fopen(cstr,"r");															//abre el archivo desde la direccion
   		   																							
		while(!feof(archer))																//ciclo hasta encontrar el final de linea
		{	
			numarchivos++;																	//Cantidad de lineas leidas
			fscanf(archer,"%[^\n]\n",aux);													//se lee el archivo linea por linea
		
		}
		rewind(archer);																		//se rebobina el archivo y se coloca el cursor al inicio
		Lista ListaNombresArchivos[numarchivos]; 											//se crea una lista del tamano de archivos del usb fuente
		bool ListaCopia[numarchivos];
	
		for(int i=0;i<numarchivos;i++)
		{
			ListaCopia[i]=false;
		}
	
		int f=0;																										
		while(!feof(archer))																		//ciclo hasta encontrar el final de linea
		{	
			fscanf(archer,"%[^\n]\n",ListaNombresArchivos[f]);										//Se guarda en la lista los nombres de los archivos del usb fuente
			f++;		
		}
		fclose(archer);
		
		NuevoDirectorio();
		
		for(int i=0;i<numarchivos;i++)
		{
			CopiarArchivos(ListaNombresArchivos[i]);
		}
		
/////////////////////////////////////////////////////////////////////////////////////////////////////

		/*Seccion para preguntar al usuario que desea hacer-> copia total o seleccionar archivos*/
		
		
//////////////////////////////////////////////////////////////////////////////////////////////////////		
		textprintf_ex(buffer, font, 500, 30, makecol(255, 0, 0),-1, "# elementos: %d", numarchivos);//Imprime la cantidad de archivos
		pantalla();
		
/////////////////////////////////////////////////////////////////////////////////////////////////////		
//IMPRIME LA LISTA DE ARCHIVOS		
		for(int i=0;i<numarchivos;i++)																//ciclo para mostrar el nombre de los archivos almacenados en la lista
				{
					
					if(ArchivoODirectorio(ListaNombresArchivos[i]))											//comprueba si es un archivo o un directorio
						{
							
							textout_ex(buffer,font,ListaNombresArchivos[i] , 100, (i)*15+20, makecol(0,0,0), -1);	//si es archivo solamente imprime el nombre
							draw_sprite(buffer,caja,77, (i)*15+19);						
						}
					else
						{
							textout_ex(buffer,font,ListaNombresArchivos[i] , 100, (i)*15+20, makecol(0,0,0), -1);	//imprime el nombre del directorio
							textout_ex(buffer,font,"*" , 90, (i)*15+20, makecol(0,0,0), -1);							//coloca un asterisco para diferenciar las carpetas
							draw_sprite(buffer,caja,77, (i)*15+19);	
						}
				}
		draw_sprite(buffer,sobrecaja,77,19);	
		pantalla();
		
//CICLO PARA ESCOGER ARCHIVOS		
		while(!key[KEY_ESC])
		{
			usleep(100000);
			char tecla= readkey() >> 8;																	//espera teclaso del usuario
			
			if(tecla==KEY_S)
			{
				ListaCopia[scroll]=true;
				draw_sprite(buffer,marcacaja,77, (scroll)*15+19);
				
			}
			
			if(tecla==KEY_D)
			{
				ListaCopia[scroll]=false;
				draw_sprite(buffer,sobrecaja,77, (scroll)*15+19);
				
			}
						
			else if(tecla==KEY_DOWN)
			{
				for(int i=0;i<numarchivos;i++)																//ciclo para mostrar el nombre de los archivos almacenados en la lista
				{	
					if(ArchivoODirectorio(ListaNombresArchivos[i]))											//comprueba si es un archivo o un directorio
						{
							textout_ex(buffer,font,ListaNombresArchivos[i] , 100, (i)*15+20, makecol(0,0,0), -1);	//si es archivo solamente imprime el nombre
							draw_sprite(buffer,caja,77, (i)*15+19);						
						}
					else
						{
							textout_ex(buffer,font,ListaNombresArchivos[i] , 100, (i)*15+20, makecol(0,0,0), -1);	//imprime el nombre del directorio
							textout_ex(buffer,font,"*" , 90, (i)*15+20, makecol(0,0,0), -1);							//coloca un asterisco para diferenciar las carpetas
							draw_sprite(buffer,caja,77, (i)*15+19);	
						}
				}
				if(scroll+1<numarchivos)
				{
					scroll++;
					draw_sprite(buffer,sobrecaja,77, (scroll)*15+19);	
					if(ListaCopia[scroll])
					{
					draw_sprite(buffer,marcacaja,77, (scroll)*15+19);
					}
					
				}
			
				
				else
				{
					draw_sprite(buffer,sobrecaja,77, (scroll)*15+19);
					if(ListaCopia[scroll])
					{
						draw_sprite(buffer,marcacaja,77, (scroll)*15+19);
					}
					
					
				}
			}
			
			if(tecla==KEY_UP)
			{
				for(int i=0;i<numarchivos;i++)																//ciclo para mostrar el nombre de los archivos almacenados en la lista
				{
					if(ArchivoODirectorio(ListaNombresArchivos[i]))											//comprueba si es un archivo o un directorio
						{
							textout_ex(buffer,font,ListaNombresArchivos[i] , 100, (i)*15+20, makecol(0,0,0), -1);	//si es archivo solamente imprime el nombre
							draw_sprite(buffer,caja,77, (i)*15+19);						
						}
					else
						{
							textout_ex(buffer,font,ListaNombresArchivos[i] , 100, (i)*15+20, makecol(0,0,0), -1);	//imprime el nombre del directorio
							textout_ex(buffer,font,"*" , 90, (i)*15+20, makecol(0,0,0), -1);							//coloca un asterisco para diferenciar las carpetas
							draw_sprite(buffer,caja,77, (i)*15+19);	
						}
				}
				if(scroll>0)
				{
					scroll--;
					draw_sprite(buffer,sobrecaja,77, (scroll)*15+19);	
					if(ListaCopia[scroll])
					{
						draw_sprite(buffer,marcacaja,77, (scroll)*15+19);
					}
					
					
				}
				else
				{
					draw_sprite(buffer,sobrecaja,77, (scroll)*15+19);
					if(ListaCopia[scroll])
					{
					draw_sprite(buffer,marcacaja,77, (scroll)*15+19);
					}
					
				}
			}
					
			
			
		pantalla();
		
		}
		
		
		
		
		
		
		while(true)
		{
			char tecla1= readkey() >> 8;
			if(tecla1==KEY_ENTER)
			{
				break;
			}
		}
		
		
				
        allegro_exit();
		return 0;
}
END_OF_MAIN()

