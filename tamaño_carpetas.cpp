#include <tamaño.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>


using namespace std;


FILE *Juan;																			
string dus (" du -sh ");	   														    //comando para calcuar el tamaño de  carpeta
string comandos;
string des ("> ");
string destino("/home/sergio/Escritorio/resultado");																		//variable de comando de ejecucion 												
string Documentoss("/media/sergio/CHECHO");

int main ()
{ 
	tama(comandos, Documentoss,dus,des,destino);
	return 0;
}
