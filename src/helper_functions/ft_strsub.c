/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 13:56:03 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/09 11:43:27 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates and returns a copy of a substring of the string s starting at
** index start of length len.
** If allocation fails, return NULL.
** If start and len do not designate a valid substring, behavior is undefined.
*/

#include "ft_ssl_helper_functions.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	j;

	j = 0;
	i = start;
	if (!len)
		return (ft_memalloc(1));
	if (!s || !(*s))
		return (NULL);
	if (!(sub = ft_strnew(len)))
		return (NULL);
	while (j < len)
		sub[j++] = s[i++];
	sub[j] = '\0';
	return (sub);
}
