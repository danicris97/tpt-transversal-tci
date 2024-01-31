#include "tData.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//---MODULOS AUXILIARES PARA CADENAS---

//quita primer y último caracter de la cadena
//asume que inicia y termina con {} o con []
char* clean(char* s){
	int i=1;
	char* aux;
	aux=(char*) malloc(sizeof(char)*255); 
	while (s[i]!='\0'){
		aux[i-1]=s[i];
		i++;
	}
	aux[i-2]='\0';
	return aux;
}

//de la cadena s extrae el primer elemento de la estructura
//asume llaves y corchetes balanceados
void getElem(char**s, char**aux){
	char* s_aux;
	int i=0;
	int cont_abre_l=0;
	int cont_cierra_l=0;
	int cont_abre_c=0;
	int cont_cierra_c=0;
	int j,salir;
	
	*aux=(char*) malloc(sizeof(char)*255); 
	s_aux=(char*) malloc(sizeof(char)*255);
	if ((*s)[0]!='{' && (*s)[0]!='[') {
		while ((*s)[i]!='\0' && (*s)[i]!=',') {
			(*aux)[i]=(*s)[i];
			i++;
		}
		(*aux)[i]='\0';
	} else {
		salir=0;
		while ((*s)[i]!='\0' && !salir) {
			(*aux)[i]=(*s)[i];
			switch ((*s)[i]) {
			case '{':
				cont_abre_l++;
				break;
			case '[':
				cont_abre_c++;
				break;	
			case '}':
				cont_cierra_l++;
				break;
			case ']':
				cont_cierra_c++;
				break;
			}
			if (cont_abre_l-cont_cierra_l==0 && cont_abre_c-cont_cierra_c==0) 
				salir=1;
			i++;
		}
		(*aux)[i]='\0';
	}
	i++;
	if (i<strlen(*s)) {
		j=0;
		while ((*s)[i]!='\0'){
			s_aux[j]=(*s)[i];
			j++;
			i++;
		}
		s_aux[j]='\0';
		*s=s_aux;
	} else *s=NULL;
}
	
void cleanBuffer(){
	char c;
	while ((c=getchar())!='\n' && c!=EOF);
}

//lee una cadena
void leeCad(char *cadena, int tam){
	int j, m;
	/*obtener el primer caracter del stdin*/
	m=getchar();
	/*ANALIZAR EL PRIMER CARACTER LEÍDO*/
	if (m!=EOF) { /*si el primer caracter no es fin de archivo*/
		
		/*inicializacion del índice que maneja el vector de char*/
		j=0;
		/*si el primer caracter leido no es un enter, se lo guarda en la cadena*/
		if (m!='\n'){ 
			cadena[j]=m; 
			j++;
		}
		/*LEER DEL SEGUNDO CARACTER EN ADELANTE*/
		/*leer el resto de los caractaeres y ponerlos en el vector de char*/
		m=getchar();
		while (j<tam-1 && m!=EOF && m!='\n') {
			cadena[j]=m;
			m=getchar();
			j++;
		}
		/*agregar marca de fin de cadena*/
		cadena[j]='\0';
		
		/*vaciar la pila*/
		while(m!=EOF && m!='\n')
			m=getchar();
		
	} else {
		/*si se lee el fin del archivo en el primer caracter, no hay cadena*/
		/*solo poner la marca de fin de cadena*/
		cadena[0]='\0';
	}
	
}	

//--MODULOS AUXILIARES PARA EL MANEJO DE LA ESTRUCTURA---

//crea un nuevo nodo vacio de un determinado tipo
tData newNodeNull(int type){
	tData newNode=(tData)malloc(sizeof(struct dataType));
	newNode->nodeType=type;
	if(type==ATM){
		newNode->atom=NULL;
	}else{
		newNode->data=NULL;
		newNode->next=NULL;
	}
	
	return newNode;
}

//crea un nuevo nodo set list indicando tipo
tData newNodeSetList(int type){
	if(type!=ATM){
		tData nodeSetList=(tData)malloc(sizeof(struct dataType));
		nodeSetList->nodeType=type;
		nodeSetList->data=NULL;
		nodeSetList->next=NULL;
		
		return nodeSetList;
	}else{
		printf("\nError. Tipo de dato indicado erroneo");
		return NULL;
	}
}

