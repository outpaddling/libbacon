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

#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * \addtogroup libbacon
 *  @{
 */

/**
 *  \brief  Purge unwanted input data from a file descriptor
 *
 *  fd_purge() reads and discards unwanted input data (such as leftover
 *  input from a keyboard or mouse) from the input file descriptor fd.
 ****************************************************************************/

void    fd_purge(int fd)

{
    char    buff[128];
    int     old_flags;
    
    old_flags = fcntl(fd,F_GETFL,0);
    
    /* Set fd to non-blocking */
    fcntl(fd,F_SETFL,O_NONBLOCK);
    
    /* Remove pending characters */
    while ( read(fd,buff,128) != -1 )
	;
    
    fcntl(fd,F_SETFL,old_flags);
}

/** @} */

