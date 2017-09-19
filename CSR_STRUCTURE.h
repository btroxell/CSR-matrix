#ifndef _CSR_STRUCTURE_H_
#define _CSR_STRUCTURE_H_

class CSR_STRUCTURE
{
public:
	CSR_STRUCTURE();
	CSR_STRUCTURE(int row_in, int col_in, int nnz_in);
	~CSR_STRUCTURE();

	int * nnz_val_;
	int * col_ptr_;
	int * row_ptr_;
	
	int rows;
	int columns;
	int nonzeroes;
};

#endif // !HEADER_H_

