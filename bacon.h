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

#if !defined(_STDIO_H_) && !defined(__STDIO_H__)
#include <stdio.h>
#endif

#if !defined(_STDARG_H_) && !defined(__STDARG_H__)
#include <stdarg.h>
#endif

#if !defined(_SYS_TYPE_H)
#include <sys/types.h>
#endif

#if !defined(_SYS_TIME_H)
#include <sys/time.h>
#endif

#if 0   /* Not sure this is needed anywhere anymore */
typedef void (*sig_t)();
#endif

#ifdef SCO_SV
void    *alloca(size_t);
#endif

/* Use POSIX default if not defined */
#ifndef PATH_MAX
#define PATH_MAX    255
#endif

/* Process functions */
#define P_NOWAIT  0
#define P_WAIT    1
#define P_NOECHO  0
#define P_ECHO    1

/* param reading functions */
#define PARAM_NAME_MAX      64
#define LONG_STRING_MAX     64
#define DOUBLE_STRING_MAX   64
#define MATRIX_STRING_MAX   1024

/* match_files() */
#define M_ERROR     -1

#define P_TERM_STATUS(s)    ((s) & 0xff)
#define P_EXIT_CODE(s)      (((s) & 0x0000ff00) >> 8)

#define P_EXEC_FAILED(s)    ( (s) & 0x8000 )

/* General stuff */
#ifndef MIN
#define MIN(a,b)    ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a,b)    ((a) > (b) ? (a) : (b))
#endif

#ifndef ISIDENT
#define ISIDENT(c)  ( isalnum(c) | ((c)=='_') )
#endif

#ifndef MALLOC
#define MALLOC(nelem,type)   ((type *)malloc((nelem)*sizeof(type)))
#endif

#ifndef REALLOC
#define REALLOC(ptr,nelem,type) ((type *)realloc((ptr),(nelem)*sizeof(type)))
#endif

/* Macro version in case somebody needs to save a few instruction cycles */
#define LCM(a,b)    ((a)*(b)/gcd(a,b))

#if defined(hpux) || defined(solaris)
int vsnprintf(char *,size_t,const char *,va_list);
#endif

/* Helper type for bsearch(), qsort() etc with string pointer arrays */
typedef int (*strptrcmp_t)(const void *,const void *);

/**
 * \defgroup libbacon   Various utility functions
 *  @{
 */

/**
 *  \addtogroup libbacon
 *
 *  The debug_t type provides common library functions with information
 *  from the calling program. This allows the function to produce meaningful
 *  error and warning messages.
 */

typedef struct
{
    FILE    *log_fp;
    char    *prog_name;
    char    *log_file;
}   debug_t;

/** @} */

/* bc_eval.c */
char *bc_eval(debug_t *debug, char *dest, char *src, size_t dest_max);
/* check_int_range.c */
int check_int_range(debug_t *debug, int val, int min, int max, char *name);
/* cleanup_exit.c */
void cleanup_exit(int status, ...);
/* difftimeday.c */
time_t difftimeofday(struct timeval *t1, struct timeval *t2);
/* eprintf.c */
int eprintf(const char *format, ...);
/* factorial.c */
double factorial(unsigned n);
/* fast_cp.c */
int fast_cp(char *src, char *dest);
/* fd_purge.c */
void fd_purge(int fd);
/* fgetline.c */
size_t fgetline(FILE *fp, char *buff, size_t maxlen);
/* file_mod_cmp.c */
int file_mod_cmp(char *file1, char *file2);
/* gcd.c */
unsigned long gcd(unsigned long a, unsigned long b);
unsigned long lcm(unsigned long a, unsigned long b);
/* get_home_dir.c */
char *get_home_dir(char dir[], int maxlen);
/* get_param_code.c */
int get_param_code(char *param_name, char *param_name_list[], size_t nelem);
int strptrcasecmp(char **p1, char **p2);
/* gethostname.c */
/* getpwinfo.c */
struct passwd *getpwinfo(struct passwd *pwent);
/* gettimeofday.c */
/* init_debug.c */
void init_debug(debug_t *debug, char *prog_name);
/* ltostrn.c */
char *ltostrn(char string[], long val, unsigned base, unsigned maxlen);
/* match_files.c */
int match_files(char *file_spec, char *list[], size_t max_files, int flags);
/* memicmp.c */
int memicmp(char *str1, char *str2, int len);
/* meta_chars.c */
int meta_chars(char *dest, char *src, size_t dest_len);
/* mv.c */
int mv(char *src, char *dest);
/* ncuserid.c */
char *ncuserid(char *buff, unsigned maxlen);
/* num_size.c */
int num_size(long val);
/* parse_cmd.c */
void parse_cmd(char *argv[], char *cmd);
/* polar_distance.c */
double polar_distance(double rho1, double theta1, double rho2, double theta2);
/* poly.c */
double poly(double x, double coefficient[], int order);
/* read_double.c */
double read_double(debug_t *debug, FILE *fp);
/* read_double_matrix.c */
double **read_double_matrix(debug_t *debug, FILE *fp, size_t rows, size_t cols);
void print_double_matrix(debug_t *debug, double **matrix, size_t rows, size_t cols);
/* read_long.c */
long read_long(debug_t *debug, FILE *fp);
/* read_long_matrix.c */
long **read_long_matrix(debug_t *debug, FILE *fp, size_t rows, size_t cols);
void print_long_matrix(debug_t *debug, long **matrix, size_t rows, size_t cols);
/* read_param_name.c */
char *read_param_name(FILE *fp, char *param_name, size_t maxlen);
/* read_param_val.c */
char *read_param_value(FILE *fp, char *param_value, size_t maxlen);
/* read_string.c */
char *read_string(debug_t *debug, FILE *fp, size_t max_len);
/* read_string_matrix.c */
char ***read_string_matrix(debug_t *debug, FILE *fp, size_t rows, size_t cols);
void print_string_matrix(debug_t *debug, char ***matrix, size_t rows, size_t cols);
/* rint.c */
double rint(double num);
/* rmkdir.c */
int rmkdir(char *path, mode_t mode);
/* spawnlp.c */
int spawnlp(int parent_action, int echo, char *infile, char *outfile, char *errfile, char *arg0, ...);
/* spawnvp.c */
int spawnvp(int parent_action, int echo, char *argv[], char *infile, char *outfile, char *errfile);
void redirect(char *infile, char *outfile, char *errfile);
/* strbasecpy.c */
char *strbasecpy(char *dest, char *src, char *dest_base, int len);
/* strblank.c */
int strblank(char *str);
/* strcap.c */
char *strcap(char *dest, char *src, size_t maxlen);
/* strcasecmp.c */
int strcasecmp(const char *s1, const char *s2);
/* strcomment.c */
int strcomment(char *buff, char *starter);
/* strlcat.c */
size_t strlcat(char *dest, const char *src, size_t maxlen);
/* strlcpy.c */
size_t strlcpy(char *dest, const char *src, size_t len);
/* strlower.c */
char *strlower(char *dest, char *src, size_t maxlen);
/* strptrcmp.c */
int strptrcmp(char **p1, char **p2);
/* strupper.c */
#if defined(sun)
char *strsep(char **stringp, const char *delim);
#endif
char *strupper(char *dest, char *src, size_t maxlen);
/* strword.c */
char *strword(char *string, char *word);
/* usage.c */
void usage(char *format_string, ...);
/* usleep.c */
/* viscpy.c */
char *viscpy(unsigned char dest[], unsigned char src[], size_t maxlen);


