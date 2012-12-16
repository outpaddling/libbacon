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

#if defined(COHERENT) || defined(SCO_SV)
#include "bacon.h"

/****************************************************************************
Name:
    Get network host name.

Description: 
    This function provides a pseudo-compatible gethostname() for
    SCO and COHERENT systems, which lack the standard gethostname(3)
    function.  The hostname is retrieved from /etc/uucpname.
    
    The source code is macro-guarded, so that object code is only
    generated on these systems.  To enable the function, you must
    compile with -DCOHERENT or -DSCO_SV.
 
Author: 
    Jason W. Bacon

Returns: 
    0 upon success, -1 upon failure.
****************************************************************************/

int     gethostname(hostname,maxlen)
char    hostname[];
int     maxlen;

{
    FILE    *fp;
    char    temp[1024];
    
    fp = fopen("/etc/uucpname","r");
    if ( fp != NULL )
    {
	fscanf(fp,"%s",temp);
	fclose(fp);
	strlcpy(hostname,temp,maxlen);
	return 0;
    }
    else
    {
	strlcpy(hostname,"unknown.host",maxlen);
	return -1;
    }
}
#endif

