/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 13:42:17 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/02 13:22:30 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_core.h"
#include "ft_md5.h"
#include "ft_sha256.h"

int	main(int ac, char **av)
{
	t_task							**tasks;
	int								i;
	static const t_task_executor	task_f[2] = {&ft_md5, &ft_sha256};

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
		task_f[tasks[i]->cmd](tasks[i]);
		if (tasks[i]->error[0])
			show_error_message(tasks[i]);
		else
			print_task_result(tasks[i]);
		free_task(tasks[i]);
	}
	return (0);
}
