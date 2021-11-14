#include "string.h"

#include "assert.h"
#include "errno.h"

// Copies bytes from memory area s2 into s1, stopping after the first occurrence
// of byte c (converted to an unsigned char) is copied, or after n bytes are
// copied, whichever comes first. If copying takes place between objects that
// overlap, the behaviour is undefined.
//
// Returns a pointer to the byte after the copy of c in s1, or a null pointer if
// c was not found in the first n bytes of s2.
void* memccpy(void* s1, const void* s2, int c, size_t n)
{
    while (n-- > 0)
    {
        *(unsigned char*)s1 = *(unsigned char*)s2++;

        if (*(unsigned char*)s1++ == (unsigned char)c)
        {
            return s1;
        }
    }

    return NULL;
}

// Locates the first occurrence of c (converted to an unsigned char) in the
// initial n bytes (each interpreted as unsigned char) of the object pointed to
// by s.
// 
// Returns a pointer to the located byte, or a null pointer if the byte does not
// occur in the object.
void* memchr(const void* s, int c, size_t n)
{
    while (n-- > 0)
    {
        if (*(unsigned char*)s == (unsigned char)c)
        {
            return (void*)s;
        }

        s++;
    }

    return NULL;
}

// Compares the first n bytes (each interpreted as unsigned char) of the object 
// pointed to by s1 to the first n bytes of the object pointed to by s2.
// 
// The sign of a non-zero return value is determined by the sign of the
// difference between the values of the first pair of bytes (both interpreted as
// type unsigned char) that differ in the objects being compared.
// 
// Returns an integer greater than, equal to or less than 0, if the object
// pointed to by s1 is greater than, equal to or less than the object pointed to
// by s2 respectively.
int memcmp(const void* s1, const void* s2, size_t n)
{
    while (n-- > 0)
    {
        int diff = *(unsigned char*)s1++ - *(unsigned char*)s2++;

        if (diff != 0)
        {
            return diff;
        }
    }

    return 0;
}

// Copies n bytes from the object pointed to by s2 into the object pointed to by
// s1. If copying takes place between objects that overlap, the behaviour is
// undefined.
//
// Returns s1; no return value is reserved to indicate an error.
void* memcpy(void* s1, const void* s2, size_t n)
{
    void* backup = s1;

    while (n--)
    {
        *(unsigned char*)s1++ = *(unsigned char*)s2++;
    }

    return s1;
}

// Copies n bytes from the object pointed to by s2 into the object pointed to by
// s1. Copying takes place as if the n bytes from the object pointed to by s2
// are first copied into a temporary array of n bytes that does not overlap the
// objects pointed to by s1 and s2, and then the n bytes from the temporary
// array are copied into the object pointed to by s1.
//
// Returns s1; no return value is reserved to indicate an error.
void *memmove(void* s1, const void* s2, size_t n)
{
    void* backup = s1;

    if (s1 < s2)
    {
        while (n--)
        {
            *(unsigned char*)s1++ = *(unsigned char*)s2++;
        }
    }
    else if (s1 > s2)
    {
        while (n--)
        {
            *(unsigned char*)(s1 + n) = *(unsigned char*)(s2 + n);
        }
    }

    return backup;
}

// Copies c (converted to an unsigned char) into each of the first n bytes of
// the object pointed to by s.
//
// Returns s; no return value is reserved to indicate an error.
void* memset(void* s, int c, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        ((unsigned char*)s)[i] = (unsigned char)c;
    }

    return s;
}

// Appends a copy of the string pointed to by s2 (including the terminating null
// byte) to the end of the string pointed to by s1. The initial byte of s2
// overwrites the null byte at the end of s1. If copying takes place between
// objects that overlap, the behaviour is undefined.
//
// Returns s1; no return value is reserved to indicate an error.
char* strcat(char* s1, const char* s2)
{
    char* backup = s1;

    while (*s1++);
    s1--;
    while ((*s1++ = *s2++));

    return backup;
}

// Locates the first occurrence of c (converted to an unsigned char) in the
// string pointed to by s. The terminating null byte is considered to be part
// of the string.
//
// Returns a pointer to the byte, or a null pointer if the byte was not found.
char* strchr(const char* s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
        {
            return (char*)s;
        }
        
        s++;
    }

    return NULL;
}

