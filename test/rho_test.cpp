#include "factorization.hpp"

using namespace std;

int main() {
    rho_pollard RHO;
    cout << RHO.factor(4000852962116741);
    return 0;
}