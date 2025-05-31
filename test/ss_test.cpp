#include "factorization.hpp"

using namespace std;

int main() {
    solovay_strassen SS;
    //cout << SS.test(1125897758834679, 10)
    cout << SS.test(3, 1000);
    return 0;
}
