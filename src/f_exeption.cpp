#include "f_exeption.hpp"

factor_exception::factor_exception(int factor) : std::runtime_error(std::to_string(factor) + " is a factor of N"), factor(factor) {}