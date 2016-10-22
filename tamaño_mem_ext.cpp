#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <tamañototal.h>

using namespace std;

FILE *Juan;																			
string df("df -h ");	   														    //comando para calcuar el tamaño de  carpeta
string comandos;
string des ("> ");
string destino("/home/sergio/Escritorio/resultados");																		//variable de comando de ejecucion 												
string Documentoss("/media/sergio/CHECHO");

int main ()
{
	tamm(comandos,Documentoss,df,des,destino);
	
	}