// Compares the string pointed to by s1 to the string pointed to by s2.
//
// The sign of a non-zero return value is determined by the sign of the
// difference between the values of the first pair of bytes (both interpreted
// as type unsigned char) that differ in the strings being compared.
//
// Returns an integer greater than, equal to or less than 0, if the string
// pointed to by s1 is greater than, equal to or less than the string pointed to
// by s2 respectively.
int strcmp(const char* s1, const char* s2)
{
    while (*s1 && *s2)
    {
        int diff = *(unsigned char*)s1++ - *(unsigned char*)s2++;

        if (diff != 0)
        {
            return diff;
        }
    }

    if (*s1 != *s2)
    {
        return *s1 - *s2;
    }

    return 0;
}

// Copies the string pointed to by s2 (including the terminating null byte) into
// the array pointed to by s1. If copying takes place between objects that
// overlap, the behaviour is undefined.
// 
// Returns s1; no return value is reserved to indicate an error.
char* strcpy(char* s1, const char* s2)
{
    char* backup = s1;

    while ((*s1++ = *s2++));

    return backup;
}

// Computes the length of the maximum initial segment of the string pointed to
// by s1 which consists entirely of bytes not from the string pointed to by s2.
// 
// Returns the length of the computed segment of the string pointed to by s1;
// no return value is reserved to indicate an error.
size_t strcspn(const char* s1, const char* s2)
{
    for (int i = 0; 1; i++)
    {
        int j = 0;
        for (; s2[j] != 0; j++)
        {
            if (*s1 == s2[j])
            {
                break;
            }
        }

        if (s2[j] == 0)
        {
            return i;
        }
    }
}

// Returns a pointer to a new string, which is a duplicate of the string pointed
// to by s1. The returned pointer can be passed to free(). A null pointer is
// returned if the new string cannot be created.
//
// Returns a pointer to a new string on success. Otherwise it returns a null
// pointer and sets errno to indicate the error.
char* strdup(const char* s1)
{
    assert(0 && "strdup not implemented, requires malloc");

    return NULL;
}

