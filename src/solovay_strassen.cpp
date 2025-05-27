#include "factorization.hpp"
#include <iostream>
#include <cstdint>
#include <numeric>

using namespace std;

static uint64_t gcd(uint64_t a, uint64_t b) {
    while (b!=0) {
        uint64_t r=a%b;
        a=b;
        b=r;
    }
    return a;
}
uint64_t sollovay_strassen::factor(uint64_t p){
    int k=0;
    
    uint64_t x;
    if(p%2==1){//тамдалі перевірка на псевдопростість за ойлером ітуди підхдять лише непарні
        while(true){
            x=1+rand()%p;
            if(gcd(x,p)==1){
                if(x%p==p-1){//символ якобі потрібного формату при х=-1
                    k++;
                }
                else{
                    cout<<"Число складене"<<endl;
                    break;  
                }
            }
            if(gcd(x,p)>1){
                cout<<"Число складене"<<endl;
                break;
            }
    
        }

    }
    else{
        cout<<"Число складене"<<endl;
    }
    return 0;
}
