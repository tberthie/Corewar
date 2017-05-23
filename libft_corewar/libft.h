/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tberthie <tberthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 19:51:42 by tberthie          #+#    #+#             */
/*   Updated: 2017/05/20 13:52:52 by tberthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>

int				ft_atoi(const char *str);
int				ft_atoip(char **str);
char			*ft_itoa(int n);
char			*ft_itoabase(int n, unsigned int b);
char			*ft_utoabase(unsigned int n, unsigned int b);
unsigned int	ft_abs(int nb);

unsigned char	ft_freeret(void *ptr, unsigned char ret);
void			*ft_freeswap(void **ptr, void *swap);
void			*ft_memalloc(unsigned int size);
void			ft_memcpy(void *dest, const void *src, unsigned int byte_nb);
void			*ft_m(unsigned int byte_nb);
void			ft_ptrswap(void **p1, void **p2);
void			ft_free(void *ptr);
void			ft_memset(void *mem, unsigned int size, char c);

char			*ft_gnl(int fd);
char			*ft_rfc(char *file);
char			**ft_gdc(char *path);

unsigned char	ft_isdir(char *path);

void			ft_putchar(char c);
void			ft_putnchar(char c, unsigned int nb);
void			ft_putnbr(int nb);
void			ft_putstr(const char *str);

char			*ft_strchr(char *str, char c);
char			*ft_strrchr(char *str, char c);
char			*ft_strstr(char *str, char *needle);
char			ft_strcmp(const char *s1, const char *s2);
char			ft_strncmp(const char *s1, const char *s2, unsigned int n);
unsigned int	ft_stricmp(const char *s1, const char *s2);
void			ft_strcpy(char *dest, const char *src);
char			*ft_strdup(const char *str);
char			*ft_strndup(const char *str, int size);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strcjoin(const char *s1, const char *s2, char c);
char			*ft_strsjoin(const char *s1, const char *s2, const char *in);
unsigned int	ft_strlen(const char *str);
char			*ft_strfrmchr(char c, unsigned int n);
char			**ft_strsplit(char *s, char c);
unsigned int	ft_strcount(const char *s, char c);

char			*ft_strnew(void);
void			ft_strpush(char **str, char c);
void			ft_strspush(char **str, char *push);
void			ft_strins(char **str, char c, unsigned int i);
void			ft_strsins(char **str, char *ins, unsigned int i);
void			ft_strrem(char *str);

char			**ft_strarrdup(char **array);
int				ft_strarrstr(char **array, char *str);
int				ft_strarrstrn(char **array, char *str, unsigned int n);
char			*ft_strarrstrstrr(char **array, char *str);
void			ft_strarrrem(char **array);
unsigned int	ft_strarrstrlen(char **array);

void			**ft_parrnew(void);
void			ft_parrfree(void **tab);
void			ft_parrelmfree(void **tab);
void			ft_parrpush(void ***tab, void *elem);
void			ft_parrrem(void **tab);
void			ft_parrprem(void **tab, void *elem);
unsigned int	ft_parrlen(void **array);
void			**ft_parrdup(void **array);
void			**ft_parrndup(void **array, unsigned int n);
void			**ft_parrjoin(void **a1, void **a2);

int				ft_intlen(int nb);

void			ft_print(int fd, char *s, ...);
int				ft_printf(const char *s, ...);

#endif
