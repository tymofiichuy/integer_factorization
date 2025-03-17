#pragma once

#include<iostream>

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
public:
    uint64_t factor(uint64_t in) override;
};