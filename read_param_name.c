#include <stdio.h>
#include <ctype.h>

/*
 *  Read a parameter name from an input line of the form
 *  
 *  parameter-name = expression
 */
 
char    *read_param_name(FILE *fp,char *param_name,size_t maxlen)

{
    char    *p;
    int     ch; 

    /* Find beginning of next token */
    do
    {
	/* Pass over leading whitespace */
	while ( ((ch = getc(fp)) != EOF) && isspace(ch) )
	    ;
	
	/* If next token is a comment, discard the rest of the line */
	if ( ch == '#' )
	{
	    while ( ((ch = getc(fp)) != EOF) && (ch != '\n') )
		;
	}
    }   while ( ch == '\n' );   /* Repeat if end of a comment */
    
    if ( ch == EOF )
	return NULL;
    
    /* Read parameter name */
    p = param_name;
    do
    {
	*p++ = ch;
    }   while ( ((ch =getc(fp)) != EOF) && !isspace(ch) 
		&& ((size_t)(p-param_name) < maxlen) );
    *p = '\0';
    
    /* Skip past '=' separator */
    while ( ((ch = getc(fp)) != EOF) && (isspace(ch) || (ch == '=')) )
	;
    ungetc(ch,fp);
    
    return param_name;
}

