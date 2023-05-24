#include "../inc/asm_to_mc.hpp"

std::string toUnsignedBinaryString(const std::string &numberString, size_t size)
{
    // Convert the string to an unsigned integer
    unsigned int number = strtoul(numberString.c_str(), NULL, 10);

    // Convert the integer to a binary string
    std::bitset<sizeof(unsigned int)*8> binary(number);
    std::string binaryString = \
	binary.to_string<char, std::string::traits_type,std::string::allocator_type>();

    // Remove leading zeros
    size_t pos = binaryString.find_first_not_of('0');
    if (pos != std::string::npos)
        binaryString = binaryString.substr(pos);
	else
        binaryString = "0";

	if (binaryString.length() < size)
	{
		std::string aux_str = "";
		int 		dif = size - binaryString.length();
		for (int i = 0; i < dif; i++)
			aux_str += '0';
		binaryString = aux_str + binaryString;
	}

    return binaryString;
}
