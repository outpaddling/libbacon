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

/**
 * \addtogroup libbacon
 *  @{
 */

/**
 *  \brief  Compute the greatest common divisor.
 *
 *  Computes the greatest common divisor of two natural
 *  numbers a and b.
 * 
 *  \return The greatest common divisor of a and b.
 */

unsigned long   gcd(unsigned long a,    /* natural number */
		    unsigned long b     /* natural number */
		    )

{
    if ( a == 0 ) return b;
    if ( b == 0 ) return a;
    if ( a < b )
	return gcd(b,a);
    else
	return gcd(b, a % b);
}


/**
 *  \brief  Compute the least common multiple.
 *
 *  Computes the least common multiple of two natural
 *  numbers a and b.  Note that this function may fail for relatively
 *  small values, as their LCM may be beyond the range of a 32-bit
 *  integer.
 * 
 *  \return The least common multiple of a and b.
 */

unsigned long   lcm(unsigned long a,unsigned long b)

{
    return a * b / gcd(a,b);
}

/** @} */

