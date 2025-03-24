#pragma once

#include<iostream>
#include<vector>
#include<cmath>
#include<string>
#include"matrix.hpp"

class primality_test{
public:
    virtual bool test(uint64_t in, const int& precision);

    primality_test() = default;
    virtual ~primality_test() = default;
};

class solovay_strassen final:public primality_test{
private:
public:
    bool test(uint64_t in, const int& precision) override;
};

class factorization_algorithm{
public:
    virtual uint64_t factor(uint64_t in) = 0;

    factorization_algorithm() = default;
    virtual ~factorization_algorithm() = default;
};

class trial_division final:public factorization_algorithm{
private:
public:
    uint64_t factor(uint64_t in) override;
};

class rho_pollard final:public factorization_algorithm{
private:
public:
    uint64_t factor(uint64_t in) override;
};

class quadratic_sieve final:public factorization_algorithm{
private:
    uint64_t N;

    vector<uint32_t> base;
    matrix coef_mtr;
    matrix echelon_mtr;
    int interval = 0;

    int legendre_symbol(uint64_t n, uint64_t p);
    void set_base(vector<uint32_t>& primes);

    //coefficients array size must match base size!
    bool base_probe_division(vector<int>& coefficients, int number);
    void set_matrix();
    void gaussian_elimination();  
public:
    uint64_t factor(uint64_t in) override;
};

class sieve_of_eratosthenes{
private:
    std::vector<bool> flag_array;

    void joint_sieving(uint32_t high);
    void segment_sieving(uint32_t low, uint32_t high);
public:
    bool segmentation = false;
    std::vector<uint32_t> primes;

    void sieve(uint32_t high);
};