#include "CSR_STRUCTURE.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

void transpose_matrix(CSR_STRUCTURE &csr, std::string op_file)
{

}

void cos_similarity_calculation(CSR_STRUCTURE &csr, std::string op_file)
{

}

void parse_string_to_int(CSR_STRUCTURE &csr, std::string str_to_int)
{
	std::stringstream in_ss(str_to_int);
	do
	{
		std::string sub_str;
		in_ss >> sub_str;


	} while (in_ss);
}

int main(int argc, char * argv[])
{


	std::string str_entire_line, str_info, str_col, str_val;
	std::string delimiter = " ";

	int info_val, int_col_val, int_nnz_val;
	int matrix_info[3];
	int counter = 0;
	int pos = 0;

	if (argc > 0)
	{
		std::ifstream input_file(argv[1]);
		getline(input_file, str_entire_line);

		std::istringstream first_line_ss(str_entire_line);

		//std::cout << str_entire_line << std::endl;
		do {
			first_line_ss >> str_info;
			info_val = atoi(str_info.c_str());
			matrix_info[counter] = info_val;
			counter++;
		} while (first_line_ss);

		CSR_STRUCTURE current_matrix(matrix_info[0], matrix_info[1], matrix_info[2]);

		//current_matrix = CSR_STRUCTURE(int_row, int_col, int_nnz);
		//std::string trans_output;
		//std::string sim_output;

		int col_ptr_counter = 0;
		int row_ptr_counter = 1;
		int nnz_values_in_row = 0;
		int eo_counter = 1;

		while (!input_file.eof())
		{
			getline(input_file, str_entire_line);
			std::istringstream entire_line(str_entire_line);
			while (entire_line)
			{
				entire_line >> str_col >> str_val;
				int_col_val = atoi(str_col.c_str());
				int_nnz_val = atoi(str_val.c_str());
				current_matrix.col_ptr_[col_ptr_counter] = int_col_val;
				current_matrix.nnz_val_[col_ptr_counter] = int_nnz_val;
				col_ptr_counter++;
			}
			col_ptr_counter -= 1;
			current_matrix.row_ptr_[row_ptr_counter] += col_ptr_counter;
			row_ptr_counter++;
		}//end while in file
		std::cout << "values in col_ptr: ";
		for (int i = 0; i < current_matrix.nonzeroes; i++) {
			std::cout << current_matrix.col_ptr_[i] << " ";
		}
	}//end if

	else
	{
		std::cout << "You did not type a valid file name" << std::endl;
	}

}//end main

