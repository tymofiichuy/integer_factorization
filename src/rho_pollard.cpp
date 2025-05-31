#include "factorization.hpp"
#include <vector>

using namespace std;

static uint64_t gcd(uint64_t a, uint64_t b) {
    while (b!=0) {
        uint64_t r=a%b;
        a=b;
        b=r;
    }
    return a;
}

uint64_t rho_pollard::factor(uint64_t n) {
    vector<uint64_t> list;
    list.push_back(2);
    int t=1;
    uint64_t d=1;

    uint64_t x=2;
    uint64_t y=2;

    while(d==1){
        x=(x*x+1)%n;
        list.push_back(x);
        y=(y*y+1)%n;
        y=(y*y+1)%n;
        list.push_back(y);
        uint64_t diff=(x>y) ? x-y : y-x;
        d=gcd(diff, n);
        if(x==y){
            x=3;
            y=3;
            list.clear();
            list.push_back(3);
            d=1;
        }
        t++;
    }

    return d;
}
