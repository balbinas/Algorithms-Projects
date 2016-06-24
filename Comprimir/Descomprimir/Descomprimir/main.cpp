//
//  main.cpp
//  Descomprimir
//
//  Created by  Balbina Santana  A00812215
//          and Erasmo Leal      A00809453
//

#include <iostream>
#include <fstream>
#include <queue>
#include <math.h>
#include <iomanip>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Nodo.h"

using namespace std;

//ya hecho
#define BITS 12                   /* Setting the number of bits to 12, 13*/
#define HASHING_SHIFT (BITS-8)    /* or 14 affects several constants.    */
#define MAX_VALUE (1 << BITS) - 1 /* Note that MS-DOS machines need to   */
#define MAX_CODE MAX_VALUE - 1    /* compile their code in large model if*/
/* 14 bits are selected.               */
#if BITS == 14
#define TABLE_SIZE 18041        /* The string table size needs to be a */
#endif                            /* prime number that is somewhat larger*/
#if BITS == 13                    /* than 2**BITS.                       */
#define TABLE_SIZE 9029
#endif
#if BITS <= 12
#define TABLE_SIZE 5021
#endif
int *code_value;                  /* This is the code value array        */
unsigned int *prefix_code;        /* This array holds the prefix codes   */
unsigned char *append_character;  /* This array holds the appended chars */
unsigned char decode_stack[4000]; /* This array holds the decoded string */

/* -------HUFFMAN------- */

//para Huffman
Nodo *arr[256];
Nodo *raiz;
int newSizeH = 0;//para checar porcentaje antes
int oldSizeH = 0;//checar porcentaje despues

//arbol Huffman
void huffTree(int cont[] ){
    //iniciar PQ manejar sorting +eficiente = arboles chicos
    priority_queue<Nodo *, vector<Nodo*>, ComparaNodos> pq;
    
    for(int i=0; i < 256; i++){
        if (cont[i] > 0) {//no gastar memoria checando los que no tienen valor
            arr[i] = new Nodo(cont[i], (char) i, false, NULL, NULL, NULL);//valor, letra, izq(!), pointers izq,der,padre

            pq.push(arr[i]); //meter Nodo en priority queue
    
        }
    }
    
    while (pq.size() > 1) {//empezar con nodos individuales, cuando queda 1 = arbol completo
        Nodo* izq = pq.top();
        pq.pop();
        
        Nodo* der = pq.top();
        pq.pop();
        
        //crear nuevo Nodo para ser el padre de los nodos previos
        Nodo* t = new Nodo(izq->valor + der->valor, izq->letra, false, NULL, NULL, NULL);
        
        izq->esIzq = true;
        t->izq = izq;//cambia a nodo padre
        t->der = der;
        
        izq->pad = t;//t = nuevo nodo padre
        der->pad = t;
        
        pq.push(t);//nuevo padre a pq
    }
    
    raiz = pq.top();//terminado, ultimo nodo = raiz y se asigna
    
}

//codificador Huffman
void codH( char letra, ofstream& EscribirH ){//H por Huffman
    vector<int> code;
	Nodo *nodoAct = arr[letra];
    
	while (nodoAct->pad != NULL) {
		if (nodoAct->esIzq) {
			//si es izq(0) = push a 0 to vector
			code.push_back(0);
		}
		else{
			//si es der(1) = push a 1 to vector
			code.push_back(1);
		}
		nodoAct = nodoAct->pad;
	}
	
	//se genera el codigo al reves
	int i;
	for (i = (int)code.size() - 1; i>=0; i--) {
		EscribirH << code[i];
	}
    
    newSizeH += (int)code.size();
}

//Decodificador Huffman
void decodH( ifstream& LeerH, ofstream& EscribirH ){
	Nodo *nodoAct = raiz;
    
    char aux[1];
    while (LeerH.read(aux, 1)) {
        if (aux[0] == '0') {
            if (nodoAct->izq != NULL) {
                nodoAct = nodoAct->izq;//checar si se llego hasta abajo para imprimir char y regresar a raiz
                if (nodoAct->izq == NULL) {
                    EscribirH << nodoAct->letra;
                    nodoAct = raiz;
                }
            }
        } else {
            if (nodoAct->der != NULL) {
                nodoAct = nodoAct->der;//checar si se llego hasta abajo para imprimir char y regresar a raiz
                if (nodoAct->der == NULL) {
                    EscribirH << nodoAct->letra;
                    nodoAct = raiz;
                }
            }
        }
    }
    
}

