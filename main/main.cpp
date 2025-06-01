#include "factorization.hpp"
#include <iostream>
#include <vector>
#include <chrono>
#include <memory>
#include <iomanip>

using namespace std;
using namespace std::chrono;

bool is_prime(uint64_t n) {
    solovay_strassen primality;
    return primality.test(n, 10);
}

void factorize(uint64_t n, vector<uint64_t>& result) {
    auto timestamp = []() {
        auto now = system_clock::to_time_t(system_clock::now());
        tm* ptm = localtime(&now);
        char buffer[32];
        strftime(buffer, 32, "%H:%M:%S", ptm);
        return string(buffer);
    };

    if (is_prime(n)) {
        // cout << "[" << timestamp() << "] Просте число: " << n << endl;
        cout << "[" << timestamp() << "] Prime number: " << n << endl;
        result.push_back(n);
        return;
    }

    // (б) Метод пробних дiлень
    {
        unique_ptr<factorization_algorithm> trial = make_unique<trial_division>();
        auto start = high_resolution_clock::now();
        uint64_t d = trial->factor(n);
        auto end = high_resolution_clock::now();
        if (d != n && d != 1) {
            // cout << "[" << timestamp() << "] Дільник (trial_division): " << d
            //      << ", час: " << duration_cast<milliseconds>(end - start).count() << " мс" << endl;
            cout << "[" << timestamp() << "] Divisor (trial_division): " << d
                 << ", time: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;                
            factorize(d, result);
            factorize(n / d, result);
            return;
        }
    }

    // (в) Метод Полларда
    {
        unique_ptr<factorization_algorithm> rho = make_unique<rho_pollard>();
        auto start = high_resolution_clock::now();
        uint64_t d = rho->factor(n);
        auto end = high_resolution_clock::now();

        if (d != n && d != 1) {
            // cout << "[" << timestamp() << "] Дільник (rho_pollard): " << d
            //      << ", час: " << duration_cast<milliseconds>(end - start).count() << " мс" << endl;
            cout << "[" << timestamp() << "] Divisor (rho_pollard): " << d
                 << ", time: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl; 
            factorize(d, result);
            factorize(n / d, result);
            return;
        }
    }

    // (г) Повторна перевірка на простоту
    if (is_prime(n)) {
        // cout << "[" << timestamp() << "] Просте число: " << n << endl;
        cout << "[" << timestamp() << "] Prime number: " << n << endl;
        result.push_back(n);
        return;
    }

    // (д) Квадратне сито
    {
        unique_ptr<factorization_algorithm> qs = make_unique<quadratic_sieve>();
        auto start = high_resolution_clock::now();
        uint64_t d = qs->factor(n);
        auto end = high_resolution_clock::now();

        if (d != n && d != 1) {
            // cout << "[" << timestamp() << "] Дільник (quadratic_sieve): " << d
            //      << ", час: " << duration_cast<milliseconds>(end - start).count() << " мс" << endl;
            cout << "[" << timestamp() << "] Divisor (quadratic_sieve): " << d
                 << ", time: " << duration_cast<milliseconds>(end - start).count() << " ms" << endl;
            if(d == 0){
                factorize(n, result);
            }
            else{
                factorize(d, result);
                factorize(n / d, result);                
            }
            return;
        } else {
            // cout << "[" << timestamp() << "] Я не можу знайти канонічний розклад числа :(" << endl;
            cout << "[" << timestamp() << "] I can't find canonical representation :(" << endl;
        }
    }
}

int main() {
    uint64_t n;
    // cout << "Введіть число: ";
    cout << "Enter number: ";
    cin >> n;

    auto start_time = chrono::system_clock::now();
    vector<uint64_t> result;

    factorize(n, result);

    auto end_time = chrono::system_clock::now();
    time_t start_c = chrono::system_clock::to_time_t(start_time);
    time_t end_c = chrono::system_clock::to_time_t(end_time);

    // cout << "\nКанонічний розклад: ";
    cout << "\nCanonical representation: ";
    for (uint64_t d : result)
        cout << d << " ";
    cout << endl;

    // cout << "Час початку: " << put_time(localtime(&start_c), "%H:%M:%S") << endl;
    // cout << "Час завершення: " << put_time(localtime(&end_c), "%H:%M:%S") << endl;
    cout << "Start: " << put_time(localtime(&start_c), "%H:%M:%S") << endl;
    cout << "End: " << put_time(localtime(&end_c), "%H:%M:%S") << endl;
    return 0;
}
