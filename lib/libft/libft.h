/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfrancie <cfrancie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 10:57:07 by cfrancie          #+#    #+#             */
/*   Updated: 2023/04/22 19:15:05 by cfrancie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*ctype*/

/**
 * @brief checks for an alphanumeric character; it is equivalent to 
 * (isalpha(c) || isdigit(c)).
 * 
 * @param c 
 * @return true 
 * @return false 
 */
bool				ft_isalnum(int c);

/**
 * @brief checks for an alphabetic character; in the standard "C" locale, it is
 * equivalent to (isupper(c) || islower(c)).  In some locales, there may be
 * additional characters for which isalpha()  is  true—letters which are neither
 * uppercase nor lowercase.
 * 
 * @param c 
 * @return true 
 * @return false 
 */
bool				ft_isalpha(int c);

/**
 * @brief checks whether c is a 7-bit unsigned char value that fits into the
 * ASCII character set.
 * 
 * @param c 
 * @return true 
 * @return false 
 */
bool				ft_isascii(int c);

/**
 * @brief checks for a blank character; that is, a space or a tab.
 * 
 * @param c 
 * @return true 
 * @return false 
 */
bool				ft_isblank(int c);

/**
 * @brief checks for a control character.
 * 
 * @param c 
 * @return true 
 * @return false 
 */
bool				ft_iscntrl(int c);

/**
 * @brief checks for a digit (0 through 9).
 * 
 * @param c 
 * @return true 
 * @return false 
 */
bool				ft_isdigit(int c);

/**
 * @brief checks for any printable character except space.
 * 
 * @param c 
 * @return true 
 * @return false 
 */
bool				ft_isgraph(int c);

/**
 * @brief checks for any printable character including space.
 * 
 * @param c 
 * @return true 
 * @return false 
 */
bool				ft_isprint(int c);

/**
 * @brief checks for any printable character which is not a space or an
 * alphanumeric character.
 * 
 * @param c 
 * @return true 
 * @return false 
 */
bool				ft_ispunct(int c);

/**
 * @brief checks for white-space characters. In the "C" and "POSIX" locales,
 * these are: space, form-feed ('\f'), newline ('\n'), carriage return ('\r'),
 * horizontal tab ('\t'), and vertical tab ('\v').
 * 
 * @param c 
 * @return true 
 * @return false 
 */
bool				ft_isspace(int c);

/**
 * @brief checks for hexadecimal digits, that is, one of
 * 0 1 2 3 4 5 6 7 8 9 a b c d e f A B C D E F.
 * 
 * @param c 
 * @return true 
 * @return false 
 */
bool				ft_isxdigit(int c);

/**
 * @brief converts a upper-case letter to the corresponding lower-case letter.
 * 
 * @param c 
 * @return int 
 */
int					ft_tolower(int c);

/**
 * @brief converts a lower-case letter to the corresponding upper-case letter.
 * 
 * @param c 
 * @return int 
 */
int					ft_toupper(int c);

/*string*/

/**
 * @brief The ft_bzero() function erases the data in the n bytes of the memory
 * starting at the location pointed to by s, by writing zeros (bytes containing
 * '\0') to that area.
 * 
 * @param s 
 * @param n 
 */
void				ft_bzero(void *s, size_t n);

/**
 * @brief The ft_memchr() function scans the initial n bytes of the memory area
 * pointed to by s for the first instance of c. Both c and the bytes of the
 * memory area pointed to by s are interpreted as unsigned char.
 * 
 * @param s 
 * @param c 
 * @param n 
 * @return void* 
 */
void				*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief The ft_memcmp() function compares the first n bytes (each interpreted
 * as unsigned char) of the memory areas s1 and s2.
 * 
 * @param s1 
 * @param s2 
 * @param n 
 * @return int 
 */
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief The ft_memcpy() function copies n bytes from memory area src to memory
 * area dest. The memory areas must not overlap. Use memmove(3) if the memory
 * areas do overlap.
 * 
 * @param dest 
 * @param src 
 * @param n 
 * @return void* 
 */
