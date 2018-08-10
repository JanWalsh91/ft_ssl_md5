/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 13:42:17 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/10 12:45:21 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_core.h"
#include "ft_md5.h"
#include "ft_sha256.h"
#include "ft_sha512.h"

int		main(int ac, char **av)
{
	if (ac <= 1)
		read_stdin();
	else
		parse_input(--ac, ++av);
	return (0);
}

/*
** Interprets arguments, converts them to tasks, and executes them.
*/

void	parse_input(int ac, char **av)
{
	t_task	**tasks;
	int		i;

	if (!(tasks = handle_arguments(ac, av)))
		return ;
	handle_tasks(tasks);
	i = -1;
	while (tasks[++i])
		free_task(tasks[i]);
	free(tasks);
}

/*
** Executes tasks, handles errors, and displays results
*/

int		handle_tasks(t_task **tasks)
{
	int	i;

	i = -1;
	while (tasks[++i])
	{
		if (tasks[i]->error[0])
			return (show_error_message(tasks[i]));
		execute_task(tasks[i]);
		if (((tasks[i]->opts | OPTION_X) == tasks[i]->opts))
			continue ;
		if (tasks[i]->error[0])
			show_error_message(tasks[i]);
		else
			print_task_result(tasks[i], NULL);
	}
	return (0);
}

void	execute_task(t_task *task)
{
	static const t_task_executor	task_f[3] = {
		&ft_md5,
		&ft_sha256,
		&ft_sha512
	};

	task_f[task->cmd](task);
}
