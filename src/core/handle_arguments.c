/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 14:59:57 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/26 13:04:29 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_core.h"
#include "ft_ssl_helper_functions.h"

t_task		**handle_arguments(int ac, char **av)
{
	printf("handle_arguments\n");
	int8_t		options;
	int			i;
	t_command	command;
	t_task		**tasks;

	options = 0;
	// get command
	if ((command = parse_command(av[1])) == CMD_INVALID)
	{
		printf("invalid command\n");
		return (NULL);
	}
	printf("command: %d\n", command);
	if (ac <= 2)
	{
		read_from_stdin();	
		return (NULL);
	}
	if (!(tasks = (t_task**)ft_memalloc(sizeof(t_task**) * (ac + 1))))
		return (NULL);
	
	i = 1;
	// parse options
	while (++i < ac)
	{
		// TODO: handle illegal options (is arg starts with '-')
		options |= parse_option(av[i]);
		if ((options | OPTION_NOT) == options)
			break ;
		if ((options | OPTION_INVALID) == options)
		{
			printf("illegal option\n");
			// stop execution, print error
			return (NULL);
		}
		if ((options | OPTION_S) == options)
		{
			// handle -s option
			// TODO: create task with string
			if (++i < ac)
				tasks = add_task(tasks, new_task(command, options, av[i]));
			else
			{
				printf("error must provide string after -s option\n");
				return (NULL);
			}
			options -= OPTION_S;
		}
	}
	printf("final options: %d\n", options);
	printf("current arg: %s\n", av[i]);
	while (i < ac)
		tasks = add_task(tasks, new_task(command, options, av[i++]));
	printf("task[0]: %p\n", tasks[0]);
	return (tasks);
}

t_command	parse_command(char *arg)
{
	printf("parse_command\n");
	int							i;
	t_command					cmd;
	static const char *const	commands[] = {
		"md5",
		"sha256"
	};

	cmd = 0;
	i = -1;
	while (++i < 2)
	{
		if (!ft_strcmp(arg, commands[i]))
			return (i);
		cmd++;
	}
	return (CMD_INVALID);
}

t_option	parse_option(char *arg)
{
	printf("parse_option\n");
	int							i;
	t_option					opt;
	static const char *const	options[] = {
		"-s",
		"-p",
		"-q",
		"-r"
	};

	if (arg[0] != '-')
		return (OPTION_NOT);
	opt = 1;
	i = -1;
	while (++i < 4)
	{
		if (!ft_strcmp(arg, options[i]))
			return (opt);
		opt *= 2;
	}
	return (OPTION_INVALID);
}
