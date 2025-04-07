#pragma once

#include<cstring>

class matrix{
    int size;
public:
    int** mtr;
    int get_size();

    void swap(int ind1, int ind2);
    void inplace_row_xor(int ind1, int ind2);
    void inplace_col_xor(int ind1, int ind2);
    int find_pivot(int col);
    int find_zero_row(int from);

    matrix& operator=(matrix&& other);
    matrix& operator=(const matrix& other);
    matrix(int size);
    matrix(matrix&& other);
    matrix(const matrix& other);
    matrix();    
    ~matrix();
};