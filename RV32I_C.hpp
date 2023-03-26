#ifndef RV32I_C_HPP
# define RV32I_C_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <array>
# include <algorithm>
# include <stdbool.h>
# include <bitset>

enum instruction_type
{
	R,
	I_1,
	I_2,
	I_3,
	I_4,
	S,
	B,
	J
};

std::array<std::string, 35> isa = \
{
	"jal", "jalr", "beq", "bne", "blt",		// 0 - 4
	"bge", "bltu", "bgeu", "lb", "lh",		// 5 - 9
	"lw", "lbu", "lhu", "sb", "sh",			// 10 - 14
	"sw", "addi", "slti", "sltiu", "xori",	// 15 - 19
	"ori", "andi", "slli", "srli", "srai",	// 20 - 24
	"add", "sub", "sll", "slt", "sltu",		// 25 - 29
	"xor", "srl", "sra", "or", "and"		// 30 - 34
};

typedef struct s_instruction
{
	instruction_type		type;
	std::string				name;
	std::string				args;
	std::string				machine_code;
	s_instruction(const std::string &, const std::string &);
} t_instruction;

std::string toUnsignedBinaryString(const std::string& numberString, size_t size);
void	generate_mc(t_instruction *ins);

#endif