// Maps the error number in errnum to a locale-dependent error message string
// and returns a pointer thereto. The string pointed to must not be modified by
// the program, but may be overwritten by a subsequent call to strerror() or
// perror().
//
// The contents of the error message strings returned by strerror() should be
// determined by the setting of the LC_MESSAGES category in the current locale.
// 
// The implementation will behave as if no function defined in this
// specification calls strerror().
// 
// The strerror() function will not change the setting of errno if successful.
// 
// Because no return value is reserved to indicate an error, an application
// wishing to check for error situations should set errno to 0, then call
// strerror(), then check errno.
// 
// This interface need not be reentrant.
// 
// Upon successful completion, strerror() returns a pointer to the generated
// message string. On error errno may be set, but no return value is reserved to
// indicate an error.
#define TO_STR_CASE(ident) case ident: return #ident;
char* strerror(int error)
{
    switch (error)
    {
        TO_STR_CASE(EPERM)
        TO_STR_CASE(ENOENT)
        TO_STR_CASE(ESRCH)
        TO_STR_CASE(EINTR)
        TO_STR_CASE(EIO)
        TO_STR_CASE(ENXIO)
        TO_STR_CASE(E2BIG)
        TO_STR_CASE(ENOEXEC)
        TO_STR_CASE(EBADF)
        TO_STR_CASE(ECHILD)
        TO_STR_CASE(EAGAIN)
        TO_STR_CASE(ENOMEM)
        TO_STR_CASE(EACCES)
        TO_STR_CASE(EFAULT)
        TO_STR_CASE(ENOTBLK)
        TO_STR_CASE(EBUSY)
        TO_STR_CASE(EEXIST)
        TO_STR_CASE(EXDEV)
        TO_STR_CASE(ENODEV)
        TO_STR_CASE(ENOTDIR)
        TO_STR_CASE(EISDIR)
        TO_STR_CASE(EINVAL)
        TO_STR_CASE(ENFILE)
        TO_STR_CASE(EMFILE)
        TO_STR_CASE(ENOTTY)
        TO_STR_CASE(ETXTBSY)
        TO_STR_CASE(EFBIG)
        TO_STR_CASE(ENOSPC)
        TO_STR_CASE(ESPIPE)
        TO_STR_CASE(EROFS)
        TO_STR_CASE(EMLINK)
        TO_STR_CASE(EPIPE)
        TO_STR_CASE(EDOM)
        TO_STR_CASE(ERANGE)
        TO_STR_CASE(EDEADLK)
        TO_STR_CASE(ENAMETOOLONG)
        TO_STR_CASE(ENOLCK)
        TO_STR_CASE(ENOSYS)
        TO_STR_CASE(ENOTEMPTY)
        TO_STR_CASE(ELOOP)
        TO_STR_CASE(EWOULDBLOCK)
        TO_STR_CASE(ENOMSG)
        TO_STR_CASE(EIDRM)
        TO_STR_CASE(ECHRNG)
        TO_STR_CASE(EL2NSYNC)
        TO_STR_CASE(EL3HLT)
        TO_STR_CASE(EL3RST)
        TO_STR_CASE(ELNRNG)
        TO_STR_CASE(EUNATCH)
        TO_STR_CASE(ENOCSI)
        TO_STR_CASE(EL2HLT)
        TO_STR_CASE(EBADE)
        TO_STR_CASE(EBADR)
        TO_STR_CASE(EXFULL)
        TO_STR_CASE(ENOANO)
        TO_STR_CASE(EBADRQC)
        TO_STR_CASE(EBADSLT)
        TO_STR_CASE(EDEADLOCK)
        TO_STR_CASE(EBFONT)
        TO_STR_CASE(ENOSTR)
        TO_STR_CASE(ENODATA)
        TO_STR_CASE(ETIME)
        TO_STR_CASE(ENOSR)
        TO_STR_CASE(ENONET)
        TO_STR_CASE(ENOPKG)
        TO_STR_CASE(EREMOTE)
        TO_STR_CASE(ENOLINK)
        TO_STR_CASE(EADV)
        TO_STR_CASE(ESRMNT)
        TO_STR_CASE(ECOMM)
        TO_STR_CASE(EPROTO)
        TO_STR_CASE(EMULTIHOP)
        TO_STR_CASE(EDOTDOT)
        TO_STR_CASE(EBADMSG)
        TO_STR_CASE(EOVERFLOW)
        TO_STR_CASE(ENOTUNIQ)
        TO_STR_CASE(EBADFD)
        TO_STR_CASE(EREMCHG)
        TO_STR_CASE(ELIBACC)
        TO_STR_CASE(ELIBBAD)
        TO_STR_CASE(ELIBSCN)
        TO_STR_CASE(ELIBMAX)
        TO_STR_CASE(ELIBEXEC)
        TO_STR_CASE(EILSEQ)
        TO_STR_CASE(ERESTART)
        TO_STR_CASE(ESTRPIPE)
        TO_STR_CASE(EUSERS)
        TO_STR_CASE(ENOTSOCK)
        TO_STR_CASE(EDESTADDRREQ)
        TO_STR_CASE(EMSGSIZE)
        TO_STR_CASE(EPROTOTYPE)
        TO_STR_CASE(ENOPROTOOPT)
        TO_STR_CASE(EPROTONOSUPPORT)
        TO_STR_CASE(ESOCKTNOSUPPORT)
        TO_STR_CASE(EOPNOTSUPP)
        TO_STR_CASE(EPFNOSUPPORT)
        TO_STR_CASE(EAFNOSUPPORT)
        TO_STR_CASE(EADDRINUSE)
        TO_STR_CASE(EADDRNOTAVAIL)
        TO_STR_CASE(ENETDOWN)
        TO_STR_CASE(ENETUNREACH)
        TO_STR_CASE(ENETRESET)
        TO_STR_CASE(ECONNABORTED)
        TO_STR_CASE(ECONNRESET)
        TO_STR_CASE(ENOBUFS)
        TO_STR_CASE(EISCONN)
        TO_STR_CASE(ENOTCONN)
        TO_STR_CASE(ESHUTDOWN)
        TO_STR_CASE(ETOOMANYREFS)
        TO_STR_CASE(ETIMEDOUT)
        TO_STR_CASE(ECONNREFUSED)
        TO_STR_CASE(EHOSTDOWN)
        TO_STR_CASE(EHOSTUNREACH)
        TO_STR_CASE(EALREADY)
        TO_STR_CASE(EINPROGRESS)
        TO_STR_CASE(ESTALE)
        TO_STR_CASE(EUCLEAN)
        TO_STR_CASE(ENOTNAM)
        TO_STR_CASE(ENAVAIL)
        TO_STR_CASE(EISNAM)
        TO_STR_CASE(EREMOTEIO)
        default:
            errno = EINVAL;
            return "Default Taken";
    }
}

// Computes the number of bytes in the string to which s points, not including
// the terminating null byte.
//
// Returns the length of s; no return value is reserved to indicate an error.
size_t strlen(const char* s)
{
    size_t i = 0;
    for (;s[i] != 0;i++);

    return i;
}

