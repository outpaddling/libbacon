#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include "bacon.h"

long    **read_long_matrix(debug_t *debug,FILE *fp,size_t rows,size_t cols)

{
    long    **matrix;
    size_t  r,c;
    
    matrix = MALLOC(rows,long *);
    for (r=0; r<rows; ++r)
    {
	matrix[r] = MALLOC(cols,long );
	for (c=0; c<cols; ++c)
	{
	    if ( fscanf(fp,"%ld",&matrix[r][c]) != 1 )
	    {
		fprintf(stderr,"%s: Error: read_integer_matrix(): Ran out of data reading %lu x %lu matrix.",
			debug->prog_name,(unsigned long)rows,(unsigned long)cols);
		exit(EX_DATAERR);
	    }
	}
    }
    return matrix;
}


void    print_long_matrix(debug_t *debug,long **matrix,size_t rows,size_t cols)

{
    size_t  r,c;
    
    for (r=0; r<rows; ++r)
    {
	for (c=0; c<cols; ++c)
	    fprintf(debug->log_fp,"%10ld",matrix[r][c]);
	putc('\n',debug->log_fp);
    }
}

