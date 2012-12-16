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

#if ! (defined(__FreeBSD__) || defined(__APPLE__))

#include "bacon.h"

/*
 * Author: Jason W. Bacon
 * Acadix Software Systems
 *
 * Limited string concatenation function.
 * Unlike strncat(), which allows maxlen characters to be added
 * to the string "dest", strlcat() assumes "maxlen" is the size of the
 * "dest" array, and prevents overfilling.  strlcat() also guarantees
 * the string is null-terminated, and than the null byte is within
 * the bounds of the array.
 */
 
size_t  strlcat(char *dest,const char *src,size_t maxlen)

{
    char    *dp,*sp;
    
    /* Find end of first string */
    for (dp=dest; (*dp != '\0') && --maxlen; ++dp)
	;
    
    /* Concetanate second string */
    for (sp=(char *)src; (*sp != '\0') && --maxlen; )
	*dp++ = *sp++;
    
    /* Null terminate */
    *dp = '\0';
    return dp-dest;
}

#endif

