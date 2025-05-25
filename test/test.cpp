#include "factorization.hpp"

using namespace std;

int main(){
    quadratic_sieve QS;
    cout << QS.factor(2485021628404193);
    return 0;
}