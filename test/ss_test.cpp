#include "factorization.hpp"

using namespace std;

int main() {
    solovay_strassen SS;
    cout << SS.test(7442109405582674149, 10);
    //cout << SS.test(5, 10);
    return 0;
}
