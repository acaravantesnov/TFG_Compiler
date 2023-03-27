#include "RV32I_C.hpp"

s_instruction::s_instruction(const std::string &name, const std::string &args) \
: name(name), args(args)
{
	size_t	i;

	for (i = 0; i < isa.size(); i++)
		if (this->name == isa[i].ins_name)
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
	short							index_1, index_2;
	std::array<std::string, 3>		args;
	std::vector<t_isa>::iterator	it;

	for(it = isa.begin(); it != isa.end(); it++)
		if (it->ins_name == ins->name)
			break;

	switch (ins->type)
	{
		case R:
			index_1 = ins->args.find(',');
			args[0] = ins->args.substr(0, index_1);
			if (args[0][0] == 'x')
				args[0] = args[0].substr(1);
			index_2 = (ins->args.substr(index_1 + 1)).find(',');
			args[1] = ins->args.substr(index_1 + 2, index_2 - index_1 + 2);
			if (args[1][0] == 'x')
				args[1] = args[1].substr(1);
			args[2] = ins->args.substr(index_1 + index_2 + 3);
			if (args[2][0] == 'x')
				args[2] = args[2].substr(1);

			ins->machine_code = \
			(it->code).substr(0, 7) + \
			toUnsignedBinaryString(args[2], 5) + \
			toUnsignedBinaryString(args[1], 5) + (it->code).substr(7) + \
			toUnsignedBinaryString(args[0], 5) + "0110011";
			break;
		case I_1:
			index_1 = ins->args.find(',');
			args[0] = ins->args.substr(0, index_1);
			if (args[0][0] == 'x')
				args[0] = args[0].substr(1);
			index_2 = (ins->args.substr(index_1 + 1)).find('(');
			args[1] = ins->args.substr(index_1 + 2, index_2 - index_1 + 2);
			if (args[1][0] == 'x')
				args[1] = args[1].substr(1);
			args[2] = ins->args.substr(index_1 + index_2 + 3, \
			ins->args.length() - (index_1 + index_2) - 4);
			if (args[2][0] == 'x')
				args[2] = args[2].substr(1);

			ins->machine_code = toUnsignedBinaryString(args[1], 12) + \
			toUnsignedBinaryString(args[2], 5) + it->code + \
			toUnsignedBinaryString(args[0], 5) + "1100111";
			break;
		case I_2:
			index_1 = ins->args.find(',');
			args[0] = ins->args.substr(0, index_1);
			if (args[0][0] == 'x')
				args[0] = args[0].substr(1);
			index_2 = (ins->args.substr(index_1 + 1)).find('(');
			args[1] = ins->args.substr(index_1 + 2, index_2 - index_1 + 2);
			if (args[1][0] == 'x')
				args[1] = args[1].substr(1);
			args[2] = ins->args.substr(index_1 + index_2 + 3, \
			ins->args.length() - (index_1 + index_2) - 4);
			if (args[2][0] == 'x')
				args[2] = args[2].substr(1);

			ins->machine_code = toUnsignedBinaryString(args[1], 12) + \
			toUnsignedBinaryString(args[2], 5) + it->code + \
			toUnsignedBinaryString(args[0], 5) + "0000011";
			break;
		case I_3:
			index_1 = ins->args.find(',');
			args[0] = ins->args.substr(0, index_1);
			if (args[0][0] == 'x')
				args[0] = args[0].substr(1);
			index_2 = (ins->args.substr(index_1 + 1)).find(',');
			args[1] = ins->args.substr(index_1 + 2, index_2 - index_1 + 2);
			if (args[1][0] == 'x')
				args[1] = args[1].substr(1);
			args[2] = ins->args.substr(index_1 + index_2 + 3);
			if (args[2][0] == 'x')
				args[2] = args[2].substr(1);

			ins->machine_code = toUnsignedBinaryString(args[2], 12) + \
			toUnsignedBinaryString(args[1], 5) + it->code + \
			toUnsignedBinaryString(args[0], 5) + "0010011";
			break;
		case I_4:
			index_1 = ins->args.find(',');
			args[0] = ins->args.substr(0, index_1);
			if (args[0][0] == 'x')
				args[0] = args[0].substr(1);
			index_2 = (ins->args.substr(index_1 + 1)).find(',');
			args[1] = ins->args.substr(index_1 + 2, index_2 - index_1 + 2);
			if (args[1][0] == 'x')
				args[1] = args[1].substr(1);
			args[2] = ins->args.substr(index_1 + index_2 + 3);
			if (args[2][0] == 'x')
				args[2] = args[2].substr(1);

			ins->machine_code = (it->code).substr(0, 7) + \
			toUnsignedBinaryString(args[2], 5) + \
			toUnsignedBinaryString(args[1], 5) + \
			(it->code).substr(7) + toUnsignedBinaryString(args[0], 5) + \
			"0010011";
			break;
		case S:
			index_1 = ins->args.find(',');
			args[0] = ins->args.substr(0, index_1);
			if (args[0][0] == 'x')
				args[0] = args[0].substr(1);
			index_2 = (ins->args.substr(index_1 + 1)).find('(');
			args[1] = ins->args.substr(index_1 + 2, index_2 - index_1 + 2);
			if (args[1][0] == 'x')
				args[1] = args[1].substr(1);
			args[2] = ins->args.substr(index_1 + index_2 + 3, \
			ins->args.length() - (index_1 + index_2) - 4);
			if (args[2][0] == 'x')
				args[2] = args[2].substr(1);

			ins->machine_code = \
			toUnsignedBinaryString(args[1], 12).substr(0, 7) + \
			toUnsignedBinaryString(args[0], 5) + \
			toUnsignedBinaryString(args[2], 5) + \
			it->code + \
			toUnsignedBinaryString(args[1], 12).substr(7) + "0100011";
			break;
		case B:
			index_1 = ins->args.find(',');
			args[0] = ins->args.substr(0, index_1);
			if (args[0][0] == 'x')
				args[0] = args[0].substr(1);
			index_2 = (ins->args.substr(index_1 + 1)).find(',');
			args[1] = ins->args.substr(index_1 + 2, index_2 - index_1 + 2);
			if (args[1][0] == 'x')
				args[1] = args[1].substr(1);
			args[2] = ins->args.substr(index_1 + index_2 + 3);
			if (args[2][0] == 'x')
				args[2] = args[2].substr(1);

			ins->machine_code = (toUnsignedBinaryString(args[2], 13))[0] + \
			(toUnsignedBinaryString(args[2], 13)).substr(2, 6) + \
			toUnsignedBinaryString(args[1], 5) + \
			toUnsignedBinaryString(args[0], 5) + \
			it->code + \
			(toUnsignedBinaryString(args[2], 13)).substr(8, 4) + \
			(toUnsignedBinaryString(args[2], 13))[1];
			break;
		case J:
			index_1 = ins->args.find(',');
			args[0] = ins->args.substr(0, index_1);
			if (args[0][0] == 'x')
				args[0] = args[0].substr(1);
			args[1] = ins->args.substr(index_1 + 2);
			if (args[1][0] == 'x')
				args[1] = args[1].substr(1);

			ins->machine_code = (toUnsignedBinaryString(args[1], 21))[0] + \
			toUnsignedBinaryString(args[1], 21).substr(10, 10) + \
			(toUnsignedBinaryString(args[1], 21))[9] + \
			toUnsignedBinaryString(args[1], 21).substr(1, 8) + \
			toUnsignedBinaryString(args[0], 5) + "1101111";
			break;
		default:
			break;
	}
}
