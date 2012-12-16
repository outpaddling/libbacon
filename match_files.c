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

#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <fnmatch.h>
#include "bacon.h"

/****************************************************************************
 * Author: Jason W. Bacon
 * Acadix Software Systems
 * http://www.execpc.com/~acadix
 * acadix@execpc.com
 *
 * Arguments:
 * Return values:   Number of files matching filespec
 * Description:
 *      Simple alternative to glob().  match_files() fills a simple
 *      array of string pointers vs. glob()'s complicated glob_t
 *      structures.
 ****************************************************************************/

int     match_files(file_spec,list,max_files,flags)
char    *file_spec;
char    *list[];
size_t  max_files;
int     flags;

{
    DIR             *dir;
    struct dirent   *dir_entry;
    size_t          files = 0;
    
    if ( (dir = opendir(".")) == NULL )
	return M_ERROR;
    
    /* Find matching files in current directory */
    while ( (files < max_files) && ((dir_entry = readdir(dir)) != NULL ) )
    {
	if ( fnmatch(file_spec,dir_entry->d_name,flags) == 0 )
	    list[files++] = strdup(dir_entry->d_name);
    }
    list[files] = NULL; /* Cap pointer array */
    closedir(dir);
    return files;
}

