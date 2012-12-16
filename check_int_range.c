#include <stdio.h>
#include "bacon.h"

int     check_int_range(debug_t *debug,int val,int min,int max,char *name)

{
    if ( (val < min) || (val > max) )
    {
	fprintf(stderr,"%s: Error: Invalid %s: %d.  Must be between %d and %d.\n",
		debug->prog_name,name,val,min,max);
	return 1;
    }
    else
	return 0;
}