void				*ft_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief The ft_memmove() function copies n bytes from memory area src to
 * memory area dest. The memory areas may overlap: copying takes place as though
 * the bytes in src are first copied into a temporary array that does not
 * overlap src or dest, and the bytes are then copied from the temporary array
 * to dest.
 * 
 * @param dest 
 * @param src 
 * @param n 
 * @return void* 
 */
void				*ft_memmove(void *dest, const void *src, size_t n);

/**
 * @brief The ft_memset() function fills the first n bytes of the memory area
 * pointed to by s with the constant byte c.
 * 
 * @param s 
 * @param c 
 * @param n 
 * @return void* 
 */
void				*ft_memset(void *s, int c, size_t n);

/**
 * @brief This function catenates the string pointed to by src, after the string
 * pointed to by dst (overwriting its terminating null byte). The programmer is
 * responsible for allocating a destination buffer large enough, that is,
 * ft_strlen(dst) + ft_strlen(src) + 1.
 * 
 * @param dest 
 * @param src 
 * @return char* 
 */
char				*ft_strcat(char *dest, const char *src);

/**
 * @brief The ft_strchr() function returns a pointer to the first occurrence of
 * the character c in the string s.
 * 
 * @param s 
 * @param c 
 * @return char* 
 */
char				*ft_strchr(const char *s, int c);

/**
 * @brief These functions copy the string pointed to by src, into a string at
 * the buffer pointed to by dst. The programmer is responsible for allocating a
 * destination buffer large enough, that is, strlen(src) + 1. For the difference
 * between the two functions, see RETURN VALUE.
 * 
 * @param dst 
 * @param src 
 * @return char* 
 */
char				*ft_strcpy(char *dst, const char *src);

/**
 * @brief The ft_strcmp() function compares the two strings s1 and s2. The
 * locale is not taken into account (for a locale-aware comparison, see
 * ft_strcoll(3)). The comparison is done using unsigned characters.
 * 
 * @param s1 
 * @param s2 
 * @return int 
 */
int					ft_strcmp(const char *s1, const char *s2);

/**
 * @brief The ft_strlcat() function appends the NUL-terminated string src to the
 * end of dst. It will append at most size - strlen(dst) - 1 bytes,
 * NUL-terminating the result.
 * 
 * @param dst 
 * @param src 
 * @param size 
 * @return size_t 
 */
size_t				ft_strlcat(char *dst, const char *src, size_t size);

/**
 * @brief The ft_strlcpy() function copies up to size - 1 characters from the
 * NUL-terminated string src to dst, NUL-terminating the result.
 * 
 * @param dst 
 * @param src 
 * @param size 
 * @return size_t 
 */
size_t				ft_strlcpy(char *dst, const char *src, size_t size);

/**
 * @brief The ft_strnlen() function returns the number of bytes in the string
 * pointed to by s, excluding the terminating null byte ('\0'), but at most
 * maxlen. In doing this, strnlen() looks only at the first maxlen characters in
 * the string pointed to by s and never beyond s[maxlen-1].
 * 
 * @param s 
 * @param maxlen 
 * @return size_t 
 */
size_t				ft_strnlen(const char *s, size_t maxlen);

/**
 * @brief The ft_strlen() function calculates the length of the string pointed
 * to by s, excluding the terminat‐ing null byte ('\0').
 * 
 * @param s 
 * @return size_t 
 */
size_t				ft_strlen(const char *s);

/**
 * @brief This function catenates the input character sequence contained in a
 * null-padded fixed-width buffer, into a string at the buffer pointed to by
 * dst. The programmer is responsible for allocating a des‐tination buffer
 * large enough, that is, ft_strlen(dst) + ft_strnlen(src, sz) + 1.
 * 
 * @param dest 
 * @param src 
 * @param n 
 * @return char* 
 */
