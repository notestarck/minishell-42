/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reclaire <reclaire@student.42mulhouse.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:07:15 by reclaire          #+#    #+#             */
/*   Updated: 2022/05/18 15:11:15 by reclaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_lstremove(t_list **lst, t_list *elem, void (*del)(void *));

char	*ft_strcat(char *dest, char *src);

//Compares two strings
int		ft_strcmp(char *s1, char *s2);

//Append a at the end of b
char	*ft_str_appnd(char *a, char *b, int free_a, int free_b);

//Returns true if number is between the specified range. (Inclusive)
int		ft_isrange(int i, int min, int max);

//Malloc, but protected
void	*ft_malloc(size_t size);

//Returns the absolute value of n
int		ft_abs(int n);

//Returns the absolute value of n
float	ft_fabs(float n);

int		ft_wrap(int min, int max, int n);

void	ft_lstremoveif(t_list **lst, void (*del)(void *),
			int (*f)(), void *ref);

//Check if character is digit or alpha.
int		ft_isalnum(int c);

//Check if character is alpha.
int		ft_isalpha(int c);

//Check if character is ascii.
int		ft_isascii(int c);

//Returns the smallest between a and b.
int		ft_min(int a, int b);

//Returns the smallest between a and b.
float	ft_fmin(float a, float b);

//Returns the largest between a and b.
int		ft_max(int a, int b);

//Returns the largest between a and b.
float	ft_fmax(float a, float b);

//Check if character is digit.
int		ft_isdigit(int c);

//Check if str is digit.
int		ft_str_isdigit(char *str);

//Check if character is printable.
int		ft_isprint(int c);

//Converts a string to a number.
int		ft_atoi(const char *str);

//Writes n zeroed bytes to the string s.
void	ft_bzero(void *s, size_t n);

//Allocate memory of size count * size and set all values to NULL.
void	*ft_calloc(size_t count, size_t size);

//Locates the first occurrence of c in string s.
void	*ft_memchr(const void *s, int c, size_t n);

//Compares byte string s1 against byte string s2.
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/*
Copies n bytes from memory area src to memory area dst. 
The two strings may not overlap. If they do use ft_memmove instead.
*/
void	*ft_memcpy(void *dst, const void *src, size_t n);

/*
Copies len bytes from string src to string dst. The two strings may overlap; 
the copy is always done in a non-destructive manner.
*/
void	*ft_memmove(void *dst, const void *src, size_t len);

//Writes len bytes of value c.
void	*ft_memset(void *b, int c, size_t len);

/*
Locates the first occurrence of c in the string pointed to by s.
The terminating null character taken into account.
*/
char	*ft_strchr(const char *s, int c);

//Duplicates the string s1 into a new char array
char	*ft_strdup(const char *s1);

/*
Appends string src to the end of dst.  
It will append at most dstsize - strlen(dst) - 1 characters. 
It will then NUL-terminate the new string
*/
size_t	ft_strlcat(char *dest, char *src, size_t size);

/*
Copies up to dstsize - 1 characters from the string src to dst, 
NUL-terminating the result if dstsize is not 0.
*/
size_t	ft_strlcpy(char *dest, char *src, size_t size);

//Returns the length of string s
size_t	ft_strlen(const char *s);

//Compares string s1 against string s2.
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/*
Locates the first occurrence of the null-terminated string needle in the 
string haystack, where not more than len characters are searched.
If to_find is an empty string, str is returned; if to_find occurs 
nowhere in str, NULL is returned; otherwise a pointer to the first
character of the first occurrence of to_find is returned.
*/
char	*ft_strnstr(const char *str, const char *to_find, size_t len);

//Locates the last occurrence of c in string s
char	*ft_strrchr(const char *s, int c);

//Converts a lower-case letter to the corresponding upper-case letter.
int		ft_tolower(int c);

//Converts a upper-case letter to the corresponding lower-case letter.
int		ft_toupper(int c);

//Returns a new string from s, starting at index start with size len.
char	*ft_substr(char const *s, unsigned int start, size_t len);

//Concatenate s1 and s2
char	*ft_strjoin(char const *s1, char const *s2);

//Creates a copy of s1 wihout the characters in set at end and start of string.
char	*ft_strtrim(char const *s1, char const *set);

//Splits string s by separator c.
char	**ft_split(char const *s, char c);

//Converts an int to an string.
char	*ft_itoa(int n);

/*
Applies function f to each characters in string s, and returns
a new string of all the results of f.
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

//Applies function f to each characters in string s.
void	ft_striteri(char *s, void (*f)(unsigned int, char *));

//Writes character c in file descriptor fd.
void	ft_putchar_fd(char c, int fd);

//Write string s in file descriptor fd.
void	ft_putstr_fd(char *s, int fd);

//Write s in file fd, and append a line end.
void	ft_putendl_fd(char *s, int fd);

//Write a number in file descriptor fd.
void	ft_putnbr_fd(int n, int fd);

//Read the next line in fd, NULL if all lines are read.
char	*ft_gnl(int fd);

//Returns the index of the first occurrence of c in str, -1 if not found.
int		ft_getindex(char *str, char c);

//Returns the magnitude of n.
size_t	ft_magnitude(long n);

//Check if a number is prime.
int		ft_is_prime(int nb);

//Raises nb to power
int		ft_pow(int nb, int power);

//Creates an array of int from min to max.
int		*ft_range(int min, int max);

//Creates an array of int from min to max and returns the size of the array.
int		ft_nrange(int **range, int min, int max);

//Itoa for unsigned int
char	*ft_uitoa(unsigned int n);

//Printf...
int		ft_printf(const char *str, ...);

//Creates a new list element using content
t_list	*ft_lstnew(void *content);

//Adds new at the front of lst.
void	ft_lstadd_front(t_list **lst, t_list *new);

//Returns the size of lst.
int		ft_lstsize(t_list *lst);

//Returns the last element of lst.
t_list	*ft_lstlast(t_list *lst);

//Adds new at the end of lst.
void	ft_lstadd_back(t_list **lst, t_list *new);

//Deletes an element from lst, using del on it's content.
void	ft_lstdelone(t_list *lst, void (*del)(void *));

//Iterates through lst, deleting every element (see ft_lstdelone).
void	ft_lstclear(t_list **lst, void (*del)(void *));

//Iterates through lst, using f on each element's content.
void	ft_lstiter(t_list *lst, void (*f)(void *));

/*
Iterates through "lst", applies "f" on every
element's content, puts results in a new list and returns it.
"del" is used if anything goes wrong.
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

#endif