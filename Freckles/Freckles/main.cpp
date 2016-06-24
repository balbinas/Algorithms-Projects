//
//  main.cpp
//  Freckles
//
//  Created by Balbina Santana on 5/5/14.
//  Copyright (c) 2014 Balbina Santana A00812215. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
using namespace std;

float x[1000], y[1000];//maximo 10 pecas
int arr[1000];
float ady[1000][1000];
double min = 100000000;

int main(int argc, const char * argv[])
{
    int n, cont = 0, a, b, nodo;//# pecas
    float dx, dy, h = 0;//coordenadas x,y tipo 1.0
    double min = 1000000000, acum = 0, total;//a dos decimales.... darle floor(resultado)
    
    cin >>n;
    nodo = n;
    
    acum = 0;
    for(int i = 0; i < n; i++){
        arr[i] = 0;
    }
    arr[0] = true;
    
    for(int i = 0; i < n; i++){
        cin >>x[i] >>y[i];
    }
    
    //saca la matriz de adycencias
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++){
            dx = x[i] - x[j];
            dy = y[i] - y[j];
            h = sqrt(pow(dx,2) + pow(dy,2));
            ady[i][j] = h;
        }
    }
    
    while(cont <= nodo - 1){
        min = 100000000;
        for(int i = 0; i < n; i++){
            if(arr[i] == true){
                for(int j = 0; j < n; j++){
                    if(arr[j] == false){
                        if(min > ady[i][j]){
                            min = ady[i][j];
                            a = i;
                            b = j;
                        }
                    }
                }
            }
        }
        cont++;
        
        arr[b] = true;
        
        acum = acum + ady[a][b];
        
    }
    cout << acum;
    total = (round(acum*1000)/1000);
    cout <<fixed <<setprecision(2) <<total <<"\n";
    
    
    return 0;
}