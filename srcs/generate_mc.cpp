#include "../inc/asm_to_mc.hpp"

void	generate_mc(t_instruction *ins)
{
	short							index_1, index_2;
	std::array<std::string, 3>		args;
	std::vector<t_isa>::iterator	it;

	for (it = isa.begin(); it != isa.end(); it++)
		if (it->ins_name == ins->name)
			break;

	switch (ins->type)
	{
		case U:
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
		case I_Jalr:
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
		case I_Loads:
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
		case I:
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
		case I_Shifts:
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
		case I_Atomic:
			break;
		default:
			break;
	}
}
