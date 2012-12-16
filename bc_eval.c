#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sysexits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "bacon.h"

/**
 *  \addtogroup libbacon
 *  @{
 */

/**
 *  \brief  Run a parameter value string through the "bc" command for
 *  evaluation.
 *
 *  \param  debug   Structure containing debug information from caller.
 *
 *  \param  dest    String to capture bc output
 *
 *  \param  src     String containing bc expression
 *
 *  \param  dest_max    Length of character-array dest
 *
 *  The bc_eval function takes a bc calculator expression in src, runs
 *  it through the bc command, and returns the bc output in dest.
 *
 *  Care should be taken to use portable bc expressions.  Verious
 *  Unix systems have different implementations of the bc command, some
 *  having many extensions.
 *
 *  \return Output from bc command
 */
 
char    *bc_eval(debug_t *debug,char *dest,char *src,size_t dest_max)

{
    pid_t   pid;
    int     status = 0;
    char    to_bc_fn[] = "FFtobc",
	    from_bc_fn[] = "FFfrombc";
    FILE    *from_bc, *to_bc;
    
    /* 
     * Filter parameter value string through bc command, to allow
     * arithmetic expressions.
     */

    /* Spare the user from the fact that bc doesn't like capital letters */
    strlower(src,src,strlen(src)+1);
    
    /* Create fifo files to communicate with bc process */
    if ( mkfifo(to_bc_fn,0644) == -1 )
    {
	fprintf(stderr,"%s: Error: Cannot create fifo %s: %s\n",
		debug->prog_name,to_bc_fn,strerror(errno));
	exit(EX_CANTCREAT);
    }
    if ( mkfifo(from_bc_fn,0644) == -1 )
    {
	fprintf(stderr,"%s: Error: Cannot create fifo %s: %s\n",
		debug->prog_name,from_bc_fn,strerror(errno));
	cleanup_exit(EX_CANTCREAT,to_bc_fn,NULL);
    }
    
    /* fork() and exec() a bc process with stdin and stdout redirected 
       to fifos for talking to parent */
    if ( (pid = fork()) == 0 )
    {
	/* bc: Redirect stdin and stdout */
	close(0);
	close(1);
	
	/* Open read file first since it will be assigned descriptor 0 */
	to_bc = fopen(to_bc_fn,"r");
	if ( to_bc == NULL )
	{
	    fprintf(stderr,"%s: Error: Cannot open %s: %s\n",
		    debug->prog_name,to_bc_fn,strerror(errno));
	    cleanup_exit(EX_UNAVAILABLE,to_bc_fn,from_bc_fn,NULL);
	}
	
	/* Open write file - will be assigned descriptor 1 */
	from_bc = fopen(from_bc_fn,"w");
	if ( from_bc == NULL )
	{
	    fprintf(stderr,"%s: Error: Cannot open %s: %s\n",\
		    debug->prog_name,from_bc_fn,strerror(errno));
	    cleanup_exit(EX_UNAVAILABLE,to_bc_fn,from_bc_fn,NULL);
	}
	
	execlp("bc","bc","-l",NULL);
	
	/* Shouldn't return from exec() - something's screwy. */
	fprintf(stderr,"%s: Error: exec() failed: %s\n",
		debug->prog_name,strerror(errno));
	exit(EX_UNAVAILABLE);
    }
    else
    {
	/* Write expression to bc stdin */
	to_bc = fopen(to_bc_fn,"w");
	if ( to_bc == NULL )
	{
	    fprintf(stderr,"%s: Error: Cannot open %s: %s\n",
		    debug->prog_name,to_bc_fn,strerror(errno));
	    cleanup_exit(EX_UNAVAILABLE,to_bc_fn,from_bc_fn);
	}
	fprintf(to_bc,"scale=20\n pi=a(1)*4\n %s\n quit\n",src);
	fclose(to_bc);
	
	/* Read output from bc stdout */
	from_bc = fopen(from_bc_fn,"r");
	if ( from_bc == NULL )
	{
	    fprintf(stderr,"%s: Error: Cannot open %s: %s\n",
		    debug->prog_name,from_bc_fn,strerror(errno));
	    cleanup_exit(EX_UNAVAILABLE,to_bc_fn,from_bc_fn);
	}

	/* Wait for bc to finish writing to FIFO */
	waitpid(pid,&status,0);
	
	fgets(dest,dest_max,from_bc);
	fclose(from_bc);
	
    }
    
    /* Clean up fifos */
    unlink(from_bc_fn);
    unlink(to_bc_fn);
    return dest;
}

/** @} */

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

