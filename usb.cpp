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
string dirusbs(" /media/berni/");														//ruta a directorio de los dispositivos usb conectados
string dirusb0("cd /media/berni/");														//ruta a directorio de los dispositivos usb conectados
string ls(" ls ");																		//comando para ver archivos del directorio en que se este dentro
string dir1("/Proyecto_3");																//directorio de archivos para el proyecto*** Carpeta necesaria dentro de documentos
string comando;																			//variable de comando de ejecucion 
string usbconectadas("/usbconectadas");													//nombre de archivo con nombre de usb conectada
string archivofuente("/archivosfuente");												//nombre de archivo con nombre de archivos dentro del usb fuente
string archivoARCDIR("/arcdir");														//nombre de archivo donde se determina si es archivo o directorio
string destino(">");																	//signo de comando para crear un archivo
string Documentos("/home/berni/Documentos");											//ruta a directorio de documentos

int numarchivos=0;																		//Cantidad de archivos dentro del usb fuente
typedef char Lista[100];

char *cstr = new char[100];																//Variable char para comandos
BITMAP *buffer;																			//buffer de almacenamiento de todos los sprites
BITMAP *fondo;																			//variable para guardar imagen del fondo
BITMAP *fa;																				//variable para guardar imagen del fondo
BITMAP *duplicador;
BITMAP *iconos;
BITMAP *press;
BITMAP *usbs;

int x=0;
int sizescreen_x=700;																	//tamano horizontal de la ventana de juego
int sizescreen_y=750;																	//Tamano vertical de la ventana de juego



///////////////----------FUNCIONES-----------////////////////


void pantalla()
{
     blit(buffer,screen,0,0,0,0,sizescreen_x,sizescreen_y);     
} 


void init_allegro()					//Funcion de inicializacion de la libreria Allegro
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
		fa = load_bitmap("usbi.bmp",NULL);								//^
		duplicador = load_bitmap("duplicador.bmp",NULL);				//^
		iconos = load_bitmap("iconos.bmp",NULL);						//^
		press = load_bitmap("press.bmp",NULL);						//^
		usbs = load_bitmap("usbs.bmp",NULL);						//^
        		
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
			if(x<100000000)
			{
				x=x+30000;
				pivot_sprite(buffer,fa,340,340,80,85,x);
				pantalla();
			}	
			else
			{
				pivot_sprite(buffer,fa,340,340,80,85,x);
				
				pantalla();
				x=0;
			}
		
		
		}
				
		
		else{break;}																	//si no esta vacio rompe el ciclo 
	}
   
   
	 
	rewind(doc);																			//rebobina el archivon con el nombre del usb fuente conectado
	fscanf(doc,"%s",var);																//se adquiere el nombre del usb fuente conectado
	fclose(doc);																			//cierra el archivo																								
	
	clear(buffer);
	draw_sprite(buffer,fondo,0,0);
	//draw_sprite(buffer,iconos,0,500);
	textout_ex(buffer,font, "NUEVO DISPOSITIVO", 100, 50, makecol(0,255,0), -1);
	textout_ex(buffer,font, var, 100, 60, makecol(0,255,0), -1);
	
	pantalla();
}


bool ArchivoODirectorio(Lista nomarch)
{
	
	comando=dirusb0+varusb+" && "+"file "+nomarch+destino+Documentos+archivoARCDIR;					
	strcpy(cstr, comando.c_str());
	system(cstr);																		
		
	comando=Documentos+archivoARCDIR;					
	strcpy(cstr, comando.c_str());
	docaux=fopen(cstr,"r");
		
	char dato[100];
	char *ptrToken;
	char linea[140];
		
	fgets(linea, 100, docaux);
	ptrToken = strtok(linea, ":");
	strcpy(dato, ptrToken);
					
	ptrToken = strtok(NULL,	 "\n");
	strcpy(dato, ptrToken);
	
		
	if(strcmp(dato," directory")!=0)
	{
		strcpy(dato, "");
		return true;
		
	}
	else
	{
		strcpy(dato, ""); 	
		return false;
		
	}
	
}



