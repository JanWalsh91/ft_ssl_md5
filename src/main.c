/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 13:42:17 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/31 16:34:25 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_core.h"
#include "ft_ssl_helper_functions.h"

int		show_error_message(t_task *task);

int	main(int ac, char **av)
{
	t_task		**tasks;
	int			i;

	// errno = 500;
	// printf("sizeof(errno): %lu\n", sizeof(errno));
	if (ac <= 1)
	{
		print_usage();
		return (0);
	}
	tasks = handle_arguments(ac, av);
	if (!tasks)
	{
		printf("no tasks found\n");
		return (0);
	}
	// print_tasks(tasks);
	i = -1;
	while (tasks[++i])
	{
		if (tasks[i]->error[0])
			return (show_error_message(tasks[i]));
		execute_task(tasks[i]);
		if (tasks[i]->error[0])
			show_error_message(tasks[i]);
		else
			print_task_result(tasks[i]);
	}
	return (0);
}

int		show_error_message(t_task *task)
{
	ft_putstr(task->error);
	ft_putchar('\n');
	return (0);	
}
