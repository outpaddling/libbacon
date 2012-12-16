#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sysexits.h>
#include "bacon.h"

double  read_double(debug_t *debug,FILE *fp)

{
    char    *end,
	    buff[DOUBLE_STRING_MAX+1],
	    param_str[DOUBLE_STRING_MAX+1];
    double  n;

    /* Find beginning of parameter value */
    read_param_value(fp,param_str,DOUBLE_STRING_MAX);

    /* Filter string through "bc" to evaluate expressions */
    bc_eval(debug,buff,param_str,DOUBLE_STRING_MAX);
    fprintf(debug->log_fp,"%-25s",param_str);
    
    /* Convert bc output to double if possible */
    n = strtod(buff,&end);
    if ( (end == buff) || !(isspace((int)*end) || (*end == '\0')))
    {
	fprintf(stderr,"%s: Error: Invalid real parameter: %s\n",
		debug->prog_name,param_str);
	exit(EX_DATAERR);
    }
    fprintf(debug->log_fp,"(%f)\n",n);
    return n;
}

