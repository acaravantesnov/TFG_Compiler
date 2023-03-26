#include "RV32I_C.hpp"

s_instruction::s_instruction(const std::string &name, const std::string &args) : \
name(name), args(args)
{
	size_t	i;

	for (i = 0; i < isa.size(); i++)
		if (this->name == isa[i])
			break;

	if (i == 0)
		this->type = J;
	else if (i == 1)
		this->type = I_1;
	else if ((i >= 2) && (i <= 7))
		this->type = B;
	else if ((i >= 8) && (i <= 12))
		this->type = I_2;
	else if ((i >= 13) && (i <= 15))
		this->type = S;
	else if ((i >= 16) && (i <= 21))
		this->type = I_3;
	else if ((i >= 22) && (i <= 24))
		this->type = I_4;
	else if ((i >= 25) && (i <= 34))
		this->type = R;

	machine_code = "00000000000000000000000000000000";
}

std::string toUnsignedBinaryString(const std::string& numberString, size_t size)
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

void	generate_mc(t_instruction *ins)
{
	short						index_1, index_2;
	std::array<std::string, 3>	args;

	switch (ins->type)
	{
		case R:
			index_1 = ins->args.find(',');
			args[0] = ins->args.substr(0, index_1);
			if (args[0][0] == 'x')
				args[0] = args[0].substr(1);
			index_2 = ins->args.substr(index_1).find(',');
			args[1] = ins->args.substr(index_1, index_2);
			if (args[1][0] == 'x')
				args[1] = args[1].substr(1);
			args[2] = ins->args.substr(index_2);
			if (args[2][0] == 'x')
				args[2] = args[2].substr(1);

			ins->machine_code = XXX + toUnsignedBinaryString(args[2], 5) + \
			toUnsignedBinaryString(args[1], 5) + XXX + \
			toUnsignedBinaryString(args[0], 5) + "0110011";
			break;
		case I_1:
			break;
		case I_2:
			break;
		case I_3:
			break;
		case I_4:
			break;
		case S:
			break;
		case B:
			break;
		case J:
			break;
		default:
			break;
	}
}
