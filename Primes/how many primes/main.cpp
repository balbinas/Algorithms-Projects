//
//  main.cpp
//  how many primes
//
//  Created by Balbina Santana on 20/01/15.
//  Copyright (c) 2015 Balbina Santana. All rights reserved.
//

#include <iostream>
#include <math.h>
#define max 1000000
using namespace std;

int arr[max+1];//incluye
    
bool isPrime(long x){//mete a cuantos primos tiene cada rango de 1-x
    if(x==2 || x==3 || x==5 || x==7)//ahorro de trabajo, son primos
        return true;
    if(x%2==0 || x%3==0 || x%5==0 || x%7==0)//ahorro de trabajo si son multiplos de los primeros primos
        return false;
    
    for ( int i= 2; i<=sqrt(double(x)); i++)//fcn para sacar primo
        if( x%i == 0 )
            return false;
    
    return true;
    }
    
int main()
{
    int a, b;
    arr[1]=0;//a mano para facilitar los primeros
    arr[2]=1;
    arr[3]=2;
    arr[4]=2;
    arr[5]=3;
    arr[6]=3;
    arr[7]=4;
    
    for(int x=8; x<=max ; x++){
        if(isPrime(x))
        {
            arr[x]=arr[x-1]+1;
        }
        else
        {
            arr[x]=arr[x-1];
        }
    }
    
    while((cin>>a) && (cin>>b) && (a!=0) && (b!=0)){//sale si los 2 inputs son 0
        cout<< arr[b] - arr[a-1] <<endl;
    }
        return 0;
    }

