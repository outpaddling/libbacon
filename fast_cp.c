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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "bacon.h"

/**
 * \addtogroup libbacon description
 *  @{
 */

/**
 *  \brief  Optimized file copy
 *
 *  fast_cp() copies a file using optimal buffering for both source and
 *  destination filesystems.
 *
 *  \return The return value of the last read(3) call.
 */

int     fast_cp(src,dest)
char    *dest,*src;

{
    int         infile,outfile;
    struct stat infile_stats,outfile_stats;
    long        x;
    long        buff_size, nbytes;
    char        *buff;
    
    /* Open source and destination files for low level transfer */
    if ( (infile = open(src,O_RDONLY)) == -1 )
	return -1;
    
    if ( (outfile = open(dest,O_WRONLY|O_CREAT|O_TRUNC,0700)) == -1 )
	return -1;

    /* Create buffer of optimum size for both files, 64k max
       Optimum buffer size is any multiple of the both sector sizes
       given by struct stat member st_blksize.  COHERENT cc lacks
       st_blksize */
    fstat(infile,&infile_stats);
    fstat(outfile,&outfile_stats);
    x = LCM(infile_stats.st_blksize,outfile_stats.st_blksize);
    buff_size = MIN(x,64*1024);

    buff = (char *)malloc(buff_size);
    
    /* Copy file */
    while ( (nbytes = read(infile,buff,buff_size)) > 0 )
	write(outfile,buff,nbytes);
    close(infile);
    close(outfile);
    free(buff);
    return nbytes;  /* Return 0 for success, or error code from read() */
}
/** @} */

