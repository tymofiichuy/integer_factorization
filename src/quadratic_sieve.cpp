#include "factorization.hpp"
#include "f_exeption.hpp"
#include <long_arithmetic.hpp>
#include <set>

using namespace std;

// int quadratic_sieve::legendre_symbol(int64_t n, int64_t p){
//     int res = 1, counter = 0;
//     uint64_t pow;

//     n %= p;

//     if(n==0){
//         return 0;
//     }
//     while((n&1)==0){
//         counter++;
//         n >>= 1;
//     }
//     if(counter%2==1){
//         pow = (p*p-1)/8;
//         if(pow%2==1){
//             res *= -1;
//         }
//     }        
//     if(n==1){
//         return res;
//     }

//     pow = (n-1)*(p-1)/4;
//     if(pow%2==1){
//         res *= -1;
//     }
//     res *= legendre_symbol(p, n);
//     return res;
// }

void quadratic_sieve::set_base(vector<uint32_t>& primes){
    base.reserve(primes.size());
    for(auto it = primes.begin(); it != primes.end(); it++){
        int ls = tonelli_shanks::legendre_symbol(N, *it);
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
    int64_t sq = static_cast<int64_t>(sqrt(N)), mod_sq = 0;
    int64_t a, b;
    int counter = 0, size = static_cast<int>(base.size())+1;

    vector<int> temp(base.size()+1, 0);
    matrix temp_mtr(size);
    coef_mtr = move(temp_mtr);

    // while(true){
    //     for (int sign : {1, -1}){
    //         a = sign*interval + sq;
    //         b = a*a-static_cast<int64_t>(N);
    //         if(base_probe_division(temp, b)){
    //             a_vector.push_back(a);
    //             b_vector.push_back(b);
    //             for(int i = 0; i < size; i++){
    //                 coef_mtr.mtr[i][counter] = temp[i];
    //             }
    //             counter++;
    //         }
    //         if(counter == size){
    //             break;
    //         }            
    //     }
    //     if(counter == size){
    //         break;
    //     }
    //     else{
    //         interval++;  
    //     }
    // }

    int64_t interval = 20*base.size();
    vector<set<double>> logarithms;
    logarithms.resize(2*interval);
    int64_t gen_solution = 0, solution = 0;
    for(int it = 1; it < base.size(); it++){
        mod_sq = sq%base[it];
        gen_solution = tonelli_shanks::quad_congruence(0, N, base[it]);
        //cout << gen_solution << " " << N%base[it] << " " << base[it] << "\n";
        solution = gen_solution-mod_sq;
        for(int64_t i = ((-interval-solution)/(base[it]))+1; i < ((interval-solution)/(base[it]))-1; i++){
            logarithms[solution+i*base[it]+interval].insert(static_cast<double>(log10(base[it])));
        }
        solution = base[it]-gen_solution-mod_sq;
        for(int64_t i = ((-interval-solution)/(base[it]))+1; i < ((interval-solution)/(base[it]))-1; i++){
            logarithms[solution+i*base[it]+interval].insert(static_cast<double>(log10(base[it])));
        }
    }

    double Q = 0;
    for(int i = 1; i <= interval; i++){
        for (int sign : {1, -1}){
            a = sign*i + sq;
            b = a*a-static_cast<int64_t>(N);
            Q = static_cast<double>(log10(abs(b)));
            switch(sign){
                case 1:
                    for(auto it = logarithms[i*sign+interval-1].begin(); it != logarithms[i*sign+interval-1].end(); it++){
                        Q -= *it;
                    } 
                    break;
                case -1:
                    for(auto it = logarithms[i*sign+interval].begin(); it != logarithms[i*sign+interval].end(); it++){
                        Q -= *it;
                    } 
                    break;                   
            }
            //cout << Q << " ";
            if(abs(Q)<1.5f){
                if(base_probe_division(temp, b)){
                        a_vector.push_back(a);
                        b_vector.push_back(b);
                        for(int i = 0; i < size; i++){
                            coef_mtr.mtr[i][counter] = temp[i];
                        }
                        counter++;
                    }
                if(counter == size){
                    //cout << i << " " << counter << " ";
                    return;
                }            
            }
        }
    }
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
    }
}

uint64_t quadratic_sieve::factor(uint64_t in){
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
                modular_arithmetic::long_mod_add(res_x, res_y, mod, mu, temp);
                if(temp == long_int(0, 2)){
                    continue;
                }
                modular_arithmetic::steins_algorithm(temp, mod, temp);
                if(temp == long_int(1,2)){
                    continue;
                }
                else{
                    return temp.get_low_digit();
                    break;
                }
            }
            row++;
        }
    }
    return 0;
}