// Appends not more than n bytes (a null byte and bytes that follow it are not
// appended) from the array pointed to by s2 to the end of the string pointed to
// by s1. The initial byte of s2 overwrites the null byte at the end of s1. A
// terminating null byte is always appended to the result. If copying takes
// place between objects that overlap, the behaviour is undefined.
//
// Returns s1; no return value is reserved to indicate an error.
char* strncat(char* s1, const char* s2, size_t n)
{
    char* backup = s1;

    while (*s1++);

    for (size_t i = 0; i < n; i++)
    {
        if (!(*s1 = *s2++))
        {
            break;
        }

        s1++;
    }

    *s1 = 0;
    
    return backup;
}

// Compares not more than n bytes (bytes that follow a null byte are not
// compared) from the array pointed to by s1 to the array pointed to by s2.
//
// The sign of a non-zero return value is determined by the sign of the
// difference between the values of the first pair of bytes (both interpreted as
// type unsigned char) that differ in the strings being compared.
//
// Returns an integer greater than, equal to or less than 0, if the possibly
// null-terminated array pointed to by s1 is greater than, equal to or less than
// the possibly null-terminated array pointed to by s2 respectively.
int strncmp(const char* s1, const char* s2, size_t n)
{
    while (*s1 && *s2 && n--)
    {
        int diff = *(unsigned char*)s1++ - *(unsigned char*)s2++;

        if (diff != 0)
        {
            return diff;
        }
    }

    return 0;
}

// Copies not more than n bytes (bytes that follow a null byte are not copied)
// from the array pointed to by s2 to the array pointed to by s1. If copying
// takes place between objects that overlap, the behaviour is undefined.
//
// If the array pointed to by s2 is a string that is shorter than n bytes, null
// bytes are appended to the copy in the array pointed to by s1, until n bytes
// in all are written.
// 
// Returns s1; no return value is reserved to indicate an error.
char* strncpy(char* s1, const char* s2, size_t n)
{
    char* backup = s1;

    while ((*s1++ = *s2++ && n--));

    return backup;
}

// Locates the first occurrence in the string pointed to by s1 of any byte from
// the string pointed to by s2.
//
// Returns a pointer to the byte or a null pointer if no byte from s2 occurs in
// s1.
char* strpbrk(const char* s1, const char* s2)
{
    while (*s1)
    {
        size_t i = 0;
        while (s2[i])
        {
            if (*s1 == s2[i])
            {
                return (char*)s1;
            }
        }

        s1++;
    }

    return NULL;
}

// Locates the last occurrence of c (converted to a char) in the string pointed
// to by s. The terminating null byte is considered to be part of the string.
//
// Returns a pointer to the byte or a null pointer if c does not occur in the string.
char* strrchr(const char* s, int c)
{
    char* last = NULL;
    while (*s)
    {
        if (*s == (char)c)
        {
            last = (char*)s;
        }

        s++;
    }

    return last;
}

// Computes the length of the maximum initial segment of the string pointed to
// by s1 which consists entirely of bytes from the string pointed to by s2.
//
// Returns the length of s1; no return value is reserved to indicate an error.
size_t strspn(const char* s1, const char* s2)
{
    size_t len = 0;

    while (s1[len])
    {
        size_t i = 0;
        while (s2[i])
        {
            if (s1[len] == s2[i])
            {
                break;
            }
            i++;
        }

        if (!s2[i])
        {
            break;
        }

        i++;
    }

    return len;
}

// Locates the first occurrence in the string pointed to by s1 of the sequence
// of bytes (excluding the terminating null byte) in the string pointed to by
// s2.
// 
// Returns a pointer to the located string or a null pointer if the string is
// not found.
// If s2 points to a string with zero length, the function returns s1.
char* strstr(const char* s1, const char* s2)
{
    for (size_t i = 0; s1[i] != 0; i++)
    {
        for (size_t j = 0; ; j++)
        {
            if (s2[j] == 0)
            {
                return (char*)s1 + i;
            }

            if (s1[i + j] == 0)
            {
                return NULL;
            }

            if (s1[i + j] != s2[j])
            {
                break;
            }
        }
    }

    return NULL;
}

