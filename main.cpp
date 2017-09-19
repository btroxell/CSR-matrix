#include "CSR_STRUCTURE.h"
#include <fstream>
#include <iostream>
#include <sstream>

void transpose_matrix(CSR_STRUCTURE &csr, std::string op_file)
{

}

void cos_similarity_calculation(CSR_STRUCTURE &csr, std::string op_file)
{

}

int main(int argc, char * argv[])
{
	CSR_STRUCTURE current_matrix;

	std::string str_row, str_col, str_nnz;
	std::stringstream convert;

	if (argc == 1) 
	{
		std::ifstream input_file(argv[1]);
		input_file.open;
		input_file >> str_row >> str_col >> str_nnz;

		std::cout << str_row << " " << str_col << " " << str_nnz;
		//std::string trans_output;
		//std::string sim_output;
		/*
		while (input_file.is_open())
		{

		}
		*/
	}

}//end main

