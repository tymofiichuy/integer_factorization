#include "factorization.hpp"

using namespace std;

int main(){
    quadratic_sieve QS;
    cout << QS.factor(3009182572376191);
    //cout << QS.factor(44377);
    return 0;
}