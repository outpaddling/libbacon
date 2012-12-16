/*
    Copyright (c) 1994-2003, Jason W. Bacon, Acadix Software Systems
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are
    met:

    Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer. Redistributions
    in binary form must reproduce the above copyright notice, this list of
    conditions and the following disclaimer in the documentation and/or
    other materials provided with the distribution. 

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
    IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
    TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
    OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
*/

#include <errno.h>
#include "bacon.h"

/****************************************************************************
 * Name:
 *  Quick check the return status from spawnlp() or spawnvp().
 *
 * Description: 
 *  This function performs a quick check on the return value from
 *  spawnlp(3) or spawnvp(3), printing error messages to stderr
 *  for common failures, and the raw exit status for others.
 * 
 * Author: 
 *  Jason W. Bacon
 *
 * Returns: 
 *  The value of stat, unaltered.  This allows compact usage such as
 *  if ( check_stat(spawnvp(...),cmd) )
 ****************************************************************************/


int     check_stat(
	    int     stat,   /* Return value from spawn*p() */
	    char    *cmd    /* Used in error message if stat shows failure */
	)

{
    if ( P_EXEC_FAILED(stat) )
    {
	switch( (stat>>8) & 0x7f )  /* Extract errno returned by spawnvp */
	{
	    case    EPERM:
	    case    EACCES:
		fprintf(stderr,"%s: Permission denied.\n",cmd);
		break;
	    case    ENOENT:
		fprintf(stderr,"%s: Command not found.\n",cmd);
		break;
	    default:
		fprintf(stderr,"Command failed with status %d.\n",stat);
	}
    }
    return stat;
}

