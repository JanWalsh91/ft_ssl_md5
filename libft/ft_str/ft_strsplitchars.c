/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:16:41 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/10 13:00:57 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates and returns an array of null-terminated strings which are the
** result of the separation of the input string s by the char c.
** If memory allocation fails, return NULL.
*/

#include "ft_ssl_helper_functions.h"

static size_t	get_word_count(char *s, char const *chars)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s || s[i] == '\0')
		return (0);
	if (!ft_strchr(chars, s[i++]))
		count++;
	while (s[i])
	{
		if (!ft_strchr(chars, s[i]) && ft_strchr(chars, s[i - 1]))
			count++;
		i++;
	}
	return (count);
}

char			**ft_strsplit(char const *s, char const *chars)
{
	size_t	word_count;
	size_t	i;
	size_t	j;
	char	**result;

	if (!s || !chars)
		return (NULL);
	word_count = get_word_count((char*)s, chars);
	if (!(result = (char **)ft_memalloc(sizeof(char *) * (word_count + 1))))
		return (NULL);
	result[word_count] = NULL;
	j = 0;
	while (s && word_count)
	{
		i = 0;
		while (*s && ft_strchr(chars, *s))
			s++;
		while (*s && !ft_strchr(chars, *s) && ++i)
			s++;
		if (!(result[j++] = ft_strsub(s - i, 0, i)))
			return (NULL);
		word_count--;
	}
	return (result);
}
