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
char aux[100];																			//
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

string file("file ");																	//comando para buscar archivo
string cp(" cp -r ");																	//Comando para copiar archivos
string mkdir(" mkdir ");																//Comando para crear directorio
string copiar;																			//String para guadar comando de copia
string nuevodir;																		//String para guadar comando de creacion de buffer
string bufferm("/buffer_mem");															//Nombre de directorio donde se guardara la copia temporal de la llave
string findpath(" find ");																//comando find 
string nombre(" -name ");																//parte de comando para encontrar archivos
string archivoPATH("/archivoPath");														//nombre de archivo con la direccion completa de los elementos  del usb fuente




int numarchivos=0;																		//Cantidad de archivos dentro del usb fuente
int numanterior=0;																		//Cantidad de archivos leidos
typedef char Lista[500];																//definicion de char tipo lista

char *cstr = new char[500];																//Variable char para almacenar comandos
BITMAP *buffer;																			//buffer de almacenamiento de todos los sprites
BITMAP *fondo;																			//variable para guardar imagen del fondo
BITMAP *duplicador;																		//variable para guardar imagen del titulo
BITMAP *press;																			//variable para guardar imagen de presione enter
BITMAP *usbs;																			//variable para guardar imagen de simbolo de usb fuente
BITMAP *caja;																			//variable para guardar imagen de caja para seleccion
BITMAP *sobrecaja;																		//variable para guardar imagen de sobre caja en seleccion
BITMAP *marcacaja;																		//variable para guardar imagen de marca caja en seleccion


int x=0;
int sizescreen_x=700;																	//tamano horizontal de la ventana de juego
int sizescreen_y=300;																	//Tamano vertical de la ventana de juego

int scroll=0;																			//variable para subir o bajar a traves de la lista

///////////////----------FUNCIONES-----------////////////////


/* Funcion para imprimir en pantalla*/

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
		buffer=create_bitmap(sizescreen_x,sizescreen_y);								//Creacion de espacio de pantalla
		//CARGA DE SPRITES
		fondo = load_bitmap("fondo.bmp",NULL);											//^
		duplicador = load_bitmap("duplicador.bmp",NULL);								//^
		press = load_bitmap("press.bmp",NULL);											//^
		usbs = load_bitmap("usbs.bmp",NULL);											//^
		caja= load_bitmap("caja.bmp",NULL);												//^
		sobrecaja= load_bitmap("sobrecaja.bmp",NULL);									//^
		marcacaja= load_bitmap("marcacaja.bmp",NULL);									//^
        		
}

void DetectarUSBFuente(char *var)
{
	FILE *doc;
	char varaux[500];
	
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
	
	FILE *pathaux;																							//puntero de archivo para guardar el path de un elemento		
	char direccion[500];																					//variable para guardar el path
	
	comando=findpath+Documentos+dir1+bufferm+nombre+"\""+nomarch+"\""+destino+Documentos+archivoPATH;		//creacion del comando para encontrar el path y guardar en un archivo		
	char *cstr6 = new char[comando.length() + 1];															//creacion de puntero char para almacenar el comando completo
	strcpy(cstr6, comando.c_str());
	system(cstr6);																							//ejecucion del comando
	
	comando=Documentos+archivoPATH;																			//creacion de comando para abrir archivo que contiene el path 
	char *cstr7 = new char[comando.length() + 1];															//creacion del puntero char para almacenar comando
	strcpy(cstr7, comando.c_str());	
	pathaux=fopen(cstr7,"r");																				////ejecucion del comando
	
	fscanf(pathaux,"%[^\n]\n",direccion);																	//lee la direccion completa del path del archivo
	fclose(pathaux);																						//cierra archivo
	
	
	///////////////////////////////////////////////////////////////////////////////////////////
	
	
	comando=file+"\""+direccion+"\""+destino+Documentos+archivoARCDIR;					//comando que guarda archivo con caracteristica del elemento nomarch	
	char *cstr9 = new char [comando.length() + 1];
	strcpy(cstr9, comando.c_str());
	system(cstr9);																		//ejecuta comando					

	comando=Documentos+archivoARCDIR;													//carga en comando la direccion del archivo archivoARCDIR
	char *cstr13 = new char [comando.length() + 1];
	strcpy(cstr13, comando.c_str());
	docaux=fopen(cstr13,"r");															//abre archivo archivoARCDIR
		
	char dato[1000];																	//variable para almacenar carateristicas de elementos de usb fuente
	char *ptrToken;																		//puntero para leer ineas
	char linea[1000];
		
	fgets(linea, 1000, docaux);															//se lee el documento con las caractersiticas
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
	nuevodir = mkdir+Documentos+dir1+bufferm;												//creacion de comando para crear la carpeta buffer donde se copian los elementos del usb fuente
	char *cstr3 = new char[nuevodir.length() + 1];											//puntero char para almacenar el comando
	strcpy(cstr3, nuevodir.c_str());
	system(cstr3);																			//ejecuta comando
	
	
}

