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

typedef struct s_isa
{
	std::string ins_name;
	std::string code;
} t_isa;

static std::vector<t_isa>	isa = \
{
	{"jal", ""},			{"jalr", "000"},		{"beq", "000"},
	{"bne", "001"},			{"blt", "100"},			{"bge", "101"},
	{"bltu", "110"},		{"bgeu", "111"},		{"lb", "000"},
	{"lh", "001"},			{"lw", "010"},			{"lbu", "100"},
	{"lhu", "101"},			{"sb", "000"},			{"sh", "001"},
	{"sw", "010"},			{"addi", "000"},		{"slti", "010"},
	{"sltiu", "011"},		{"xori", "100"},		{"ori", "110"},
	{"andi", "111"},		{"slli", "0000000001"},	{"srli", "0000000101"},
	{"srai", "0100000101"},	{"add", "0000000000"},	{"sub", "0100000000"},
	{"sll", "0000000001"},	{"slt", "0000000010"},	{"sltu", "0000000011"},
	{"xor", "0000000100"},	{"srl", "0000000101"},	{"sra", "0100000101"},
	{"or", "0000000110"},	{"and", "0000000111"}
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
void		generate_mc(t_instruction *ins);

#endif
