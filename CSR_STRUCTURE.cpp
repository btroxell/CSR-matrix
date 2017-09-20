#include "CSR_STRUCTURE.h"
#include <iostream>

CSR_STRUCTURE::CSR_STRUCTURE(void)
	: nnz_val_(new int [0]), col_ptr_(new int [0]), row_ptr_(new int [0]), rows(0), columns(0), nonzeroes(0)
{

}

//csr representation pairs nonzero values with their respective column index, which means the size of the array will be how many nonzero values are in the sparse matrix
//csr representation also iterates on how many nonzero values are in each ROW, so the size of row_ptr will be how many rows+1 (the 0th value in the row_ptr[] will be 1)  
CSR_STRUCTURE::CSR_STRUCTURE(int row_in, int col_in, int nnz_in)
	: nnz_val_(new int [nnz_in]), col_ptr_(new int [nnz_in]), row_ptr_(new int [row_in+1]), rows(row_in), columns(col_in), nonzeroes(nnz_in)
{
	row_ptr_[0] = 1;
	//std::cout << "rows: " << rows << " columns: " << columns << " nonzeros: " << nonzeroes << std::endl;
}

CSR_STRUCTURE::~CSR_STRUCTURE(void) 
{
	delete[] nnz_val_;
	delete[] col_ptr_;
	delete[] row_ptr_;
}