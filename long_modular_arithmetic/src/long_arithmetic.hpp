#pragma once

#include<stdint.h>
#include<string>
#include<random>

class digit{
private:
    void operator>>(int);
    void operator<<(int);
    //dynamic allocated memory!
    digit* digit_split();
    //dynamic allocated memory!
    digit* digit_mult(digit);
public:
    uint64_t value;
    digit(uint64_t = 0);

    friend class long_arithmetic;
    friend class long_int;
};

class long_int{
private:
    digit* digits;
    int size;
public:
//Shifts and bit/digit operations
    //shift whithin digits
    void long_upper_sub_shift(int);
    void long_lower_sub_shift(int);
    //digit shift
    void long_upper_super_shift(int);
    void long_lower_super_shift(int);
    void set_bit(int value, int position);
    bool get_bit(int position);
    bool even();
    void reset();
    int digit_length();
    int bit_length();
    int get_size();  

//IO
    void read_long_int(std::string);
    uint64_t get_low_digit();
    void print_int();

//Adaptive size
    void resize(int new_size);
    void resize_erase(int new_size);
    //Reduce size to minimal without loosing data
    void reduce_size();

//Operators
    void operator>>(int);
    void operator<<(int);
    bool operator==(long_int&);
    long_int& operator=(long_int&);
    //recheck
    long_int& operator=(long_int&&);
    long_int& operator=(uint64_t&);
    digit& operator[](int);

//Integer split
    void split(long_int& out1, long_int& out2);

//Partition
    void get_high(long_int& out, int part);
    void rewrite_high(long_int& in);

//Constructors/Destructor
    void random_integer(uint64_t from, long_int& to, std::mt19937_64& mt);
    void random_integer(std::mt19937_64& mt, int digit_len = 32);
    long_int(uint64_t init_value = 0, uint8_t init_size = 32);
    long_int(long_int&);
    ~long_int();

    friend class long_arithmetic;
    friend class modular_arithmetic;
};

class long_arithmetic{
public:
    static void adjust_size(long_int& in1, long_int& in2);
    // static void adjust_reduce_size(long_int& in1, long_int& in2);
    // static void adjust_reduce_even_size(long_int& in1, long_int& in2);
    
    //next functions return is a last carry/borrow bit
    static unsigned char long_add(long_int in1, long_int in2, long_int& out, unsigned char carry_bit = 0);
    static unsigned char long_sub(long_int in1, long_int in2, long_int& out, unsigned char borrow_bit = 0);

    static void long_multiply_by_one_digit(long_int& long_in, digit digit_in, long_int& carry, long_int& out);
    static void long_half_multiply(long_int& in1, long_int& in2, long_int& out);
    static void long_multiply(long_int in1, long_int in2, long_int& out);

    static void long_divide(long_int in1, long_int in2, long_int& remainder, long_int& quarter);
};

class modular_arithmetic{
public:
    //calculate u/v coefficients?
    //return a bool value: 1 if numbers are coprime, 0 if not?
    static void steins_algorithm(long_int in1, long_int in2, long_int& out);
    static void lcm(long_int& in1, long_int& in2, long_int& out);
    static void mu_calc(long_int& modulo, long_int& mu);
    static void barrett_reduction(long_int in, long_int modulo, long_int& mu, long_int& rem);

    static void long_mod_add(long_int& in1, long_int& in2, long_int& modulo, long_int& mu, long_int& out, unsigned char carry_bit = 0);
    static void long_mod_sub(long_int& in1, long_int& in2, long_int& modulo, long_int& mu,long_int& out, unsigned char borrow_bit = 0);
    static void long_mod_multiply(long_int& in1, long_int& in2, long_int& modulo, long_int& mu, long_int& out);
    static void long_mod_square(long_int& in, long_int& modulo, long_int& mu, long_int& out);
    static void long_mod_power(long_int in, long_int& power, long_int& modulo, long_int& out);

    static bool miller_rabin_test(long_int& in);
};