#include "factorization.hpp"

using namespace std;

int main(){
    sieve_of_eratosthenes sve;

    sve.sieve(100);
    size_t sz = sve.primes.size();
    for(int i = 0; i < sz; i++){
        cout << sve.primes[i] << " ";
    }

    return 0;
}