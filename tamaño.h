#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>


using namespace std;

//--------------------------------FUNCIONES------------------------

int tama(string comando, string Documentos, string du, string des, string destino ) 
{	
	comando = du+Documentos+des+destino;
	char *cstr2 = new char[comando.length() + 1];
	strcpy(cstr2, comando.c_str());
	system(cstr2);
	return 0;
}
