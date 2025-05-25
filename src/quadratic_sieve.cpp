#include "factorization.hpp"
#include "f_exeption.hpp"
#include <long_arithmetic.hpp>

using namespace std;

int quadratic_sieve::legendre_symbol(int64_t n, int64_t p){
    int res = 1, counter = 0;
    uint64_t pow;

    n %= p;

    if(n==0){
        return 0;
    }
    while((n&1)==0){
        counter++;
        n >>= 1;
    }
    if(counter%2==1){
        pow = (p*p-1)/8;
        if(pow%2==1){
            res *= -1;
        }
    }        
    if(n==1){
        return res;
    }

    pow = (n-1)*(p-1)/4;
    if(pow%2==1){
        res *= -1;
    }
    res *= legendre_symbol(p, n);
    return res;
}

void quadratic_sieve::set_base(vector<uint32_t>& primes){
    base.reserve(primes.size());
    for(auto it = primes.begin(); it != primes.end(); it++){
        int ls = legendre_symbol(N, *it);
        switch(ls){
            case 0:
                throw factor_exception(*it);
                break;
            case 1:
                base.push_back(*it);
                break;
            case -1:
                break;
        }
    }
    base.shrink_to_fit();

    //remove later!!!
    // for(int i = 0; i < base.size(); i++){
    //     cout << base[i] << " ";
    // }
    // cout << "\n";
}

bool quadratic_sieve::base_probe_division(vector<int>& coefficients, int64_t number){
    coefficients.assign(coefficients.size(), 0);
    int index = 1;

    if(number < 0){
        coefficients[0] = 1;
        number = -number;
    }

    for(auto it = base.begin(); it != base.end(); it++){
        while(number%*it==0){
            number/=*it;
            coefficients[index]++;
        }
        index++;
    }
    return number==1;
}

void quadratic_sieve::set_matrix(){
    int64_t sq = static_cast<int64_t>(sqrt(N));
    int64_t a, b;
    int counter = 0, size = static_cast<int>(base.size())+1;

    vector<int> temp(base.size()+1, 0);
    matrix temp_mtr(size);
    coef_mtr = move(temp_mtr);

    while(true){
        for (int sign : {1, -1}){
            a = sign*interval + sq;
            b = a*a-static_cast<int64_t>(N);
            if(base_probe_division(temp, b)){
                a_vector.push_back(a);
                b_vector.push_back(b);
                for(int i = 0; i < size; i++){
                    coef_mtr.mtr[i][counter] = temp[i];
                }
                counter++;
            }
            if(counter == size){
                break;
            }            
        }
        if(counter == size){
            break;
        }
        else{
            interval++;  
        }
    }
    // for(int i = 0; i < coef_mtr.get_size(); i++){
    //     for(int j = 0; j < coef_mtr.get_size(); j++){
    //         cout << coef_mtr.mtr[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    // cout << "\n";
}

void quadratic_sieve::gaussian_elimination(){
    int size = coef_mtr.get_size(), pivot;
    echelon_mtr = coef_mtr;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            //echelon_mtr.mtr[i][j] %= echelon_mtr.mtr[i][j];
            echelon_mtr.mtr[i][j] %= 2;
        }
    }
    for(int col = 0; col < size; col++){
        pivot = echelon_mtr.find_pivot(col);
        if(pivot == size){
            continue;
        }
        else{
            echelon_mtr.swap(col, pivot);
            for(int i = 0; i < size; i++){
                if(echelon_mtr.mtr[i][col]==1&&i!=col){
                    //(i, col)?
                    echelon_mtr.inplace_row_xor(col, i);
                }
            }            
        }
        // remove later!!!
        // for(int i = 0; i < echelon_mtr.get_size(); i++){
        //     for(int j = 0; j < echelon_mtr.get_size(); j++){
        //         cout << echelon_mtr.mtr[i][j] << " ";
        //     }
        //     cout << "\n";
        // }
        // cout << "\n";
    }
    // for(int i = 0; i < echelon_mtr.get_size(); i++){
    //     for(int j = 0; j < echelon_mtr.get_size(); j++){
    //         cout << echelon_mtr.mtr[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    // cout << "\n";
}

int64_t quadratic_sieve::factor(int64_t in){
    int row = -1;
    bool flag;
    matrix temp_mtr;
    vector<bool> solution;

    N = in;
    sieve_of_eratosthenes soe;
    //change later!!!
    //soe.sieve(50);
    soe.sieve(static_cast<uint32_t>(pow(exp(sqrt(log2(N)*log2(log2(N)))), (1.0/sqrt(2)))));
    try{
        set_base(soe.primes);        
    }
    catch(factor_exception err){
        return err.factor;
    }
    set_matrix();
    gaussian_elimination();
    solution.resize(echelon_mtr.get_size());
    
    // remove later!!!
    // for(int i = 0; i < a_vector.size(); i++){
    //     cout << a_vector[i] << "--" << b_vector[i] << " ";
    // }
    // cout << "\n";

    while(true){
        temp_mtr = echelon_mtr;
        solution.assign(solution.size(), false);
        flag = true;
        row = echelon_mtr.find_zero_row(row+1);
        if(row == -1){
            return 0;
            break;
        }
        else{
            solution[row] = true;
            for(int i = 0; i < echelon_mtr.get_size(); i++){
                if(temp_mtr.mtr[i][row]){
                    if(echelon_mtr.mtr[i][i]){
                        temp_mtr.inplace_col_xor(i,row);
                    }
                    else{
                        flag = false;
                        row++;
                        break;
                    }
                    solution[i] = true;
                }
            }
            if(flag){
                // for(int i = 0; i < solution.size(); i++){
                //     cout << solution[i] << " ";
                // }
                // cout << "\n";
                //form (X, Y) pair
                vector<int> powers;
                powers.resize(base.size());
                long_int res_x(1,2), res_y(1,2), mod(static_cast<uint64_t>(N), 2), temp(1,2), mu(1,2);
                modular_arithmetic::mu_calc(mod, mu);
                for(int i = 0; i < base.size()+1; i++){
                    if(solution[i]){
                        long_arithmetic::long_multiply(res_x, long_int(a_vector[i], 2), res_x);
                        long_arithmetic::long_divide(res_x, mod, res_x, temp);

                        for(int j = 0; j < base.size(); j++){
                            powers[j] += coef_mtr.mtr[j+1][i];
                        }                        
                    }
                }
                for(int i = 0; i < base.size(); i++){ 
                    powers[i] /= 2;                          
                    temp = base[i];
                    modular_arithmetic::long_mod_power(temp, long_int(powers[i],2), mod, temp);
                    long_arithmetic::long_multiply(res_y, temp, res_y);
                    long_arithmetic::long_divide(res_y, mod, res_y, temp);
                }
                //find solution
                // res_x.print_int();
                // res_y.print_int();
                modular_arithmetic::long_mod_add(res_x, res_y, mod, mu, temp);
                if(temp == long_int(0, 2)){
                    continue;
                }
                // temp.print_int();
                // mod.print_int();
                modular_arithmetic::steins_algorithm(temp, mod, temp);
                if(temp == long_int(1,2)){
                    continue;
                }
                else{
                    //temp.print_int();
                    return temp.get_low_digit();
                    break;
                }
            }
            row++;
        }
    }
    return 0;
}