#include "factorization.hpp"

using namespace std;

int quadratic_sieve::legendre_symbol(uint64_t n, uint64_t p){
    int res = 1, counter = 0;
    uint64_t pow;

    n %= p;

    if(n==0){
        return 0;
    }
    while((n&1)==0){
        counter++;
        n >>= 1;
    }
    if(counter%2==1){
        pow = (p*p-1)/8;
        if(pow%2==1){
            res *= -1;
        }
    }        
    if(n==1){
        return res;
    }

    pow = (n-1)*(p-1)/4;
    if(pow%2==1){
        res *= -1;
    }
    res *= legendre_symbol(p, n);
    return res;
}