void CopiarArchivos(Lista archivo)
{
	copiar = cp+"\""+dirusbs+varusb+"/"+archivo+"\""+(" ")+Documentos+dir1+bufferm;			//creacion de comando para copiar elemento por elemento
	char *cstr3 = new char[copiar.length() + 1];											//puntero char para almacenar el comando
	strcpy(cstr3, copiar.c_str());
	system(cstr3);																			//ejecuta comando
	
	
	
}

void LeerCarpeta(Lista archivo)
{
	
	if(!(ArchivoODirectorio(archivo)))
	{
		FILE *pathaux;																					//puntero de tipo file para apuntar a archivo
		char direccion[500];																			//variable para guardar direccion
	
		comando=findpath+Documentos+dir1+bufferm+nombre+"\""+archivo+"\""+destino+Documentos+archivoPATH;	//se crea comando para guardar en archivoPATH la direccion completa de elementos del usb fuente
		char *cstr6 = new char[comando.length() + 1];
		strcpy(cstr6, comando.c_str());
		system(cstr6);																					//ejecuta comando
	
		comando=Documentos+archivoPATH;																	//almacena direccion de archicoPATH
		char *cstr7 = new char[comando.length() + 1];
		strcpy(cstr7, comando.c_str());
		pathaux=fopen(cstr7,"r");																		//abre archivo
	
		fscanf(pathaux,"%[^\n]\n",direccion);															//lee la direccion completa del elemento
		fclose(pathaux);																				//cierra archivo
		
		comando=ls+"\""+direccion+"\""+">>"+Documentos+archivofuente;									//agrega en la ultima linea de archivofuente los contenidos de la direccion
		char *cstr5 = new char[comando.length() + 1];			
		strcpy(cstr5, comando.c_str());
		system(cstr5);																					//ejecuta comando
	}
		
		
}



