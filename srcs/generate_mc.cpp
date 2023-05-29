#include "../inc/asm_to_mc.hpp"

void	generate_mc(t_instruction *ins)
{
	short							index_1, index_2;
	std::string						rd, imm, pcrel_21, rs1, rs2, pcrel_13, shamt, csr, zimm;
	std::vector<t_isa>::iterator	it;

	for (it = isa.begin(); it != isa.end(); it++)
		if (it->ins_name == ins->name)
			break;

	switch (ins->type)
	{
		case U:
			index_1 = ins->args.find(',');
			rd = ins->args.substr(0, index_1);
			if (rd[0] == 'x')
				rd = rd.substr(1);
			imm = ins->args.substr(index_1 + 2);
			ins->machine_code = toUnsignedBinaryString(imm, 20) + \
			toUnsignedBinaryString(rd, 5);
			if (ins->name == "lui")
				ins->machine_code += isa[0].code.substr(10);
			else if (ins->name == "auipc")
				ins->machine_code += isa[1].code.substr(10);
			break;
		case J:
			index_1 = ins->args.find(',');
			rd = ins->args.substr(0, index_1);
			if (rd[0] == 'x')
				rd = rd.substr(1);
			pcrel_21 = ins->args.substr(index_1 + 2);
			if (pcrel_21[0] == 'x')
				pcrel_21 = pcrel_21.substr(1);

			ins->machine_code = (toUnsignedBinaryString(pcrel_21, 21))[0] + \
			toUnsignedBinaryString(pcrel_21, 21).substr(10, 10) + \
			(toUnsignedBinaryString(pcrel_21, 21))[9] + \
			toUnsignedBinaryString(pcrel_21, 21).substr(1, 8) + \
			toUnsignedBinaryString(rd, 5) + isa[2].code.substr(10);
			break;
		case I_Jalr:
			index_1 = ins->args.find(',');
			rd = ins->args.substr(0, index_1);
			if (rd[0] == 'x')
				rd = rd.substr(1);
			index_2 = (ins->args.substr(index_1 + 1)).find('(');
			imm = ins->args.substr(index_1 + 2, index_2 - index_1 + 2);
			if (imm[0] == 'x')
				imm = imm.substr(1);
			rs1 = ins->args.substr(index_1 + index_2 + 3, \
			ins->args.length() - (index_1 + index_2) - 4);
			if (rs1[0] == 'x')
				rs1 = rs1.substr(1);

			ins->machine_code = toUnsignedBinaryString(imm, 12) + \
			toUnsignedBinaryString(rs1, 5) + isa[3].code.substr(7, 3) + \
			toUnsignedBinaryString(rd, 5) + isa[3].code.substr(10);
			break;
		case B:
			index_1 = ins->args.find(',');
			rs1 = ins->args.substr(0, index_1);
			if (rs1[0] == 'x')
				rs1 = rs1.substr(1);
			index_2 = (ins->args.substr(index_1 + 1)).find(',');
			rs2 = ins->args.substr(index_1 + 2, index_2 - index_1 + 2);
			if (rs2[0] == 'x')
				rs2 = rs2.substr(1);
			pcrel_13 = ins->args.substr(index_1 + index_2 + 3);
			if (pcrel_13[0] == 'x')
				pcrel_13 = pcrel_13.substr(1);

			ins->machine_code = (toUnsignedBinaryString(pcrel_13, 13))[0] + \
			(toUnsignedBinaryString(pcrel_13, 13)).substr(2, 6) + \
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
