/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_helper_functions.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 15:41:00 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/09 15:31:11 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_HELPER_FUNCTIONS_H
# define FT_SSL_HELPER_FUNCTIONS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

char	*ft_bytetohex(void *addr, size_t len);
void	ft_bzero(void *s, size_t n);
int		ft_islower(int c);
void	*ft_memalloc(size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putchar(char c);
void	ft_putnbr(int nb);
void	ft_putstr(char const *s);
char	*ft_strcat(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dst, const char *src);
char	*ft_strnew(size_t size);
size_t	ft_strlen(const char *s);
char	**ft_strsplit(char const *s, char const *chars);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
void	ft_strtoupper(char *s);
int		ft_toupper(int c);

void	hex_dump(char *desc, void *addr, int len);

#endif
