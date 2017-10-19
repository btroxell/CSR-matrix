Compile and run commands(assumes everything is in the same directory):

make -f makefile.mak
./pa1 "sparse matrix input file" "transpose output file" "similarity output file" "threshold"

*anything between two quotations ("") is a file name you type or:

make -f makefile.mak
./pa1 data.txt transpose.out similarity.out .5


**AS SAID IN CLASS FOR FORMAT OF THE INPUT FILE:**
-first line must be row, column, nonzero values
-REMOVE SPACES THAT OCCUR AFTER EVERY ROW... format when data.txt had spaces at the beginning of every line after the first line

If the lines that start with a space are not removed, the parser will not correctly store the matrix in the csr representation
and only the first line will be correctly represented in the csr representation

I have included my data.txt file that is formatted correctly (reverse tabbed everything to get rid of lines that begin with a space and the first line has matrix size and # nonzeros)

b) functions that perform IO: void output_matrix, void cosine_similarity, and in int main
function that performs transpose: void create_transpose_matrix
function that performs cosine similarity: void cosine_similarity
