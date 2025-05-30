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
bool solovay_strassen::test(uint64_t p, const int& precision ){
    int k=0;
    
    uint64_t x;
    if(p%2==1){//тамдалі перевірка на псевдопростість за ойлером ітуди підхдять лише непарні
        while(k<precision){
            x=1+rand()%p;
            if(gcd(x,p)==1){
                if(x%p==p-1){//символ якобі потрібного формату при х=-1
                    k++;
                }
                else{
                    //cout<<"Число складене"<<endl;
                    return false;
                    //break;  
                }
            }
            if(gcd(x,p)>1){
                //cout<<"Число складене"<<endl;
                return false;
                //break;
            }
    
        }

    }
    else{
        //cout<<"Число складене"<<endl;
        return false;
    }
    return true;
}
