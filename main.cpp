#include "CSR_STRUCTURE.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>

//, std::ofstream &transpose_of

void create_transpose_matrix(CSR_STRUCTURE &csr_matrix, std::ofstream &transpose_of)
{
	
	int transpose_rows = csr_matrix.columns_;
	int transpose_cols = csr_matrix.rows_;
	int transpose_nnzs = csr_matrix.nonzeroes_;
	int *row_counts = new int[transpose_rows-1];

	CSR_STRUCTURE transpose_matrix(transpose_rows, transpose_cols, transpose_nnzs);

	for (int i = 0; i < transpose_matrix.rows_ + 1; i++) 
	{
		transpose_matrix.row_ptr_[i] = 0;
	}//end for

	std::cout << csr_matrix.row_ptr_[6] << std::endl;

	/*counts number of non zero values in a column by incrementing the value in the row_ptr everytime it sees the same column*/
	/*it also updates the number of non zeros in that column which turns into the # of nonzeros in that row of the transpose*/
	for (int i = 0; i < csr_matrix.rows_+1; i++) 
	{
		for (int j = csr_matrix.row_ptr_[i]; j < csr_matrix.row_ptr_[i + 1]; j++) 
		{
			//std::cout << "at column " << csr_matrix.col_ptr_[j] << " when j = " << j << " add one" << std::endl;
			int col_nnz = csr_matrix.col_ptr_[j];
			transpose_matrix.row_ptr_[col_nnz+1]++;
		}
		//std::cout << "values in transpose row_ptr: " << transpose_matrix.row_ptr_[i] << " " << i << std::endl;
	}
	
	std::cout << "before constructing row_ptr2" << std::endl;
	/*constructs the transpose matrix row_ptr and updates its values*/
	for (int i = 0; i < csr_matrix.rows_ + 1; i++) 
	{
		transpose_matrix.row_ptr_[i+1] += transpose_matrix.row_ptr_[i];
	}

	/*populates the new csr matrix with the transpose information*/
	for (int i = 0; i < csr_matrix.rows_; i++) 
	{
		for (int j = csr_matrix.row_ptr_[i]; j < csr_matrix.row_ptr_[i + 1]; j++) 
		{
			int i2 = csr_matrix.col_ptr_[j];
			transpose_matrix.col_ptr_[transpose_matrix.row_ptr_[i2] + row_counts[i2]] = i;
			transpose_matrix.nnz_val_[transpose_matrix.row_ptr_[i2] + row_counts[i2]] = csr_matrix.nnz_val_[j];
			row_counts[i2]++;
		}
	}

	
	transpose_of << transpose_matrix.rows_ << " " << transpose_matrix.columns_ << " " << transpose_matrix.nonzeroes_ << "\n";
	
	for (int i = 0; i < transpose_matrix.rows_; i++) {
		for (int j = transpose_matrix.row_ptr_[i]; j < transpose_matrix.row_ptr_[i + 1]; j++) {
			transpose_of << transpose_matrix.col_ptr_[j] << " " << transpose_matrix.nnz_val_[j] << " ";
		}
		transpose_of << "\n";
	}
	
	
	std::cout << "non zero values in transpose CSR matrix: ";
	for (int i = 0; i < transpose_matrix.nonzeroes_; i++) {
		std::cout << transpose_matrix.nnz_val_[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "column values in transpose CSR matrix: ";
	for (int i = 0; i < transpose_matrix.nonzeroes_; i++) {
		std::cout << transpose_matrix.col_ptr_[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "row values in transpose CSR matrix: ";
	for (int i = 0; i < transpose_matrix.rows_ + 1; i++) {
		std::cout << transpose_matrix.row_ptr_[i] << " ";
	}
	std::cout << std::endl;
	
}

/*
void output_matrix(CSR_STRUCTURE csr_matrix, std::ofstream &matrix_of) 
{
	matrix_of << csr_matrix.rows_ << " " << csr_matrix.columns_ << " " << csr_matrix.nonzeroes_ << "\n";

	for (int i = 0; i < csr_matrix.rows_; i++) {
		for (int j = csr_matrix.row_ptr_[i]; j < csr_matrix.row_ptr_[i + 1]; j++) {
			matrix_of << csr_matrix.col_ptr_[j]+1 << " " << csr_matrix.nnz_val_[j];
		}
		matrix_of << "\n";
	}
}
*/

void cosine_simularity(CSR_STRUCTURE csr_matrix, std::ofstream &sim_of, double threshold_in) 
{
	/*checks all pairs including the similarity with itself and (j,i), which sim(i,j) == sim(j,i)*/
	for (int i = 0; i < csr_matrix.rows_; i++)
	{
		for (int j = 0; j < csr_matrix.rows_; j++)
		{
			int row_i = csr_matrix.row_ptr_[i + 1] - csr_matrix.row_ptr_[i];
			int row_j = csr_matrix.row_ptr_[j + 1] - csr_matrix.row_ptr_[j];
			int ni = 0, nj = 0;
			double cosine = 0, lengthi = 0, lengthj = 0;

			//std::cout << "current ni " << ni << ", current nj " << nj << " on (" << i << "," << j << ")" << " current row_i " << row_i << ", current row_j " << row_j << std::endl;

			while(ni < row_i && nj < row_j)
			{
				int col_i = csr_matrix.row_ptr_[i] + ni;
				int col_j = csr_matrix.row_ptr_[j] + nj;

				if (csr_matrix.col_ptr_[col_i] == csr_matrix.col_ptr_[col_j]) 
				{
					cosine += csr_matrix.nnz_val_[col_i] * csr_matrix.nnz_val_[col_j];
					lengthi += csr_matrix.nnz_val_[col_i] * csr_matrix.nnz_val_[col_i];
					lengthj += csr_matrix.nnz_val_[col_j] * csr_matrix.nnz_val_[col_j];
					ni++;
					nj++;
				}//end if
				else if (csr_matrix.col_ptr_[col_i] > csr_matrix.col_ptr_[col_j])
				{
					lengthj += csr_matrix.nnz_val_[col_j] * csr_matrix.nnz_val_[col_j];
					nj++;
				}
				else
				{
					lengthi += csr_matrix.nnz_val_[col_i] * csr_matrix.nnz_val_[col_i];
					ni++;
				}

			}//end while ni && nj
			
			//std::cout << "ni: " << ni << " nj: " << nj << std::endl;
			/*check to see which row finished first because the while loop exits before calculating the last length at the last index of the nonzero value*/
			if (nj == row_j && ni < row_i) {
				lengthi += csr_matrix.nnz_val_[ni + csr_matrix.row_ptr_[i]] * csr_matrix.nnz_val_[ni + csr_matrix.row_ptr_[i]];
			}
			else if(ni == row_i && nj < row_j){
				lengthj += csr_matrix.nnz_val_[nj + csr_matrix.row_ptr_[j]] * csr_matrix.nnz_val_[nj + csr_matrix.row_ptr_[j]];
			}

			if (lengthi * lengthj) 
			{
				//std::cout << "cosine simularity of rows: " << i << " and " << j << " cosine = " << cosine << " where lengthi = " << lengthi << " and lengthj = " << lengthj << std::endl;
				cosine /= sqrt(lengthi * lengthj);
				//std::cout << "calculated cosine = " << cosine << std::endl;
			}
			else {
				cosine = 0;
			}

			if (cosine > threshold_in) {
				sim_of << i << " " << j << " " << cosine << "\n";
			}

			//std::cout << "cosine similarity between (" << i << "," << j << ")" << " is " << cosine << std::endl;

		}//end for j

	}//end for i

	sim_of.close();

}//end cosine sim



int main(int argc, char * argv[])
{


	std::string str_entire_line, str_info, str_col, str_val;

	int info_val, int_val;
	int matrix_info[3];
	int counter = 0;

	if (argc > 1)
	{
		std::ifstream input_file(argv[1]);
		getline(input_file, str_entire_line);

		std::istringstream first_line_ss(str_entire_line);

		std::ofstream transpose_outfile(argv[2], std::ofstream::out);
		//transpose_outfile << "created and opened file";

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

		int col_nnz_index_ptr = 0;
		int col_ptr_counter = 0;
		int row_ptr_counter = 0;
		int nnz_values_in_row = 0;

		while (!input_file.eof())
		{
			getline(input_file, str_entire_line);
			//std::cout << "str entire line: " << str_entire_line << std::endl;
			
			
			std::istringstream entire_line(str_entire_line);

		
			while (entire_line)
			{

				//std::cout << col_ptr_counter << " ";
				
				getline(entire_line, str_val, ' '); 
				//std::cout << "str_val: " << str_val << std::endl;
				
				
				//std::cout << "int_val: " << int_val << std::endl;

				/*description says odd numbers in each line are columns, start from 0, evens are columns odds are nnz values*/
				if (col_ptr_counter % 2 == 0) {
					int_val = atoi(str_val.c_str());
					current_matrix.col_ptr_[col_nnz_index_ptr] = int_val-1;
				}
				else {
					int_val = atof(str_val.c_str());
					current_matrix.nnz_val_[col_nnz_index_ptr] = int_val;
					col_nnz_index_ptr++;
					nnz_values_in_row++;
				}

				col_ptr_counter++;
				
			}

			current_matrix.row_ptr_[row_ptr_counter+1] = nnz_values_in_row + current_matrix.row_ptr_[row_ptr_counter];
			col_ptr_counter -= 1;
			nnz_values_in_row = 0;
			row_ptr_counter++;

		}//end while in file

		
		std::cout << "non zero values in CSR matrix: ";
		for (int i = 0; i < current_matrix.nonzeroes_; i++) {
		std::cout << current_matrix.nnz_val_[i] << " ";
		}
		std::cout << std::endl;

		std::cout << "column values in CSR matrix: ";
		for (int i = 0; i < current_matrix.nonzeroes_; i++) {
			std::cout << current_matrix.col_ptr_[i] << " ";
		}
		std::cout << std::endl;

		std::cout << "row values in CSR matrix: ";
		for (int i = 0; i < current_matrix.rows_+1; i++) {
			std::cout << current_matrix.row_ptr_[i] << " ";
		}
		std::cout << std::endl;

		/*TO DO*/
		/*get the arguments and write to an output file*/
		/*think it might have to do with args*/

		
		//std::ofstream cos_sim_outfile(argv[3]);
		//int threshold = atof(argv[4]);
		

		//transpose_outfile.open(argv[2], out);

		//CSR_STRUCTURE transpose = create_transpose_matrix(current_matrix);
		//, transpose_outfile

		//std::cout << current_matrix.row_ptr_[6] << std::endl;
		create_transpose_matrix(current_matrix, transpose_outfile);

		
		//transpose_outfile.open(argv[2]);

		
		//cosine_simularity(current_matrix, cos_sim_outfile, threshold);
		
	}//end if
	else
	{
		std::cout << "This program takes 4 arguments" << std::endl;
	}

}//end main

