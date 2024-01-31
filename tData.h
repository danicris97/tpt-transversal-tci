#ifndef TDATA_H
#define TDATA_H

#define ATM 1
#define SET 2
#define LIST 3

struct dataType{
	int nodeType;
	union{
		char* atom;
		struct{
			struct dataType* data;
			struct dataType* next; 
		};
	};
};
typedef struct dataType* tData;

/*operaciones generales*/

//a partir de una cadena dada por el usuario, crea un nuevo dato (ATM, SET o LIST)
tData newData(char *s);
//a partir de un tData crea uno nuevo anidando (nest) el tData recibido como hijo derecho
tData newNestedData(tData d, int t);
//copia un tData
tData copyData(tData d);
//elimina un dataSL
void dataFree(tData* d);
//imprime un dato por pantalla
void printData(tData d);
//auxiliares para imprimir por pantalla
//printea un tipo atomo
void printAtm(tData d);
//printra una tipo list
void printList(tData d);
//printea un tipo set
void printSet(tData d);
//retorna tipo de dato
int returnType(tData d);
//convierte tData a cadena
char* toStr(tData d);

/*operaciones con SET y LIST*/
/*Retorna elemento en posición pos dentro del SLData*/
tData returnElem(tData d, int pos);
//retorna 1 si esta vacio, 0 si tiene elementos
int isEmpty(tData d);
//retorna 1 si son iguales, 0 si son distintos
int isEqual(tData d1, tData d2);

/*operaciones con LIST*/
//agrega un elemento a la lista por el final 
void PUSH(tData L, tData elem); 
//elimina el último elemento de la lista y lo devuelve como salida
tData POP(tData* L); 
//retorna el tamaño de la lista
int SIZEL(tData L); 

/*operaciones con SET*/
//calcula la cantidad de elementos de un conjunto
int CARDINAL(tData S);
//determina si un elemento pertenece a un conjunto
int IN(tData S, tData elem);
//genera un nuevo conjunto que resulta de la unión de dos conjuntos
tData UNION(tData A,tData B);
//genera un nuevo conjunto que resulta de la intersección de dos conjuntos
tData INTER(tData A,tData B);
//genera un nuevo conjunto que resulta de la diferencia de dos conjuntos
tData DIFF(tData A,tData B);

//modulos auxliares
void leeCad(char *cadena, int tam);
void cleanBuffer();
void getElem(char**s, char**aux);

#endif
