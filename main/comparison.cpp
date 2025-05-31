#include <iostream>
#include <vector>
#include <chrono>
#include "factorization.hpp"
using namespace std;
using namespace std::chrono;

int main() {
    vector<uint64_t> numbers = {
        3009182572376191ULL, 1021514194991569ULL, 4000852962116741ULL,
        15196946347083ULL, 499664789704823ULL, 269322119833303ULL,
        679321846483919ULL, 96267366284849ULL, 61333127792637ULL,
        2485021628404193ULL
    };

    for (uint64_t n : numbers) {
        cout << "Число: " << n << "\n";

        //полард
        auto start_rho = high_resolution_clock::now();
        uint64_t factor_rho = rho_pollard::factor(n);
        auto end_rho = high_resolution_clock::now();
        auto dur_rho = duration_cast<milliseconds>(end_rho - start_rho).count();

        cout << "  Поллард ρ-метод: дільник = " << factor_rho
             << ", час = " << dur_rho << " мс\n";

        //сито
        auto start_qs = high_resolution_clock::now();
        uint64_t factor_qs = quadratic_sieve::factor(n);
        auto end_qs = high_resolution_clock::now();
        auto dur_qs = duration_cast<milliseconds>(end_qs - start_qs).count();

        cout << "  Метод Померанця: дільник = " << factor_qs
             << ", час = " << dur_qs << " мс\n";

        if (factor_rho == factor_qs) {
            cout << " Обидва алгоритми знайшли однаковий дільник.\n";
        } else {
            cout << "Різні дільники.\n";
        }

        cout << "------------------------------------------\n";
    }

    return 0;
}
