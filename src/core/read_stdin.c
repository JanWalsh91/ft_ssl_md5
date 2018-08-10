/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_stdin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 12:44:52 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/10 13:03:58 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_core.h"

/*
** Reads user input from stdin. Converts string to arg list.
** Interprets args list.
*/

void		read_stdin(void)
{
	char	**input;
	int		ac;
	int		y;

	print_usage();
	while (1)
	{
		input = get_user_input(&ac);
		if (ac && !ft_strcmp(input[0], "exit"))
			break ;
		if (ac)
		{
			parse_input(ac, input);
			y = -1;
			while (++y < ac)
				free(input[y]);
		}
		ft_bzero(input, sizeof(*input) * ac);
		free(input);
	}
}

char		**get_user_input(int *i)
{
	int		ret;
	char	buf[1024];
	char	**input;

	input = NULL;
	*i = 0;
	ft_bzero(buf, 1024);
	if ((ret = read(0, &buf, 1024)) < 1024)
	{
		buf[ret - 1] = '\0';
		if (ft_strlen(buf))
			input = get_args(buf, i);
	}
	else
		ft_putstr("input too long\n");
	return (input);
}
