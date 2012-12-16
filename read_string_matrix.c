#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sysexits.h>
#include "bacon.h"

char    ***read_string_matrix(debug_t *debug,FILE *fp,size_t rows,size_t cols)

{
    char    ***matrix,
	    temp[MATRIX_STRING_MAX+1];
    size_t  r,c;
    
    matrix = MALLOC(rows,char **);
    for (r=0; r<rows; ++r)
    {
	matrix[r] = MALLOC(cols,char *);
	for (c=0; c<cols; ++c)
	{
	    if ( fscanf(fp,"%s",temp) != 1 )
	    {
		fprintf(stderr,"%s: Error: read_real_matrix(): Ran out of data reading %lu x %lu matrix.",
			debug->prog_name,(unsigned long)rows,(unsigned long)cols);
		exit(EX_DATAERR);
	    }
	    matrix[r][c] = strdup(temp);
	}
    }
    return matrix;
}


void    print_string_matrix(debug_t *debug,char ***matrix,size_t rows,size_t cols)

{
    size_t  r,c;
    
    for (r=0; r<rows; ++r)
    {
	for (c=0; c<cols; ++c)
	    fprintf(debug->log_fp,"%10s",matrix[r][c]);
	putc('\n',debug->log_fp);
    }
}

