#include <stdio.h>

/*
 *  Read a parameter expression from an input stream into a string
 *  variable.  The input stream has the form:
 *
 *  parameter-name = expression
 */
 
char    *read_param_value(FILE *fp,char *param_value,size_t maxlen)

{
    char    *p;
    int     ch;
    
    for (p=param_value; ( ((ch = getc(fp)) != EOF) && (ch != '\n') && 
	    (ch != '#') && ((size_t)(p-param_value) < maxlen) ); ++p)
    {
	*p = ch;
    }
    *p = '\0';
    
    return param_value;
}