void Huffman(string nameH)
{
    
    
    /* -----EMPEZAMOS CON EL ALGORITMO HUFFMAN----- */
    
    int cont[256];//contar
    
    //string nameH;
    fill_n(cont, 256, 0);
    
    ifstream LeerH;
    //cin >>nameH;
    LeerH.open("/Users/Balbina/Documents/6to semestre/Algoritmos/Comprimir/Descomprimir/Descomprimir/"+nameH+".txt");
    
    if (LeerH.is_open()) {
		char aux[1];
		while (LeerH.read(aux, 1)) {
            cont[aux[0]]++;
            oldSizeH++;
		}
        LeerH.close();
        
        huffTree(cont);
        
        ofstream EscribirH;
        EscribirH.open("/Users/Balbina/Documents/6to semestre/Algoritmos/Comprimir/Descomprimir/Descomprimir/"+nameH+".huf");
        
        if (EscribirH.is_open()) {
            LeerH.open("/Users/Balbina/Documents/6to semestre/Algoritmos/Comprimir/Descomprimir/Descomprimir/"+nameH+".txt");
            
            if (LeerH.is_open()) {
                while (LeerH.read(aux, 1)) {
                    codH(aux[0], EscribirH);
                }
            }
            
            LeerH.close();
        }
        
        EscribirH.close();
        
        LeerH.open("/Users/Balbina/Documents/6to semestre/Algoritmos/Comprimir/Descomprimir/Descomprimir/"+nameH+".huf");
        if (LeerH.is_open()) {
            EscribirH.open("/Users/Balbina/Documents/6to semestre/Algoritmos/Comprimir/Descomprimir/Descomprimir/"+nameH+"2.txt");
            if (EscribirH.is_open()) {
                decodH(LeerH, EscribirH);
            }
            EscribirH.close();
        }
        LeerH.close();
        
        double porcentaje = ( 1 - ( ceil(newSizeH/8) / oldSizeH ) )*100;
        cout << "Porcentaje Huffman: " << fixed << setprecision(1) << porcentaje << "%" << endl;
	}
	else{
		cout << "Error opening \"" << nameH << "\"." << endl;
		LeerH.close();
	}

    //meterlo en arbol de nodos
};


/* -------LZW------- */

//para LZW
Nodo *arr2[256];
Nodo *raiz2;
int newSizeL = 0;//para checar porcentaje antes
int oldSizeL = 0;//checar porcentaje despues

//codificador LZW
void codL( ifstream& LeerL, ofstream& EscribirL ){//L por LZW
}

//Decodificador LZW
void decodL( ifstream& LeerL, ofstream& EscribirL ){
	Nodo *nodoAct = raiz;
    
    char aux[1];
    while (LeerL.read(aux, 1)) {
        if (aux[0] == '0') {
            if (nodoAct->izq != NULL) {
                nodoAct = nodoAct->izq;//checar si se llego hasta abajo para imprimir char y regresar a raiz
                if (nodoAct->izq == NULL) {
                    EscribirL << nodoAct->letra;
                    nodoAct = raiz;
                }
            }
        } else {
            if (nodoAct->der != NULL) {
                nodoAct = nodoAct->der;//checar si se llego hasta abajo para imprimir char y regresar a raiz
                if (nodoAct->der == NULL) {
                    EscribirL << nodoAct->letra;
                    nodoAct = raiz;
                }
            }
        }
    }
    
}


void LZW(string nameL)
{
    
    /* -----EMPEZAMOS CON EL ALGORITMO LZW----- */
    
    int dic[256];//diccionario
    
    //string nameL;
    fill_n(dic, 256, 0);
    
    vector<string> diccionario;
	for (char i = 'a'; i <= 'z'; i++)
		diccionario.push_back(string(1,i));
	for (char i = 'A'; i <= 'Z'; i++)
		diccionario.push_back(string(1,i));
    
    ifstream LeerL;
    LeerL.open("/Users/Balbina/Documents/6to semestre/Algoritmos/Comprimir/Descomprimir/Descomprimir/"+nameL+".txt");
    
    if (LeerL.is_open()) {
		char aux2[1];//un buffer para LZW
		while (LeerL.read(aux2, 1)) {
            dic[aux2[0]]++;
            oldSizeH++;
		}
        LeerL.close();
        
        ofstream EscribirL;
        EscribirL.open("/Users/Balbina/Documents/6to semestre/Algoritmos/Comprimir/Descomprimir/Descomprimir/"+nameL+".lzw");
        
        if (EscribirL.is_open()) {
            LeerL.open("/Users/Balbina/Documents/6to semestre/Algoritmos/Comprimir/Descomprimir/Descomprimir/"+nameL+".txt");
            
            if (LeerL.is_open()) {
                while (LeerL.read(aux2, 1)) {
                    codH(aux2[0], EscribirL);
                }
            }
            
            LeerL.close();
        }
        
        EscribirL.close();
        
        LeerL.open("/Users/Balbina/Documents/6to semestre/Algoritmos/Comprimir/Descomprimir/Descomprimir/"+nameL+".lzw");
        if (LeerL.is_open()) {
            EscribirL.open("/Users/Balbina/Documents/6to semestre/Algoritmos/Comprimir/Descomprimir/Descomprimir/"+nameL+"3.txt");
            if (EscribirL.is_open()) {
                decodH(LeerL, EscribirL);
            }
            EscribirL.close();
        }
        LeerL.close();
        
        double porcentaje = ( 1 - ( ceil(newSizeL/8) / oldSizeL ) )*100;
        cout << "Porcentaje LZW: " << fixed << setprecision(1) << porcentaje << "%" << endl;
	}
	else{
		cout << "Error opening \"" << nameL << "\"." << endl;
		LeerL.close();
	}
};


int main(int argc, const char * argv[])
{
    string name;
    cin >> name;
    
    Huffman(name);
    //LZW(name);
    return 0;
};

