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
static int jacobi(int64_t a, int64_t p) {
    if(a==0){
        return 0;
    }
    int j = 1;
    if(a<0){
        a=-a;
        if((p%4)==3){
            j=-j;
        }
    }
    while(a!=0){
        while((a%2)==0){
            a/=2;
            if((p%8)==3 || (p%8)==5){
                j=-j;
            }
        }
        swap(a, p);
        if ((a%4)==3 && (p%4)==3){
            j=-j;
        }
        a%=p;
    }
    return (p==1) ? j : 0;
}
static uint64_t mod_pow(uint64_t base, uint64_t exp, uint64_t mod) {
    uint64_t result=1;
    base=base%mod;
    while(exp>0){
        if (exp & 1){
            result=(__uint128_t)result*base%mod;
        }
        base=(__uint128_t)base*base%mod;
        exp>>=1;
    }
    return result;
}
bool solovay_strassen::test(uint64_t p, const int& precision ){
    if((p==2)||(p==3)){
        return true;
    }
    if (p%2==0){
        return false;
    }

    for(int k=0; k<precision; ++k){
        uint64_t x=2+rand()%(p - 3);
        if (gcd(x, p) > 1){
            return false;
        }

        int j=jacobi(x, p);
        if (j==0){
            return false;
        }

        uint64_t mod_exp=mod_pow(x, (p-1)/2, p);
        uint64_t j_mod_p=(j==-1)?p-1:j;

        if (mod_exp!=j_mod_p){
            return false;
        }
    }
    return true;
    }