//crea un nuevo nodo del tipo atomo
tData newNodeAtom(char *string){
	tData nodeAtm=(tData)malloc(sizeof(struct dataType));
	nodeAtm->nodeType=ATM;
	nodeAtm->atom=string;

	return nodeAtm;
}

//---MODULOS AUXILIARES PARA LAS OPERACIONES PRINCIPALES---
	
//obtiene una cadena de un atomo
char* getString(tData s){
	return s->atom;
}

//busca un elemento en la estructura
int search(tData tree, tData elem){
	int pos=1, b=1;
	//tData aux, ant;
	char *string=(char*)malloc(sizeof(char)*1000);
	char *stringElem=(char*)malloc(sizeof(char)*1000);
	
	if(returnType(elem)==ATM){
		stringElem=getString(elem);
	}else{
		stringElem=toStr(elem);
	}
	
	while(tree!=NULL && b){
		if(returnType(tree->data)==ATM){
			string=getString(tree->data);
		}else{
			string=toStr(tree->data);
		}
		
		if(strcmp(stringElem,string)>=0){
			pos++;
			tree=tree->next;
		}else{
			b=0;
		}
	}
	
	return pos;
}


// Inserta un nuevo elemento de manera ordenada
void insert(tData *tree, tData elem){
	int pos, con=1;
	tData ant=(tData)malloc(sizeof(struct dataType));
	tData aux=(tData)malloc(sizeof(struct dataType));
	ant=*tree, aux=*tree;
	pos=search(*tree,elem->data);
	if(*tree!=NULL){
		if(pos>CARDINAL(*tree)){
			while(aux->next!=NULL){
				aux=aux->next;
			}
			aux->next=elem;
		}else if(pos==1){
			elem->next=aux;
			*tree=elem;
		}else{
			while(con!=pos && aux->next!=NULL){
				ant=aux;
				aux=aux->next;
				con++;
			}
			ant->next=elem;
			elem->next=aux;
		}
	}else{
		*tree=elem;
	}	
}	
	
	
//determina si dos elementos son iguales
int equals(tData data, tData element){
	char* sAux=(char*)malloc(sizeof(char)*1000);
	char* sNew=(char*)malloc(sizeof(char)*1000);
	
	if(returnType(data)==ATM){
		sAux=getString(data);
	}else{
		sAux=toStr(data);
	}
	
	if(returnType(element)==ATM){
		sNew=getString(element);
	}else{
		sNew=toStr(element);
	}

	if(strcmp(sNew,sAux)==0){
		return 1;
	}
	else return 0;
}

//devuelve el tamaño de una lista o un set
int sizeSetList(tData d) {
	if(returnType(d)!=ATM){
		int i=0;
		tData aux=d;
		
		//contempla el caso de cadena vacia como {} o []
		if(strlen(aux->data->atom)==0){
			return 0;
		}else{
			i++;
		}
		
		while(aux->next!=NULL){
			aux=aux->next;
			i++;
		}
	
		return i;
	}else{
		printf("\nError: Tipo de dato es un atom");
		return -1;
	}
}

//---MODULOS AUXILIARES PARA PRINT---
//muestra un atm
void printAtm(tData d){
	printf("%s", d->atom);
}

//muestra una lista
void printList(tData d){
	printf("[");
	while(d!=NULL && d->next!=NULL){
		if(returnType(d->data)==SET){
			printSet(d->data);
			printf(",");
		}else if(returnType(d->data)==LIST){
			printList(d->data);
			printf(",");
		}else {
			printAtm(d->data);
			printf(",");
		}
		d=d->next;
	}
	
	if(d!=NULL) {
		if(returnType(d->data)==SET) {
			printSet(d->data);
		}else if(returnType(d->data)==LIST) {
			printList(d->data);
		}else{
			printAtm(d->data);
		}
	}
	printf("]");
}

