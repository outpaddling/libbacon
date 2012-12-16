#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <ctype.h>
#include "bacon.h"

long    read_long(debug_t *debug,FILE *fp)

{
    char    *end,
	    buff[LONG_STRING_MAX+1],
	    param_str[LONG_STRING_MAX+1];
    long    n;
    
    /* Find beginning of parameter value */
    read_param_value(fp,param_str,LONG_STRING_MAX);
    
    /* Filter string through "bc" to evaluate expressions */
    bc_eval(debug,buff,param_str,LONG_STRING_MAX);
    fprintf(debug->log_fp,"%-25s",param_str);
    
    /* Convert bc output to double if possible */
    n = strtol(buff,&end,0);
    if ( (end == buff) || !(isspace((int)*end) || (*end == '\0')) )
    {
	fprintf(stderr,"%s: Error: Invalid integer parameter: %s\n",
		debug->prog_name,param_str);
	exit(EX_DATAERR);
    }
    fprintf(debug->log_fp,"(%ld)\n",n);
    return n;
}

