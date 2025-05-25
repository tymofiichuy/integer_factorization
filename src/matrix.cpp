#include "matrix.hpp"

matrix::matrix(){
    mtr = nullptr;
    size = 0;
}

matrix::~matrix(){
    if(mtr){
        for(int i = 0; i < size; i++){
            delete[] mtr[i];
        }  
        delete[] mtr;              
    }
}

matrix::matrix(int size): size(size){
    mtr = new int*[size];
    for(int i = 0; i < size; i++){
        mtr[i] = new int[size]();
    }    
}

matrix::matrix(matrix&& other): size(other.size), mtr(other.mtr){
    other.mtr = nullptr;
    other.size = 0;
}

matrix::matrix(const matrix& other): size(other.size){
    mtr = new int*[size];
    for(int i = 0; i < size; i++){
        mtr[i] = new int[size];
        memcpy(mtr[i], other.mtr[i], sizeof(int)*size);
    }  
}

matrix& matrix::operator=(matrix&& other){
    if(this != &other){
        if(mtr){
            for(int i = 0; i < size; i++){
                delete[] mtr[i];
            }    
            delete[] mtr; 
            mtr = nullptr;               
        }

        mtr = other.mtr;
        size = other.size;

        other.mtr = nullptr;
        other.size = 0;
    }

    return *this;
}

matrix& matrix::operator=(const matrix& other){
    if(this != &other){
        if(mtr){
            for(int i = 0; i < size; i++){
                delete[] mtr[i];
            }
            delete[] mtr;                              
        }


        size = other.size;
        mtr = new int*[size];
        for(int i = 0; i < size; i++){
            mtr[i] = new int[size];
            memcpy(mtr[i], other.mtr[i], sizeof(int)*size);
        } 
    }

    return *this;
}

void matrix::swap(int ind1, int ind2){
    int* temp = mtr[ind1];
    mtr[ind1] = mtr[ind2];
    mtr[ind2] = temp;
}

void matrix::inplace_row_xor(int ind1, int ind2){
    for(int i = 0; i < size; i++){
        mtr[ind2][i] += mtr[ind1][i];
        mtr[ind2][i] %= 2;
    }
}

void matrix::inplace_col_xor(int ind1, int ind2){
    for(int i = 0; i < size; i++){
        mtr[i][ind2] += mtr[i][ind1];
        mtr[i][ind2] %= 2;
    }
}

int matrix::find_pivot(int col){
    int ind = 0;
    while((ind<size)&&(mtr[ind][col]==0)){
        ind++;
    }
    return ind;
}

int matrix::find_zero_row(int from){
    int flag;
    for(int i = from; i < size; i++){
        flag = true;
        for(int j = 0; j < size; j ++){
            if(mtr[i][j] != 0){
                flag = false;
                break;
            }
        }
        if(flag){
            return i;
        }
    }
    return -1;
}

int matrix::get_size(){
    return size;
}