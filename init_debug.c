#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sysexits.h>
#include "bacon.h"

void    init_debug(debug_t *debug,char *prog_name)

{
    char    *p,
	    temp[FILENAME_MAX+1];
    
    debug->prog_name = prog_name;
    
    /* Create log file, using only base name */
    if ( (p = strrchr(prog_name,'/')) != NULL )
	prog_name = p+1;
    snprintf(temp,FILENAME_MAX,"%s.log",prog_name);
    debug->log_file = strdup(temp);
    debug->log_fp = fopen(debug->log_file,"w");
    if ( debug->log_fp == NULL )
    {
	fprintf(stderr,"Cannot open log file %s: %s\n",
		debug->log_file,strerror(errno));
	exit(EX_CANTCREAT);
    }
    else
	fprintf(stderr,"Log file is %s\n",debug->log_file);
}

