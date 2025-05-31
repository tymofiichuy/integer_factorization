#include "tonelli_shanks.hpp"
#include<long_arithmetic.hpp>
#include<random>


using namespace std;

// int tonelli_shanks::legendre_symbol(int64_t n, int64_t p){
//     int res = 1, counter = 0;
//     long_int l_pow(1,2);
//     uint64_t low;

//     n %= p;

//     if(n==0){
//         return 0;
//     }
//     while((n&1)==0){
//         counter++;
//         n >>= 1;
//     }
//     if(counter%2==1){
//         //pow = (p*p-1)/8;
//         l_pow = p;
//         long_arithmetic::long_multiply(l_pow, l_pow, l_pow);
//         long_arithmetic::long_sub(l_pow, long_int(1,2), l_pow);
//         low = l_pow.get_low_digit();
//         if((low>>3)%2==1){
//             res *= -1;
//         }
//     }        
//     if(n==1){
//         return res;
//     }

//     //pow = (n-1)*(p-1)/4;
//     l_pow = p-1;
//     long_arithmetic::long_multiply(l_pow, long_int(n-1,2), l_pow);
//     low = l_pow.get_low_digit();
//     if((low>>2)%2==1){
//         res *= -1;
//     }
//     res *= legendre_symbol(p, n);
//     return res;
// }

int tonelli_shanks::legendre_symbol(int64_t n, int64_t p){
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

int64_t tonelli_shanks::quad_congruence(int64_t a, int64_t n, int64_t mod){
    n %= mod;

    if(tonelli_shanks::legendre_symbol(n, mod) != 1){
        return 0;
    }

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int64_t> dist(2, mod-1);
    int64_t temp_mod = mod-1, s = 0, z = 0, i = 0, temp_pow = 0;
    while((temp_mod&1) == 0){
        temp_mod>>=1;
        s++;
    }
    while(true){
        z = dist(mt);
        if(tonelli_shanks::legendre_symbol(z, mod) == -1){
            break;
        }
    }

    long_int mu, l_mod(mod, 2), l_c(z,2), l_T(n,2), l_R(n,2), l_pow(1,2), l_temp1(1,2), l_temp2(1,2);
    l_pow = temp_mod;
    modular_arithmetic::long_mod_power(l_c, l_pow, l_mod, l_c);
    modular_arithmetic::long_mod_power(l_T, l_pow, l_mod, l_T);
    long_arithmetic::long_add(l_pow, long_int(1,2), l_pow);
    long_arithmetic::long_divide(l_pow, long_int(2,2), l_temp1, l_pow);
    modular_arithmetic::long_mod_power(l_R, l_pow, l_mod, l_R);

    modular_arithmetic::mu_calc(l_mod, mu);
    long_int l_b(1,2);
    while(true){
        if(l_T == long_int(0,2)){
            return 0;
        }
        if(l_T == long_int(1,2)){
            return l_R.get_low_digit();
        }
        while(true){
            if(l_T == long_int(1,2)){
                break;
            }
            i++;
            l_temp1 = l_T;
            l_temp2 = l_T;
            modular_arithmetic::long_mod_multiply(l_temp1, l_temp2, l_mod, mu, l_T);
        }

        l_pow = pow(2, s - i - 1);
        modular_arithmetic::long_mod_power(l_c, l_pow, l_mod, l_b);
        s = i;
        l_temp1 = l_b;
        l_temp2 = l_b;
        modular_arithmetic::long_mod_multiply(l_temp1, l_temp2, l_mod, mu, l_c);
        l_temp1 = l_T;
        modular_arithmetic::long_mod_multiply(l_temp1, l_c, l_mod, mu, l_T);
        l_temp1 = l_R;
        modular_arithmetic::long_mod_multiply(l_temp1, l_b, l_mod, mu, l_R);        
    }
}