int main() 
{
		
		init_allegro();
		cargasprites();     
		draw_sprite(buffer,fondo,0,0);
		draw_sprite(buffer,duplicador,50,50);
		draw_sprite(buffer,iconos,0,250);
		draw_sprite(buffer,press,150,600);
		pantalla();
		
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		while(true)
		{
			if(key[KEY_ENTER])
			{
				break;
			}
		}
		
		clear(buffer);
		draw_sprite(buffer,fondo,0,0);
		draw_sprite(buffer,usbs,180,100);
		draw_sprite(buffer,iconos,0,500);
		pantalla();
		sleep(1);
		
		
		DetectarUSBFuente(varusb);
		sleep(1);
		
		comando=dirbase+ls+dirusbs+varusb+destino+Documentos+archivofuente;					//Se crea en la ruta de documentos el archivo con el nombre de los archivos contenidos dentro del usb fuente
		
		strcpy(cstr, comando.c_str());
		system(cstr);																		//Se ejecuta el comando
		
		comando = Documentos+archivofuente;													//Se busca la ruta hacia el archivo con los nombres de los archivos del usb fuente
		strcpy(cstr, comando.c_str());
		archer = fopen(cstr,"r");															//abre el archivo desde la direccion
   			
   		  			
   																							
		while(!feof(archer))																//ciclo hasta encontrar el final de linea
		{	
			numarchivos++;																	//Cantidad de lineas leidas
			fscanf(archer,"%[^\n]\n",aux);													//adquiere los datos del archivo linea por linea
		
		}
		rewind(archer);																		//se rebobina el archivo y se coloca el cursor al inicio
		Lista ListaNombresArchivos[numarchivos]; 											//se crea una lista del tamano de archivos del usb fuente
	
	
		int f=0;																										
		while(!feof(archer))																		//ciclo hasta encontrar el final de linea
		{	
			fscanf(archer,"%[^\n]\n",ListaNombresArchivos[f]);										//Se guarda en la lista los nombres de los archivos del usb fuente
			f++;		
		}
		fclose(archer);
		
		textprintf_ex(buffer, font, 250, 60, makecol(255, 0, 0),-1, "Cantidad de elementos: %d", numarchivos);//Imprime la cantidad de archivos
		int c=0;
		
		for(int i =0;i<numarchivos;i++)																//ciclo para mostrar el nombre de los archivos almacenados en la lista
		{
			if(ArchivoODirectorio(ListaNombresArchivos[i]))
				{
					textout_ex(buffer,font,ListaNombresArchivos[i] , 100, i*15+200, makecol(0,0,0), -1);
												
				}
			else
				{
					textout_ex(buffer,font,ListaNombresArchivos[i] , 100, i*15+200, makecol(0,0,0), -1);
					textout_ex(buffer,font,"*" , 90, i*15+200, makecol(0,0,0), -1);
						
				}
				
			
			/*switch(c)
			{
				case 0:
				{	
					if(ArchivoODirectorio(ListaNombresArchivos[i]))
					{
						textout_ex(buffer,font,ListaNombresArchivos[i] , 100, i*15+200, makecol(0,0,0), -1);
						
						c++;
						break;
					}
					else
					{
						textout_ex(buffer,font,ListaNombresArchivos[i] , 100, i*15+200, makecol(0,0,0), -1);
						textout_ex(buffer,font,"*" , 90, i*15+200, makecol(0,0,0), -1);
						c++;
						break;
					}
				}
				
				case 1:
				{
					if(ArchivoODirectorio(ListaNombresArchivos[i]))
					{
						textout_ex(buffer,font,ListaNombresArchivos[i] , 300, (i-1)*15+200, makecol(0,0,0), -1);
						
						c++;
						break;
					}
					else
					{
						textout_ex(buffer,font,ListaNombresArchivos[i] , 100, (i-1)*15+200, makecol(0,0,0), -1);
						textout_ex(buffer,font,"*" , 290, (i-1)*15+200, makecol(0,0,0), -1);
						c++;
						break;
					}
					
					
				}
				
				case 2:
				{
					if(ArchivoODirectorio(ListaNombresArchivos[i]))
					{
						textout_ex(buffer,font,ListaNombresArchivos[i] , 500, (i-2)*15+200, makecol(0,0,0), -1);
						c=0;
						break;
					}
					else
					{
						textout_ex(buffer,font,ListaNombresArchivos[i] , 500, (i-2)*15+200, makecol(0,0,0), -1);
						textout_ex(buffer,font,"*" , 490, (i-2)*15+200, makecol(0,0,0), -1);
						c++;
						break;
						
					}
					
					
				}
			}*/
			
			
				
		
		}
			
		
		
		
				
		pantalla();
		while(true)
		{
			if(key[KEY_ENTER])
			{
				break;
			}
		}
		
		
		
		
		
		
        allegro_exit();
		return 0;
}
END_OF_MAIN()

