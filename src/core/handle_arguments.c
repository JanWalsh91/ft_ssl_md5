/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 14:59:57 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/02 12:24:16 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_core.h"

t_task		**handle_arguments(int ac, char **av)
{
	// printf("handle_arguments\n");
	int8_t		options;
	int			i;
	t_command	command;
	t_task		**tasks;

	options = 0;
	if (!(tasks = (t_task**)ft_memalloc(sizeof(t_task**) * (ac + 1))))
		return (NULL);
	if ((command = parse_command(av[1])) == CMD_INVALID)
		return (add_task(tasks, new_task(command, options, av[1])));
	if (ac <= 2)
	{
		options |= (OPTION_STDIN | OPTION_Q);
		return (add_task(tasks, new_task(command, options, NULL)));
	}
	
	i = 1;
	while (++i < ac)
	{
		options |= parse_option(av[i]);
		if ((options | OPTION_NOT) == options)
			break ;
		if ((options | OPTION_INVALID) == options)
			return (add_task(tasks, new_task(command, options, av[i])));
		if ((options | OPTION_S) == options)
		{
			if (++i < ac)
				tasks = add_task(tasks, new_task(command, options, av[i]));
			else
				return (add_task(tasks, new_task(command, options, NULL)));
			options -= OPTION_S;
		}
		if ((options | OPTION_P) == options)
		{
			tasks = add_task(tasks, new_task(command, options | OPTION_STDIN | OPTION_Q, NULL));
			options -= OPTION_P;
		}
			
	}
	// printf("final options: %d\n", options);
	// printf("current arg: %s\n", av[i]);
	while (i < ac)
		tasks = add_task(tasks, new_task(command, options, av[i++]));
	// printf("task[0]: %p\n", tasks[0]);
	return (tasks);
}

t_command	parse_command(char *arg)
{
	int							i;

	i = -1;
	while (g_commands[++i])
		if (!ft_strcmp(arg, g_commands[i]))
			return (i);
	return (CMD_INVALID);
}

t_option	parse_option(char *arg)
{
	printf("parse option\n");
	int							i;
	t_option					opt;

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