//muestra un set
void printSet(tData d){
	printf("{");
	while(d!=NULL && d->next!=NULL){
		if(returnType(d->data)==SET){
			printSet(d->data);
			printf(",");
		}else if(returnType(d->data)==LIST){
			printList(d->data);
			printf(",");
		}else {
			printAtm(d->data);
			printf(",");
		}
		d=d->next;
	}
	
	if(d!=NULL) {
		if(returnType(d->data)==SET) {
			printSet(d->data);
		} else if(returnType(d->data)==LIST) {
			printList(d->data);
		} else{
			printAtm(d->data);
		}
	}
	printf("}");
}
	
//---MODULOS PRINCIPALES DEL TDATA.H--

//---OPERACIONES GENERALES---	
	
//muestra un tData
void printData(tData d){
	if(d!=NULL){
		if(returnType(d)==SET){
			printSet(d);
		}else{
			if (returnType(d)==LIST){
				printList(d);
			}else{
				printAtm(d);
			}
		}
	}else{
		printf("\nEstructura vacia.");
	}
}
	
//dada una cadena crea un nuevo tData
tData newData(char *s){
	tData tree, aux, newNode;
	char *subString=(char*)malloc(sizeof(char)*1000);
	aux=(tData)malloc(sizeof(struct dataType));
	
	if(s[0]=='{'){
		tree=newNodeSetList(SET);
		s=clean(s);
		getElem(&s,&subString);
		if(subString[0]!='{' && subString[0]!='['){
			tree->data=newNodeAtom(subString);
		}else{
			tree->data=newData(subString);
		}
		while(s!=NULL){
			getElem(&s,&subString);
			newNode=newNodeSetList(SET);
			if(subString[0]!='{' && subString[0]!='['){
				newNode->data=newNodeAtom(subString);
			}else{
				newNode->data=newData(subString);
			}
			if(IN(tree,newNode->data)==0){
				insert(&tree,newNode);
			}else{
				dataFree(&newNode);
			}
		}
	}else if(s[0]=='['){
		tree=newNodeSetList(LIST);
		s=clean(s);
		getElem(&s,&subString);
		
		if(subString[0]!='{' && subString[0]!='['){
			tree->data=newNodeAtom(subString);
		}else{
			tree->data=newData(subString);
		}
		aux=tree;
		
		while(s!=NULL){
			getElem(&s,&subString);
			newNode=newNodeSetList(LIST);
			if(subString[0]!='{' && subString[0]!='['){
				newNode->data=newNodeAtom(subString);
			}else{
				newNode->data=newData(subString);
			}
			
			while(aux->next!=NULL){
				aux=aux->next;
			}
			aux->next=newNode;
			aux=tree;
		}
	}else{
		tree=newNodeAtom(s);
	}

	return tree;
}
	
//agrega toda lo contenido en un tData en otro tData vacio de un tipo indicado
tData newNestedData(tData d, int t){
	tData newNested=(tData)malloc(sizeof(struct dataType));
	newNested->nodeType=t;
	newNested->data=d;
	newNested->next=NULL;
	
	return newNested;
}
	
//obtiene una cadena de un tData
char* toStr(tData elem) {
	char* string=(char*)malloc(sizeof(char)*1000);
		
	if(returnType(elem)==SET) {
		string[0]='{';
		string[1]='\0';
		while(elem->next!=NULL) {
			if(returnType(elem->data)==ATM) {
				strcat(string,elem->data->atom);
				strcat(string,",");
			}else{
				strcat(string,toStr(elem->data));
				strcat(string,",");
			}
			elem=elem->next;
		}
		
		if(returnType(elem->data)==ATM) {
			strcat(string,elem->data->atom);
			strcat(string,"}");
		}else{
			strcat(string,toStr(elem->data));
			strcat(string,"}");
		}
	}else if(returnType(elem)==LIST) {
		string[0]='[';
		string[1]='\0';
		while(elem->next!=NULL) {
			if(returnType(elem->data)==ATM) {
				strcat(string,elem->data->atom);
				strcat(string,",");
			}else{
				strcat(string,toStr(elem->data));
				strcat(string,",");
			}
			elem=elem->next;
		}
	
		if(returnType(elem->data)==ATM) {
			strcat(string,elem->data->atom);
			strcat(string,"]");
		}else{
			strcat(string,toStr(elem->data));
			strcat(string,"]");
		}
	}else{
		strcpy(string,elem->atom);
	}
		
	return string;
}	