int main() 
{
		init_allegro();
		cargasprites();     
		
		//Muestra la primera parte del programa
		draw_sprite(buffer,fondo,0,0);
		draw_sprite(buffer,duplicador,50,50);
		draw_sprite(buffer,press,150,200);
		pantalla();
		
		
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		while(true)
		{
			char tecla0= readkey() >> 8;
			if(tecla0==KEY_ENTER)
			{
				break;
			}
		}
		
		clear(buffer);																		//limpia buffer de pantalla
		draw_sprite(buffer,fondo,0,0);														//imprime fono
		draw_sprite(buffer,usbs,180,100);													//imprime mensaje de espera de usb fuente
		pantalla();																			//imprime en pantalla
		sleep(1);																			//tiempo de espera 
		
		
		DetectarUSBFuente(varusb);															//Funcion para detectar usb fuente
		sleep(1);																			//espera mientras se establece la comunicacion con el usb fuente
		
		comando=dirbase+ls+dirusbs+varusb+destino+Documentos+archivofuente;					//Se crea comando para guardar en la ruta de documentos el archivo con el nombre de los archivos contenidos dentro del usb fuente
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
		Lista ListaNombresArchivos[1000]; 													//se crea una lista del tamano de archivos del usb fuente
		
	
		int f=0;																										
		while(!feof(archer))																//ciclo hasta encontrar el final de linea
		{	
			fscanf(archer,"%[^\n]\n",ListaNombresArchivos[f]);								//Se guarda en la lista los nombres de los archivos del usb fuente
			f++;		
		}
		fclose(archer);
		
		NuevoDirectorio();
		/////////////////////////////////////////////////////////////////////////////////////////////////////
		
		for(int i=0;i<numarchivos;i++)
		{
			CopiarArchivos(ListaNombresArchivos[i]);										//Se copia elemento por elemento del usb fuente en el buffer de memoria
			LeerCarpeta(ListaNombresArchivos[i]);											//Si algun elemento es carpeta, se actualizan contenidos en la lista
		}
		
		
		numanterior=numarchivos;															//numeroanterior representa elementos que ya fueron revisados 
		numarchivos=0;																		//Se reinicia variable para contar elementos actuales cargados
		
		comando = Documentos+archivofuente;													//Se crea comando para abrir archivo fuente
		strcpy(cstr, comando.c_str());
		archer = fopen(cstr,"r");															//Se abre archivofuente
		
		
		while(!feof(archer))																//ciclo hasta encontrar el final de linea
		{	
			numarchivos++;																	//Cantidad de lineas leidas
			fscanf(archer,"%[^\n]\n",aux);													//se lee el archivo linea por linea
		}
		
		rewind(archer);																		//Se rebobina archivofuente
		
		f=0;
		while(!feof(archer))																//ciclo hasta encontrar el final de linea
		{	
			fscanf(archer,"%[^\n]\n",ListaNombresArchivos[f]);								//Se guarda en la lista los nombres de los archivos del usb fuente
			f++;		
		}
		
		fclose(archer);																		//Se cierra archivo fuente
		
		
		
		while (numanterior!=numarchivos)													//Ciclo para verififcar que  la lista esta completa con todos los elementos del usb fuente
		{
			
			for (int i =numanterior;i<numarchivos;i++)										//Se recorren los elementos de la lista que sean directorios y que no se han abierto										
			{
				LeerCarpeta(ListaNombresArchivos[i]);										//abre los directorios y actualiza lista
			}	
		
			comando = Documentos+archivofuente;												//Se busca la ruta hacia el archivo con los nombres de los archivos del usb fuente
			strcpy(cstr, comando.c_str());
			archer = fopen(cstr,"r");														//Se ejecuta comando
		
			numanterior=numarchivos;														//actualiza contidad de elementos
			numarchivos=0;																	//reinicia contador de elementos
		
			while(!feof(archer))																//ciclo hasta encontrar el final de linea
			{	
				numarchivos++;																	//Cantidad de lineas leidas
				fscanf(archer,"%[^\n]\n",aux);													//se lee el archivo linea por linea
			}
		
			rewind(archer);
			f=0;
			while(!feof(archer))															//ciclo hasta encontrar el final de linea
			{	
				fscanf(archer,"%[^\n]\n",ListaNombresArchivos[f]);							//Se guarda en la lista los nombres de los archivos del usb fuente
				f++;		
			}
		
			fclose(archer);
		}
		
		
		bool ListaCopia[numarchivos];														//Lista de estados para selecion de todos elementos
	
		for(int i=0;i<numarchivos;i++)
		{
			ListaCopia[i]=false;															//Llena con false el estado de selecion
		}
		
		
		textprintf_ex(buffer, font, 500, 30, makecol(255, 0, 0),-1, "# elementos: %d", numarchivos);//Imprime la cantidad de archivos
		pantalla();																					//imprime en pantalla
		
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
			
			if(tecla==KEY_S)																			//Si se presiona S selecciona elemento
			{
				ListaCopia[scroll]=true;
				draw_sprite(buffer,marcacaja,77, (scroll)*15+19);
				
			}
			
			if(tecla==KEY_D)																			//Si se presiona D deselecciona elemento
			{
				ListaCopia[scroll]=false;
				draw_sprite(buffer,sobrecaja,77, (scroll)*15+19);
				
			}
						
			else if(tecla==KEY_DOWN)																		//Se mueve seleccionador hacia abajo
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
			
			if(tecla==KEY_UP)																				//Se mueve seleccionador hacia arriba
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
		
		
		
		
		
		while(true)																							//Espera Enter para salir
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

