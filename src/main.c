/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 13:42:17 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/02 13:03:08 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_core.h"

int	main(int ac, char **av)
{
	t_task		**tasks;
	int			i;

	if (ac <= 1)
	{
		print_usage();
		return (0);
	}
	if (!(tasks = handle_arguments(ac, av)))
		return (0);
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
		free_task(tasks[i]);
	}
	return (0);
}