//obtiene el tipo de dato de un tData
int returnType(tData node){
	return node->nodeType;
}

//libera un tData
void dataFree(tData* node){
	free(*node);
}

//copia un tData
tData copyData(tData d){
	return newData(toStr(d));
}

//---OPERACIONES SET-LIST---
//dada una posicion valida devuelve un tData 
tData returnElem(tData d, int pos){
	if(d!=NULL && d->nodeType!=ATM){
		if(pos<=sizeSetList(d)){
			int n=1;
			tData aux=copyData(d);
			
			while(aux!=NULL && n<pos){
				aux=aux->next;
				n++;
			}
		
			if(pos==n && aux!=NULL){
				if(returnType(aux->data)==ATM){
					tData elem=aux->data;
					if(strlen(elem->atom)==0){
						return NULL;
					}else{
						return elem;
					}
				}else{
					return aux->data;
				}
			}else{
				free(aux);
				return NULL;
			}
		}else{
			printf("\nError: posicion invalida");
			return NULL;
		}
	}else{
		printf("\nError: tipo de dato es un atom");
		return NULL;
	}
}
	
//dado un tData devuelve 1 1 si esta vacio y 0 si no lo esta
int isEmpty(tData d){
	if(returnType(d)!=ATM){
		if(sizeSetList(d)==0){
			return 1;
		}else{
			return 0;
		}
	}else{
		printf("\nError: tipo de dato es un atom");
		return -1;
	}
}

//dado dos tData devuelve 1 si son iguales y 0 si no lo son
int isEqual(tData d1, tData d2){
	if(returnType(d1)!=ATM && returnType(d2)!=ATM){
		if(strcmp(toStr(d1),toStr(d2))==0){
			return 1;
		}else{
			return 0;	
		}
	}else{
		printf("\nError: tipo de dato es un atom");
		return -1;
	}
}

//---OPERACIONES LIST---
//devuelve el tamaño de una lista dada
int SIZEL(tData L){
	if(returnType(L)==LIST){
		return sizeSetList(L);
	}else{
		if(returnType(L)==SET)
			printf("\nError: tipo de dato es un set");
		else
			printf("\nError: tipo de dato es un atom");
		
		return -1;
	}
}

//agrega un elemento al final de la lista
void PUSH(tData L, tData elem){
	if(returnType(L)==LIST){
		if(SIZEL(L)!=0){
			tData aux=L;
			tData newElem=newNodeNull(LIST);
		
			while(aux->next!=NULL){
				aux=aux->next;
			}
			aux->next=newElem;
		
			newElem->data=copyData(elem);
		}else{
			L->data=copyData(elem);
		}
	}else{
		if(returnType(L)==SET)
			printf("\nError: tipo de dato es un set");
		else
			printf("\nError: tipo de dato es un atom");
	}
}

//devuelve el ultimo elemento de una lista y lo elimina
tData POP(tData* L){
	if(returnType(*L)==LIST){
		if(SIZEL(*L)!=0){
			tData aux=*L;
			tData ant=NULL;
			tData elem=(tData)malloc(sizeof(struct dataType));
			if(SIZEL(*L)==1){
				elem=copyData((*L)->data);
				free(*L);
				*L=newData("[]");
			}else{
				while(aux->next!=NULL){
					ant=aux;
					aux=aux->next;
				}
				elem=copyData(aux->data);
				ant->next=NULL;
				
				free(aux);
			}
			
			return elem;
		}else{
			return NULL;
		}
	}else{
		if(returnType(*L)==SET)
			printf("\nError: tipo de dato es un set");
		else
			printf("\nError: tipo de dato es un atom");
		
		return NULL;
	}
}

//---OPERACIONES SET---
//obtiene el cardinal de un set
int CARDINAL(tData S){
	if(returnType(S)==SET){
		return sizeSetList(S);
	}else{
		if(returnType(S)==LIST)
			printf("\nError: tipo de dato es un list");
		else
			printf("\nError: tipo de dato es un atom");
		
		return -1;
	}
}
	
