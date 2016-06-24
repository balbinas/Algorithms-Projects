//
//  main.cpp
//  Audiophobia
//
//  Created by Balbina Santana on 4/5/14.
//  Copyright (c) 2014 Balbina Santana A00812215. All rights reserved.
//

#include <iostream>
#include <climits>
using namespace std;

int mat[100][100];

int main(int argc, const char * argv[]){
	int x, w, c, s, q, c1, c2, d, cc1, cc2, cont=1;//c=cruceros, s=calles, q=consultas
	cin >> w;//numero de casos --what
    
	while (w--){
		cout <<"Case "<<cont <<":"<<endl;
        
		cin >>c >>s >>q;
		for (int j = 0; j < c; j++){
			for (int k = 0; k < c; k++){
				if (j == k){
                mat[j][k] = 0;
				} else {
                mat[j][k] = INT_MAX;
                }
            }
		}
        
		while (s--){
			cin >> c1 >> c2 >> d;
			mat[c1-1][c2-1] = d;
            mat[c2-1][c1-1] = d;
		}
        
        //--floyd x = D^k
        for (int k = 0; k < c; k++){
            for (int i = 0; i < c; i++){
                for (int j = 0; j < c; j++){
                    if (i != j && i!=k && j!=k){
                        x = INT_MAX;
                        if (mat[i][k] != INT_MAX && mat[k][j] != INT_MAX){
                            x = (mat[i][k] > mat[k][j])? mat[i][k] : mat[k][j];
                        }
                        if (mat[i][j] > x){
                            mat[i][j] = x;
                        }
                    }
                }
            }
        }
        
		while(q--){
			cin >>cc1 >>cc2;
			if (mat[cc1-1][cc2-1] == INT_MAX){
            cout << "no path\n";
            } else {
            cout << mat[cc1-1][cc2-1] <<"\n";
            }
		}
        cont++;
	}
}