// A sequence of calls to strtok() breaks the string pointed to by s1 into a
// sequence of tokens, each of which is delimited by a byte from the string
// pointed to by s2. The first call in the sequence has s1 as its first
// argument, and is followed by calls with a null pointer as their first
// argument. The separator string pointed to by s2 may be different from call
// to call.
// The first call in the sequence searches the string pointed to by s1 for the 
// first byte that is not contained in the current separator string pointed to
// by s2. If no such byte is found, then there are no tokens in the string
// pointed to by s1 and strtok() returns a null pointer. If such a byte is
// found, it is the start of the first token.
// 
// The strtok() function then searches from there for a byte that is contained
// in the current separator string. If no such byte is found, the current token
// extends to the end of the string pointed to by s1, and subsequent searches
// for a token will return a null pointer. If such a byte is found, it is
// overwritten by a null byte, which terminates the current token. The strtok()
// function saves a pointer to the following byte, from which the next search
// for a token will start.
// 
// Each subsequent call, with a null pointer as the value of the first argument,
// starts searching from the saved pointer and behaves as described above.
// 
// The implementation will behave as if no function defined in this document
// calls strtok().
// 
// The strtok() interface need not be reentrant.
// 
// The function strtok_r() considers the null-terminated string s as a sequence
// of zero or more text tokens separated by spans of one or more characters from
// the separator string sep. The argument lasts points to a user-provided
// pointer which points to stored information necessary for strtok_r() to
// continue scanning the same string.
// 
// In the first call to strtok_r(), s points to a null-terminated string, sep to
// a null-terminated string of separator characters and the value pointed to by
// lasts is ignored. The function strtok_r() returns a pointer to the first
// character of the first token, writes a null character into s immediately
// following the returned token, and updates the pointer to which lasts points.
// 
// In subsequent calls, s is a NULL pointer and lasts will be unchanged from the
// previous call so that subsequent calls will move through the string s,
// returning successive tokens until no tokens remain. The separator string sep
// may be different from call to call. When no token remains in s, a NULL
// pointer is returned.
// 
// Upon successful completion, strtok() returns a pointer to the first byte of a
// token. Otherwise, if there is no token, strtok() returns a null pointer.
// The function strtok_r() returns a pointer to the token found, or a NULL
// pointer when no token is found.
char* strtok(char* s1, const char* s2)
{
    assert(0 && "Not Yet Implemented");
}

// A sequence of calls to strtok() breaks the string pointed to by s1 into a
// sequence of tokens, each of which is delimited by a byte from the string
// pointed to by s2. The first call in the sequence has s1 as its first
// argument, and is followed by calls with a null pointer as their first
// argument. The separator string pointed to by s2 may be different from call
// to call.
// The first call in the sequence searches the string pointed to by s1 for the 
// first byte that is not contained in the current separator string pointed to
// by s2. If no such byte is found, then there are no tokens in the string
// pointed to by s1 and strtok() returns a null pointer. If such a byte is
// found, it is the start of the first token.
// 
// The strtok() function then searches from there for a byte that is contained
// in the current separator string. If no such byte is found, the current token
// extends to the end of the string pointed to by s1, and subsequent searches
// for a token will return a null pointer. If such a byte is found, it is
// overwritten by a null byte, which terminates the current token. The strtok()
// function saves a pointer to the following byte, from which the next search
// for a token will start.
// 
// Each subsequent call, with a null pointer as the value of the first argument,
// starts searching from the saved pointer and behaves as described above.
// 
// The implementation will behave as if no function defined in this document
// calls strtok().
// 
// The strtok() interface need not be reentrant.
// 
// The function strtok_r() considers the null-terminated string s as a sequence
// of zero or more text tokens separated by spans of one or more characters from
// the separator string sep. The argument lasts points to a user-provided
// pointer which points to stored information necessary for strtok_r() to
// continue scanning the same string.
// 
// In the first call to strtok_r(), s points to a null-terminated string, sep to
// a null-terminated string of separator characters and the value pointed to by
// lasts is ignored. The function strtok_r() returns a pointer to the first
// character of the first token, writes a null character into s immediately
// following the returned token, and updates the pointer to which lasts points.
// 
// In subsequent calls, s is a NULL pointer and lasts will be unchanged from the
// previous call so that subsequent calls will move through the string s,
// returning successive tokens until no tokens remain. The separator string sep
// may be different from call to call. When no token remains in s, a NULL
// pointer is returned.
// 
// Upon successful completion, strtok() returns a pointer to the first byte of a
// token. Otherwise, if there is no token, strtok() returns a null pointer.
// The function strtok_r() returns a pointer to the token found, or a NULL
// pointer when no token is found.
char* strtok_r(char* s1, const char* s2, char** lasts)
{
    assert(0 && "Not Yet Implemented");
}