//devuelve 1 si un elemento esta en un set 0 si no esta
int IN(tData S, tData elem){
	if(returnType(S)==SET){
		if (isEmpty(S)==0){
			tData aux=S;
			int b;
			while(aux!=NULL && (b=equals(aux->data,elem))!=1){
				aux=aux->next;
			}
			
			return b;
		}else{
			return 0;
		}
	}else{
		if(returnType(S)==LIST)
			printf("\nError: tipo de dato es un list");
		else
			printf("\nError: tipo de dato es un atom");
			
		return -1;
	}
}

//devuelve una union de dos set
tData UNION(tData A,tData B){
	if(returnType(A)==SET && returnType(B)==SET){
		tData result, aux;
		result=(tData)malloc(sizeof(struct dataType));
		
		if(sizeSetList(A)==0 && sizeSetList(B)==0){
			return newData("{}");
		}
		
		if(sizeSetList(A)==0){
			return copyData(B);
		}
		
		if(sizeSetList(B)==0){
			return copyData(A);
		}
		
		if(isEqual(A,B)==1){
			return copyData(A);
		}
		
		result=copyData(A);
		aux=B;
		
		while(aux!=NULL){
			if(IN(A,aux->data)==0){
				if(sizeSetList(result)==0){
					result->data=copyData(aux->data);
				}else{
					tData newElem=copyData(aux->data);
					newElem=newNestedData(newElem,SET);
					insert(&result,newElem);
				}
			}
			aux=aux->next;
		}
		
		return result;
	}else{
		if(returnType(A)==LIST)
			printf("\nError: tipo de dato A es un list");
		else
			printf("\nError: tipo de dato A es un atom");
		
		if(returnType(B)==LIST)
			printf("\nError: tipo de dato B es un list");
		else
			printf("\nError: tipo de dato B es un atom");
		
		return NULL;
	}
}

//devuelve la interseccion de dos set
tData INTER(tData A,tData B){
	if(returnType(A)==SET && returnType(B)==SET){
		tData result, aux;
		result=(tData)malloc(sizeof(struct dataType));
		result=newData("{}");
		
		if(sizeSetList(A)==0 || sizeSetList(B)==0){
			return result;
		}
		
		if(isEqual(A,B)==1){
			return copyData(A);
		}
		
		aux=B;
		while(aux!=NULL){
			if(IN(A,aux->data)==1){
				if(sizeSetList(result)==0){
					result->data=copyData(aux->data);
				}else{
					tData newElem=copyData(aux->data);
					newElem=newNestedData(newElem,SET);
					insert(&result,newElem);
				}
			}
			aux=aux->next;
		}
		
		return result;
	}else{
		if(returnType(A)==LIST)
			printf("\nError: tipo de dato A es un list");
		else
			printf("\nError: tipo de dato A es un atom");
		
		if(returnType(B)==LIST)
			printf("\nError: tipo de dato B es un list");
		else
			printf("\nError: tipo de dato B es un atom");
		
		return NULL;
	}
}

//devuleve la diferencia entre dos set
tData DIFF(tData A,tData B){
	if(returnType(A)==SET && returnType(B)==SET){
		tData result, aux;
		result=(tData)malloc(sizeof(struct dataType));
		result=newData("{}");
		
		if(sizeSetList(A)==0 && sizeSetList(B)==0){
			return result;
		}
		
		if(sizeSetList(A)==0){
			return result;
		}
		
		if(sizeSetList(B)==0){
			return copyData(A);
		}
		
		if(isEqual(A,B)==1){
			return result;
		}
		
		aux=A;
		
		while(aux!=NULL){
			if(IN(B,aux->data)==0){
				if(sizeSetList(result)==0){
					result->data=copyData(aux->data);
				}else{
					tData newElem=copyData(aux->data);
					newElem=newNestedData(newElem,SET);
					insert(&result,newElem);
				}
			}
			aux=aux->next;
		}
		
		return result;
	}else{
		if(returnType(A)==LIST)
			printf("\nError: tipo de dato A es un list");
		else
			printf("\nError: tipo de dato A es un atom");
		
		if(returnType(B)==LIST)
			printf("\nError: tipo de dato B es un list");
		else
			printf("\nError: tipo de dato B es un atom");
		
		return NULL;
	}
}
