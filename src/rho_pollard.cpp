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
    list.push_back(1);
    uint64_t x;
    int t=1;
    uint64_t d=1;
    uint64_t k=0;

    while (d==1) {
        for (int i=list.size(); i<=2*t; i++) {
            list.push_back(0);
        }

        for (int i=t; i<=2*t; i++) {
            x = list[i-1];
            list[i] = (x*x+x+1) %n;
        }

        k = (list[2*t]-list[t]) %n;
        d = gcd(k,n);
        t++;
    }

    return d;
}
