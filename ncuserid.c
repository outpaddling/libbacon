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
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>
#include "bacon.h"

/****************************************************************************
 * Author: Jason W. Bacon
 * Acadix Software Systems
 * http://www.execpc.com/~acadix
 * acadix@execpc.com
 *
 * Arguments:
 *      buff:   char array for storing user name
 *      maxlen: size of array 'buff'
 * Return values:   pointer to buff
 * Description:
 *      This is a safe and flexible version of the standard cuserid()
 *      function.  Some systems don't specify a minimum length for
 *      the buffer.  Others require char buff[L_cuserid].
 *
 ****************************************************************************/

char    *ncuserid(buff,maxlen)
char    *buff;
unsigned    maxlen;

{
    struct passwd *pwent;
    static char static_buff[PATH_MAX+1];
    
    pwent = getpwuid(getuid());
    /* If buff isn't NULL, put the name there */
    if ( buff != NULL )
    {
	strlcpy(buff,pwent->pw_name,maxlen);
	return buff;
    }
    else    /* Leave it in the internal static buffer, as cuserid() does. */
    {
	strlcpy(static_buff,pwent->pw_name,PATH_MAX);
	return static_buff;
    }
}

