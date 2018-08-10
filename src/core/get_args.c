/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 12:44:52 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/10 14:28:57 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_core.h"

/*
** Adds 'word' to the string array 'args'
*/

static void	add_word(t_arg_list *args, char *word)
{
	char	**new_args;

	if (!args->args)
	{
		if (!(args->args = (char **)ft_memalloc(sizeof(char *) * 2)))
			return ;
		args->size = 1;
		args->args[0] = word;
		return ;
	}
	if (!(new_args = (char **)ft_memalloc(sizeof(char *) * (args->size + 2))))
		return ;
	ft_memcpy(new_args, args->args, sizeof(char *) * (args->size + 1));
	free(args->args);
	args->args = new_args;
	new_args[args->size] = word;
	++args->size;
}

/*
** Extracts a word from the buffer
*/

static char	*get_word(char *buf, int *i)
{
	size_t	size;
	char	*new_word;

	size = 0;
	while (buf[*i + size] && !ft_strchr(" \t\v\n", buf[*i + size]))
		++size;
	new_word = ft_strsub(buf, *i, size);
	*i += size;
	return (new_word);
}

/*
** Extracts a contents of quote from the buffer
*/

static char	*get_quote(char *buf, int *i)
{
	char	quote;
	size_t	size;
	char	*new_word;

	size = 0;
	quote = buf[*i];
	++*i;
	while (buf[*i + size] && buf[*i + size] != quote)
		++size;
	new_word = ft_strsub(buf, *i, size);
	*i += size;
	if (buf[*i] == quote)
		++*i;
	return (new_word);
}

/*
** Converts a string to string array taking quotes into account
*/

char		**get_args(char *buf, int *ac)
{
	t_arg_list	args;
	int			i;

	ft_bzero(&args, sizeof(args));
	i = -1;
	while (buf[++i])
	{
		if (ft_strchr(" \t\v\n", buf[i]))
			continue;
		if (!ft_strchr("'\" \t\v\n", buf[i])
			&& (i == 0 || (i > 0 && ft_strchr(" \t\v\n", buf[i - 1]))))
			add_word(&args, get_word(buf, &i));
		if (ft_strchr("'\"", buf[i])
			&& (i == 0 || (i > 0 && ft_strchr(" \t\v\n", buf[i - 1]))))
			add_word(&args, get_quote(buf, &i));
	}
	*ac = args.size;
	return (args.args);
}
