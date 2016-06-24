//
//  main.cpp
//  Common Permutation
//
//  Created by Balbina Santana on 4/5/14.
//  Copyright (c) 2014 Balbina Santana. All rights reserved.
//

#include <iostream>
using namespace std;

int main(int argc, const char * argv[])
{
    int casos;
    string x, y;
    int let;
    char letra;
    int arr[26];
    int arr1[26];
    
    cin >> casos;
    while(casos--){
        cin >>x >>y;
        
        for(int i=0; i < 26; i++){
            arr[i] = arr1[i] = 0;
        }
        
        for(int j=0; j < x.length(); j++){
            arr[x[j]-'a']++;
        }
        
        for(int j=0; j < y.length(); j++){
            arr1[y[j]-'a']++;
        }
        
        for(int i=0; i<26; i++){
            if(arr[i]!=0 && arr1[i]!=0){
                if(arr[i] < arr1[i]){
                    let = arr[i];
                } else {
                    let = arr1[i];
                }
                for(int k=1; k<=let; k++){
                    letra = 'a' + i;
                    cout<< letra;
                }
            }
        }
        cout <<"\n";
    }
    
}