char				*ft_strncat(char *dest, const char *src, size_t n);

/**
 * @brief The ft_strncmp() function is similar as ft_strcmp(), except it
 * compares only the first (at most) n bytes of s1 and s2.
 * 
 * @param s1 
 * @param s2 
 * @param n 
 * @return int 
 */
int					ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief These functions copy the string pointed to by src into a null-padded
 * character sequence at the fixed-width buffer pointed to by dst. If the
 * destination buffer, limited by its size, isn't large enough to hold the copy,
 * the resulting character sequence is truncated. For the difference between the
 * two functions, see RE‐TURN VALUE.
 * 
 * @param dest 
 * @param src 
 * @param size 
 * @return char* 
 */
char				*ft_strncpy(char *dest, const char *src, size_t size);

/**
 * @brief The ft_strndup() function is similar, but copies at most n bytes. If s
 * is longer than n, only n bytes are copied, and a terminating null byte ('\0')
 * is added.
 * 
 * @param src 
 * @param size 
 * @return char* 
 */
char				*ft_strndup(const char *src, size_t size);

/**
 * @brief The ft_strnstr() function locates the first occurrence of the
 * null-terminated string little in the string big, where not more than len
 * characters are searched. Characters that appear after a ‘\0’ character are
 * not searched. Since the strnstr() function is a FreeBSD specific API, it
 * should only be used when portability is not a concern.
 * 
 * @param big 
 * @param little 
 * @param size 
 * @return char* 
 */
char				*ft_strnstr(const char *big, const char *little,
						size_t size);

/**
 * @brief The ft_strrchr() function returns a pointer to the last occurrence of
 * the character c in the string s.
 * 
 * @param s 
 * @param c 
 * @return char* 
 */
char				*ft_strrchr(const char *s, int c);

/**
 * @brief The ft_strrev() function reverses the string str in place.
 * 
 * @param str 
 */
void				ft_strrev(char *str);

/**
 * @brief The ft_strstr() function finds the first occurrence of the substring
 * needle in the string haystack. The termi‐nating null bytes ('\0') are not
 * compared.
 * 
 * @param big 
 * @param little 
 * @return char* 
 */
char				*ft_strstr(const char *big, const char *little);

/*stdlib*/

/**
 * @brief The ft_atof() function converts the initial portion of the string
 * pointed to by nptr to long double. The behavior is the same as
 * ft_strtod(nptr, NULL); except that ft_atof() does not detect errors.
 * 
 * @param str 
 * @return double 
 */
long double			ft_atof(char *str);

/**
 * @brief The ft_atoi() function converts the initial portion of the string
 * pointed to by nptr to int. The behavior is the same as
 * ft_strtol(nptr, NULL, 10); except that ft_atoi() does not detect errors.
 * 
 * @param nptr 
 * @return int 
 */
int					ft_atoi(const char *nptr);

/**
 * @brief The ft_atol() function converts the initial portion of the string
 * pointed to by nptr to long. The behavior is the same as
 * ft_strtol(nptr, NULL, 10); except that ft_atol() does not detect errors.
 * 
 * @param str 
 * @return long 
 */
long				ft_atol(const char *str);

/**
 * @brief The calloc() function allocates memory for an array of nmemb elements
 * of size bytes each and returns a pointer to the allocated memory. The memory
 * is set to zero. If nmemb or size is 0, then calloc() returns a unique pointer
 * value that can later be successfully passed to free(). If the multiplication
 * of nmemb and size would result in integer overflow, then calloc() returns an
 * error. By contrast, an integer overflow would not be detected in the
 * following call to malloc(), with the result that an incorrectly sized block
 * of memory would be allocated: malloc(nmemb * size);
 * 
 * @param nmemb 
 * @param size 
 * @return void* 
 */
