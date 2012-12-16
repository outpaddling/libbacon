#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#if defined(__sgi__) || defined(sun)
#include <alloca.h>
#endif
#include "bacon.h"

/*
 *  Read a string from stream fp.  The end of the string is defined as
 *  EOF, whitespace, or '='.
 */
 
char    *read_string(debug_t *debug,FILE *fp,size_t max_len)

{ 
    int     ch;
    char    *param_value,
	    *p;
    
    param_value = alloca(max_len);
    while ( ((ch=getc(fp)) != EOF) && (isspace(ch) || (ch == '=')) )
	;
    
    p = param_value;
    do
    {
	*p++ = ch;
    }   while ( ((ch=getc(fp)) != EOF) && (ch != '\n') && 
		((size_t)(p-param_value) < max_len) );
    *p = '\0';
    
    fputs(param_value,debug->log_fp);
    putc('\n',debug->log_fp);
    return strdup(param_value);
}

