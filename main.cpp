#include "RV32I_C.hpp"

int main(int argc, char **argv)
{
	std::vector<t_instruction>				instructions;
	std::vector<t_instruction>::iterator	it;
	std::ifstream							asm_file;
	std::ofstream							mc_file;
	std::string								line, args;

	if (argc != 2)
		return (1);
	asm_file.open(std::string(argv[1]), std::ios::in);
	if (asm_file.fail())
		return (1);
	mc_file.open("tests/machine_code_tests/" + \
	std::string(argv[1]).substr(6, std::string(argv[1]).length() - 8) + "_bin",\
	std::ios::out | std::ios::trunc);

	// Save t_instruction vector elements
	while (getline(asm_file, line))
		instructions.push_back(t_instruction(line.substr(0, line.find(" ")), \
		line.substr(line.find(" ") + 1)));

	// Assign machine codes to each element in the t_instruction vector
	for (it = instructions.begin(); it != instructions.end(); it++)
		generate_mc(&(*it));

	// Write to outfile machine codes
	for (it = instructions.begin(); it != instructions.end(); it++)
		mc_file << it->machine_code << std::endl;

	// Test purposes
	for (it = instructions.begin(); it != instructions.end(); it++)
		std::cout << it->type << " " << it->name << " " << it->args << std::endl;

	asm_file.close();
	mc_file.close();
	return (0);
}
