#include <stdio.h>
#include "tData.h"
#include <stdlib.h>
#include <string.h>

#define TAM_MAX 1000

int main() {
	char* cadena=NULL;
	char* aux=NULL;
	
	cadena=(char*) malloc(sizeof(char)*255);
	printf("Dato a cargar: ");
	leeCad(cadena, TAM_MAX);
	
	tData root=(tData)malloc(sizeof(struct dataType));
	root=newData(cadena);
	
	printf("\nData ingresada: ");
	printData(root);
	
	aux=(char*) malloc(sizeof(char)*255);
	printf("\nIngrese otro dato: ");
	leeCad(aux, TAM_MAX);
	
	tData auxiliar=(tData)malloc(sizeof(struct dataType));
	auxiliar=newData(aux);
	
	tData resultado=(tData)malloc(sizeof(struct dataType));
	
	printf("\nTest funcion: ");
	resultado=DIFF(root,auxiliar);
	printData(resultado);
	
	printf("\nData modificada: ");
	printData(root);
	
	printf("\nSi llego hasta aqui debe funcionar...");
	
	return 0;
}


