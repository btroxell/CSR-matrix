#ifndef _CSR_STRUCTURE_H_
#define _CSR_STRUCTURE_H_
#include <fstream>
#include <ios>

class CSR_STRUCTURE
{
public:
	CSR_STRUCTURE();
	CSR_STRUCTURE(int row_in, int col_in, int nnz_in);
	CSR_STRUCTURE(const CSR_STRUCTURE &csr);
	~CSR_STRUCTURE();

	double * nnz_val_;
	int * col_ptr_;
	int * row_ptr_;
	
	int rows_;
	int columns_;
	int nonzeroes_;
};

#endif // !HEADER_H_

