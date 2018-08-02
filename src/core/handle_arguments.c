/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 14:59:57 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/02 13:05:45 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_core.h"

t_task		**handle_arguments(int ac, char **av)
{
	t_command	command;
	t_task		**tasks;

	if (!(tasks = (t_task**)ft_memalloc(sizeof(t_task**) * (ac + 1))))
		return (NULL);
	if ((command = parse_command(av[1])) == CMD_INVALID)
		return (add_task(tasks, new_task(command, 0, av[1])));
	if (ac <= 2)
		return (add_task(tasks, new_task(command, OPTION_STDIN | OPTION_Q, 0)));
	tasks = handle_options(tasks, command, av);
	return (tasks);
}

t_task		**handle_options(t_task **tasks, t_command command, char **av)
{
	int8_t	options;
	int		i;

	options = 0;
	i = 1;
	while (av[++i])
	{
		options |= parse_option(av[i]);
		if ((options | OPTION_NOT) == options)
			break ;
		if ((options | OPTION_INVALID) == options)
			return (add_task(tasks, new_task(command, options, av[i])));
		if ((options | OPTION_S) == options)
		{
			if (!(av[++i]))
				return (add_task(tasks, new_task(command, options, NULL)));
			tasks = add_task(tasks, new_task(command, options, av[i]));
			options -= OPTION_S;
		}
		if ((options | OPTION_P) == options)
			tasks = handle_p_opt(tasks, command, &options);
	}
	while (av[i])
		tasks = add_task(tasks, new_task(command, options, av[i++]));
	return (tasks);
}

t_task		**handle_p_opt(t_task **tasks, t_command command, int8_t *options)
{
	tasks = add_task(tasks, new_task(command,
		*options | OPTION_STDIN | OPTION_Q, NULL));
	*options -= OPTION_P;
	return (tasks);
}

t_command	parse_command(char *arg)
{
	int	i;

	i = -1;
	while (g_commands[++i])
		if (!ft_strcmp(arg, g_commands[i]))
			return (i);
	return (CMD_INVALID);
}

t_option	parse_option(char *arg)
{
	int			i;
	t_option	opt;

	if (arg[0] != '-')
		return (OPTION_NOT);
	if (arg[0] == '-' && arg[1] == '\0')
		return (OPTION_NOT);
	opt = 1;
	i = -1;
	while (g_options[++i])
	{
		if (!ft_strcmp(arg, g_options[i]))
		{
			if (arg == g_options[1])
				return (OPTION_P);
			return (opt);
		}
		opt *= 2;
	}
	return (OPTION_INVALID);
}
