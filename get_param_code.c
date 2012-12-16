#include <stdio.h>
#include <stdlib.h>
#include "bacon.h"

/*
 *  Convert a parameter string to an integer code suitable for a
 *  switch() statement.  The string list must be sorted!
 */
 
int     get_param_code(char *param_name,char *param_name_list[],size_t nelem)

{
    char    **p,
	    *skey[1];
    
    skey[0] = param_name;
    p = bsearch(skey,param_name_list,nelem,sizeof(char *),
	(strptrcmp_t)strptrcasecmp);
    if ( p != NULL )
    {
	return p - param_name_list;
    }
    else
	return -1;
}


/*
 *  Helper function for bsearch(), qsort(), etc. to compare to 
 *  elements of an array of pointers to strings.  ( Does not work on
 *  a 2D char array - only an array of (char *).
 */
 
int     strptrcasecmp(char **p1,char **p2)

{ 
    return strcasecmp(*p1,*p2);
}