void				*ft_calloc(size_t nmemb, size_t size);

/**
 * @brief The ft_itoa() function converts the integer n into a string. The
 * ft_itoa() function allocates (with malloc(3)) and returns a string
 * representing the integer received as an argument. Negative numbers must be
 * handled.
 * 
 * @param n 
 * @return char* 
 */
char				*ft_itoa(int n);

/**
 * @brief The strdup() function returns a pointer to a new string which is a
 * duplicate of the string s. Memory for the new string is obtained with
 * malloc(3), and can be freed with free(3).
 * 
 * @param s 
 * @return char* 
 */
char				*ft_strdup(const char *s);

/* other*/

/*  bonus*/

/**
 * @brief The ft_lstnew() function allows (with malloc(3)) and returns a new
 * element. The member variable 'content' is initialized with the value of the
 * parameter content' parameter. The variable 'next' is initialized to NULL.
 * 
 * @param content 
 * @return t_list* 
 */
t_list				*ft_lstnew(void *content);

/**

	* @brief The ft_lstadd_front() function adds the element new at the beginning of
 * the list.
 * 
 * @param lst 
 * @param new 
 */
void				ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief The ft_lstsize() function counts the number of elements in a list.
 * 
 * @param lst 
 * @return int 
 */
int					ft_lstsize(t_list *lst);

/**
 * @brief The ft_lstlast() function returns the last element of the list.
 * 
 * @param lst 
 * @return t_list* 
 */
t_list				*ft_lstlast(t_list *lst);

/**
 * @brief The ft_lstadd_back() function adds the element new at the end of the
 * list.
 * @param lst 
 * @param new 
 */
void				ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief The ft_lstdelone() function takes as a parameter an element and frees
 * the memory of the element's content using the function 'del' given as a
 * parameter and free the element. The memory of 'next' must not be freed.
 * 
 * @param lst 
 * @param del 
 */
void				ft_lstdelone(t_list *lst, void (*del)(void *));

/**
 * @brief The ft_lstclear() function deletes and frees the given element and
 * every successor of that element, using the function 'del' and free(3).
 * Finally, the pointer to the list must be set to NULL.
 * 
 * @param lst 
 * @param del 
 */
void				ft_lstclear(t_list **lst, void (*del)(void *));

/**
 * @brief The ft_lstiter() function iterates the list lst and applies the
 * function f to the content of each element.
 * 
 * @param lst 
 * @param f 
 */
void				ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief The ft_lstmap() function iterates the list lst and applies the
 * function f to the content of each element. Creates a new list resulting of
 * the successive applications of the function f. The 'del' function is used to
 * delete the content of an element if needed.
 * 
 * @param lst 
 * @param f 
 * @param del 
 * @return t_list* 
 */
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

/**
 * @brief The ft_abs() function returns the absolute value of the integer n.
 * 
 * @param n 
 * @return int 
 */
int					ft_abs(int n);

/**
 * @brief The ft_intlen() function returns the number of digits in the integer
 * n.
 * 
 * @param n 
 * @return int 
 */
int					ft_intlen(int n);

/**
 * @brief The ft_ldabs() function returns the absolute value of the long double
 * n.
 * @param n 
 * @return long double 
 */
long double			ft_ldabs(long double n);

/**
 * @brief The ft_max() function returns the number of digits in the long
 * 
 * @param a 
 * @param b 
 * @return true 
 * @return false 
 */
int					ft_max(int a, int b);

/**
 * @brief The ft_min() function returns the minimum of the two integers a and b.
 * 
 * @param a 
 * @param b 
 * @return true 
 * @return false 
 */
int					ft_min(int a, int b);

/**
 * @brief The ft_putchar_fd() function writes the character 'c' to the given
 * file descriptor
 * 
 * @param c 
 * @param fd 
 */
void				ft_putchar_fd(char c, int fd);

