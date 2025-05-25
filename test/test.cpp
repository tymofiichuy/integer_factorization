#include "factorization.hpp"

using namespace std;

int main(){
    quadratic_sieve QS;
    cout << QS.factor(2485021628404193);
    //cout << QS.factor(35621);
    return 0;
}