//
//  main.cpp
//  Cutting Sticks
//
//  Created by Balbina Santana on 5/5/14.
//  Copyright (c) 2014 Balbina Santana. All rights reserved.
//

#include <iostream>
#include <climits>
using namespace std;
int c[50];
int costo[50][50];

int main(int argc, const char * argv[])
{
    int l, n;//l=longitud, n=num cortes, ci=lugar de cortes (incremental)
    c[0] = 0;
    
    cin >>l;//L<1000
    while(l != 0){
        cin >>n;//cortes a realizar
        
        for(int i = 0; i < n; i++){
            cin >>c[i+1];//se salta el 0 que es 0
        }
        n++;//para usarse el sig slot
        c[n] = l;
    
        for(int i = 0; i <= n+1; i++){
            for(int j = 0; j <= n+1; j++){
                costo[i][j] = INT_MAX;
            }
        }
        
        for(int i = 0; i <= n; i++){
            costo[i][i] = 0;
            costo[i][i+1] = 0;
            costo[i][i+2] = c[i+2] - c[i];
        }
        
        //para checar todos los caminos de i,j con k
        for(int k = 3; k <= n; k++) {
            for(int i = 0; i <= n-k; i++) {
                for(int j = i+1; j <= i+k-1; j++) {
                    if((costo[i][j] + costo[j][i+k] + c[i+k] - c[i]) < costo[i][i+k]) {
                        costo[i][i+k] = costo[i][j] + costo[j][i+k] + c[i+k] - c[i];//costo minimo dijsktra
                    }
                }
            }
        }
        
        cout <<"The minimum cutting is " <<costo[0][n] <<".\n";
        cin >>l;
    }
    return 0;
}

