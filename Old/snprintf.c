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
#include <stdarg.h>
#include "bacon.h"

/**********************************************************************
 * Author: Jason W. Bacon
 * Acadix Software Systems
 * http://www.execpc.com/~acadix
 * acadix@execpc.com
 *
 **********************************************************************/

#if !(defined(FreeBSD) || defined(IRIX64) ||defined(IRIX) || defined(Darwin))
#define BIG_BUFF_SIZE   2048

#ifdef __STDC__
int         vsnprintf(char *string,size_t maxlen,const char *format,va_list args)
#else
int         vsnprintf(string,maxlen,format,args)
char        *string;
const char  *format;
size_t      maxlen;
va_list     args;
#endif

{
    return vsprintf(string,format,args);
}

#ifdef __STDC__
int         snprintf(char *string,size_t maxlen,const char *format,...)
#else
int         snprintf(string,maxlen,format)
char        *string;
const char  *format;
size_t      maxlen;
#endif  /* __STDC__ */

{
    va_list args;
    char    buff[BIG_BUFF_SIZE+1];
    int     stat;
    
    va_start(args,format);
    stat = vsprintf(buff,format,args);
    strlcpy(string,buff,maxlen);
    va_end(args);
    return stat;
}
#endif

