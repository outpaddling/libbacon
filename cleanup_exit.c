#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

/*
 *  Remove temporary files and terminate the program.
 */
 
void    cleanup_exit(int status,...)

{
    va_list ap;
    char    *filename;
    
    va_start(ap,status);
    while ( (filename = va_arg(ap,char *)) != NULL )
	unlink(filename);
    
    exit(status);
}

