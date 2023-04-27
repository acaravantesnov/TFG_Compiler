#include "ASM_to_MC.hpp"

void open_file(char **argv, std::ofstream &mc_file)
{
	std::string argv1_str = std::string(argv[1]);
	std::string asm_file_name;

	if (argv1_str.find("/") != std::string::npos)
		asm_file_name = argv1_str.substr(argv1_str.find_last_of("/"), argv1_str.find(".s") - argv1_str.find_last_of("/"));
	else
		asm_file_name = argv1_str.substr(0, argv1_str.find(".s"));
	mc_file.open("tests/mc_files/" + \
	asm_file_name + ".mem",\
	std::ios::out | std::ios::trunc);
}

int main(int argc, char **argv)
{
	std::vector<t_instruction>				instructions;
	std::vector<t_instruction>::iterator	ins_it;
	std::ifstream							asm_file;
	std::ofstream							mc_file;
	std::string								line, args;

	if (argc != 2)
		return (1);
	asm_file.open(std::string(argv[1]), std::ios::in);
	if (asm_file.fail() || (std::string(argv[1]).find(".s") == std::string::npos))
		return (1);
	open_file(argv, mc_file);

	// Save t_instruction vector elements
	while (getline(asm_file, line))
		instructions.push_back(t_instruction(line.substr(0, line.find(" ")), \
		line.substr(line.find(" ") + 1)));

	// Assign machine codes to each element in the t_instruction vector
	for (ins_it = instructions.begin(); ins_it != instructions.end(); ins_it++)
		generate_mc(&(*ins_it));

	// Write to outfile machine codes
	for (ins_it = instructions.begin(); ins_it != instructions.end(); ins_it++)
		mc_file << ins_it->machine_code << std::endl;

	/*
	// Test purposes
	for (it = instructions.begin(); it != instructions.end(); it++)
		std::cout << it->type << " " << it->name << " " << it->args << std::endl;
	*/

	asm_file.close();
	mc_file.close();
	return (0);
}
