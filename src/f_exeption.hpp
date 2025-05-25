#pragma once

#include <iostream>
#include <string>

class factor_exception : public std::runtime_error {
public:    
    int factor;
    factor_exception(int factor);
};