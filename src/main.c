/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 13:42:17 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/26 14:46:39 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_core.h"
#include "ft_ssl_helper_functions.h"

int	main(int ac, char **av)
{
	t_task		**tasks;
	int			i;

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
	print_tasks(tasks);
	i = 0;
	while (tasks[i])
		execute_task(tasks[i++]);
	return (0);
}
