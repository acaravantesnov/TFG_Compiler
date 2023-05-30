#include "../inc/ASM_to_MC.hpp"

std::string signed_to_binary(const std::string &numberString, int size)
{
    int number = std::stoi(numberString);
    std::string binary;
    bool isNegative = (number < 0);
    if (isNegative)
        number = -number;
    
    while (number > 0) {
        binary = std::to_string(number % 2) + binary;
        number /= 2;
    }
    
    // Add leading zeros if necessary
    while (binary.size() < (size_t)size)
        binary = '0' + binary;
    
    if (isNegative) {
        // Take two's complement
        for (char& bit : binary)
            bit = (bit == '0') ? '1' : '0';
        
        // Add one
        for (int i = binary.size() - 1; i >= 0; --i) {
            if (binary[i] == '0') {
                binary[i] = '1';
                break;
            }
            binary[i] = '0';
        }
    }
    
    return binary;
}