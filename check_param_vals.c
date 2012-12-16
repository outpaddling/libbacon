#include <stdio.h>
#include <limits.h>
#include <float.h>
#include "bacon.h"

int     check_double_val(debug_t *debug,double param,char *name)

{
    if ( param == DBL_MAX )\
    {
	fprintf(stderr,"%s: Error: No value set for %s.\n",
		debug->prog_name,name);
	return 1;
    }
    else
	return 0;
}


int     check_long_val(debug_t *debug,long param,char *name)

{
    if ( param == LONG_MAX )\
    {
	fprintf(stderr,"%s: Error: No value set for %s.\n",
		debug->prog_name,name);
	return 1;
    }
    else
	return 0;
}


int     check_int_val(debug_t *debug,int param,char *name)

{
    if ( param == INT_MAX )\
    {
	fprintf(stderr,"%s: Error: No value set for %s.\n",
		debug->prog_name,name);
	return 1;
    }
    else
	return 0;
}


int     check_pointer_val(debug_t *debug,void *param,char *name)

{
    if ( param == NULL )\
    {
	fprintf(stderr,"%s: Error: No value set for %s.\n",
		debug->prog_name,name);
	return 1;
    }
    else
	return 0;
}

