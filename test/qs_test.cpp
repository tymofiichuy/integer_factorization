#include "factorization.hpp"

using namespace std;

int main(){
    quadratic_sieve QS;
    cout << QS.factor(1021514194991569);
    return 0;
}