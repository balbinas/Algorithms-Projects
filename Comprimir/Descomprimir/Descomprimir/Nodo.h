//
//  Node.h
//  Descomprimir
//
//  Created by  Balbina Santana  A00812215
//          and Erasmo Leal      A00809453
//

#ifndef Descomprimir_Nodo_h
#define Descomprimir_Nodo_h

class Nodo{

public:
    int valor;
    char letra;
    bool esIzq; //bool para saber si es el nodo de la izq
    Nodo *izq, *der, *pad;//padre
    
    Nodo(int valor, char letra, bool esIzq, Nodo* izq, Nodo* der, Nodo* pad);
};

Nodo::Nodo(int valor, char letra, bool esIzq, Nodo* izq, Nodo* der, Nodo* pad):valor(valor), letra(letra), esIzq(esIzq), izq(izq), der(der), pad(pad){}

//Clase para comparar apuntadores a Nodo para priority queue
class ComparaNodos {
public:
    bool operator()(Nodo*& izq, Nodo*& der) const {
		
		//if counts of hcnodes are different, compare them
		if (izq->valor != der->valor) {
			return izq->valor > der->valor; //return opposite > to give smaller values a higher priority
		}
		else{
			return izq->letra > der->letra;
		}
		
		return true;
    }
};
#endif
