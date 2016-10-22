#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>


using namespace std;

float x;
float x2;
float y;
float espacio;
string comando2;
string comando3;
int k = 1000;
int m = 100000;
int g = 100000000;
string a=".";
string M = "M";
string K = "K";
string G = "G";
string num2;

int main()
{
	
//------------------------------------Obtencion de tamaño de carpetas--------------------------------------------------------
	FILE* tama;
	char taman[100];
	char ta[100];
	char letra[100];
	string numero;
	comando2="/home/sergio/Escritorio/resultado";																			//creacion de comando para abrir archivo que contiene el path 
	char *cstr13 = new char[comando2.length() + 1];															//creacion del puntero char para almacenar comando
	strcpy(cstr13, comando2.c_str());	
	tama=fopen(cstr13,"r");																				////ejecucion del comando
	fscanf(tama,"%[^,]",taman);
	fscanf(tama,"%[^0-9]",ta);	
	fscanf(tama,"%[^A-Z]",ta);
	fscanf(tama,"%s",letra);
	numero=taman+a;
	numero=numero+ta;
	char *cstr1 = new char[numero.length() + 1];
	strcpy(cstr1, numero.c_str());
	x= atof(cstr1);
	if (letra ==K){
		x=x*k;
	}
	else if (letra ==M){
		x=x*m;
	}
	else if (letra ==G){
		x=x*g;
	}
	printf("el tamaño de los archivos a copiar es: ");
	printf("%f\n",x);
	fclose(tama);
    
	
//-------------------------Obtencion del tamaño disponible en la memoria externa--------------------------------------------------	
	
	FILE* tamano;
	char numero1[100];
	char letra1[100];
	char numero2[100];
	char numero2_1[100];
	char letra2[100];
	string comando3;
	comando3="/home/sergio/Escritorio/resultados";																			
	char *cstr12 = new char[comando3.length() + 1];															
	strcpy(cstr12, comando3.c_str());	
	
	tamano=fopen(cstr12,"r");																				
	fscanf(tamano,"%[^\n]\n",numero1);
	fscanf(tamano,"%s",numero1);
	fscanf(tamano,"%[^0-9]",numero1);
	fscanf(tamano,"%[^A-Z]",numero1);	
	fscanf(tamano,"%s",letra1);
    fscanf(tamano,"%[^0-9]",numero2);
    fscanf(tamano,"%[^,]",numero2);
    fscanf(tamano,"%[^0-9]",numero2_1);	
	fscanf(tamano,"%[^A-Z]",numero2_1);
	fscanf(tamano,"%s",letra2);
	
    num2=numero2+a;
    num2=num2+numero2_1;
    char *numeroc2 = new char[num2.length() + 1];
	strcpy(numeroc2, num2.c_str());
    	
    x2= atof(numero1);
	if (letra1 ==K){
		x2=x2*k;
	}
	else if (letra1 ==M){
		x2=x2*m;
	}
	else if (letra1 ==G){
		x2=x2*g;
	}
	
	y= atof(numeroc2);
	if (letra2 ==K){
		y=y*k;
	}
	else if (letra2 ==M){
		y=y*m;
	}
	else if (letra2 ==G){
		y=y*g;
	}
	
	printf("el tamaño de la llave es de : " );
	printf("%f\n",x2);
	printf("el espacio utilizado es de : " );
	printf("%f\n",y);
	espacio = x2-y;
	printf("espacio en la memoria: " );
	printf("%f\n",espacio);

	if (espacio>x){
		
		printf("si hay espacio disponible para la copia");
	}
	
	else {
		printf("no hay espacio disponible para la copia");
	}


    fclose(tamano);
	return 0;
	
}