/**
 * @brief The ft_putchar() function writes the character 'c' to the standard
 * output.
 * 
 * @param c 
 */
void				ft_putchar(char c);

/**
 * @brief The ft_putendl_fd() function writes the string 's' to the given file
 * descriptor, followed by a newline.
 * 
 * @param s 
 * @param fd 
 */
void				ft_putendl_fd(char *s, int fd);

/**
 * @brief The ft_putnbr_fd() function writes the integer 'n' to the given file
 * descriptor.
 * 
 * @param n 
 * @param fd 
 */
void				ft_putnbr_fd(int n, int fd);

/**
 * @brief The ft_putstr_fd() function writes the string 's' to the given file
 * descriptor.
 * 
 * @param s 
 * @param fd 
 */
void				ft_putstr_fd(char *s, int fd);

/**
 * @brief The ft_realloc()  function  changes the size of the memory block pointed
 * to by ptr to size bytes.  The contents of the memory will be unchanged in the
 * range from the start of the region up to the minimum of the old and new
 * sizes. If the new size is larger than the old size, the added memory will not
 * be initialized. If ptr is NULL, then the call is equivalent to malloc(size),
 * for all values of size. If size is equal to zero, and ptr is not NULL, then
 * the call is equivalent to free(ptr) (but see "Nonportable behavior" for
 * portability issues). Unless ptr is NULL, it must have been returned by an
 * earlier call to malloc or related functions. If the area pointed to was
 * moved, a free(ptr) is done.
 * 
 * @param ptr 
 * @param size 
 * @return void* 
 */
void				*ft_realloc(void *ptr, size_t size);

/**
 * @brief The ft_putstr() function writes the string 's' to the standard output.
 * 
 * @param str 
 */
void				ft_putstr(char *str);

/**
 * @brief The ft_search_char() function searches for the first occurrence of the
 * character c in the string s.
 * 
 * @param s 
 * @param c 
 * @return true 
 * @return false 
 */
int					ft_search_char(const char *s, char c);

/**
 * @brief The ft_split() function allocates (with malloc(3)) and returns an
 * array of strings obtained by splitting 's' using the character 'c' as a
 * delimiter. The array must be ended by a NULL pointer.
 * 
 * @param s 
 * @param c 
 * @return char** 
 */
char				**ft_split(char const *s, char c);

/**
 * @brief The ft_striteri() function applies the function f to each character of
 * the string passed as argument, and passing its index as first argument. Each
 * character is passed by address to f to be modified if necessary.
 * 
 * @param s 
 * @param f 
 */
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

/**
 * @brief The ft_strjoin() function allocates (with malloc(3)) and returns a
 * new string, which is the result of the concatenation of 's1' and 's2'.
 * 
 * @param s1 
 * @param s2 
 * @return char* 
 */
char				*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief The ft_strmapi() function applies the function f to each character of
 * the string passed as argument to create a new string (with malloc(3))
 * resulting from successive applications of f.
 * 
 * @param s 
 * @param f 
 * @return char* 
 */
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief ft_strtrim() function allocates (with malloc(3)) and returns a copy of
 * 's1' with the characters specified in 'set' removed from the beginning and
 * the end of the string.
 * 
 * @param s1 
 * @param set 
 * @return char* 
 */
char				*ft_strtrim(char const *s1, char const *set);

/**
 * @brief The ft_substr() function allocates (with malloc(3)) and returns a
 * substring from the string 's'. The substring begins at index 'start' and is
 * of maximum size 'len'.
 * 
 * @param s 
 * @param start 
 * @param len 
 * @return char* 
 */
char				*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief The ft_free_split() function frees the memory allocated for the
 * array of strings.
 * 
 * @param split 
 */
void				ft_free_split(char **split);

/**
 * @brief The ft_swap() function swaps the values of the two integers a and b.
 * 
 * @param a 
 * @param b 
 */
void				ft_swap(int *a, int *b);

#endif