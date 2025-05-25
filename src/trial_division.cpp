#include "factorization.hpp"

using namespace std;

void sieve_of_eratosthenes::joint_sieving(uint32_t high){
    flag_array.clear();
    flag_array.resize(static_cast<size_t>(high), true);
    //fill(flag_array.begin()+1, flag_array.end(), true);
    flag_array[0]=false;
    primes.clear();
    primes.reserve(high);

    uint32_t bound = static_cast<uint32_t>(sqrt(high));
    for(uint32_t i = 0; i <= bound; i++){
        if(flag_array[i]){
            primes.push_back(i+1);

            uint32_t number = i+1;
            for(uint32_t j = number*number-1; j < high; j += number){
                flag_array[j] = false;
            }
        }
    }
    for(uint32_t i = bound+1; i < high; i++){
        if(flag_array[i]){
            primes.push_back(i+1);
        }
    }

    primes.shrink_to_fit();
}

void sieve_of_eratosthenes::sieve(uint32_t high){
        joint_sieving(high);
}

uint64_t trial_division::factor(uint64_t in){
    sieve_of_eratosthenes soe;
    soe.sieve(static_cast<uint32_t>(sqrt(in)+1));

    for(vector<uint32_t>::iterator it = soe.primes.begin(); it != soe.primes.end(); it++){
        if(in%*it==0){
            return *it;
        }
    }
    return in;
}