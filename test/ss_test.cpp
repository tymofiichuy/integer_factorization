#include "factorization.hpp"

using namespace std;

int main() {
    solovay_strassen SS;
    cout << SS.test(1125897758834679, 10);
    //cout << SS.test(3184469, 1);
    return 0;
}
