/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_task_result.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 16:49:43 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/10 14:29:59 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_core.h"

void		print_task_result(t_task *task, char *verify)
{
	static char	commands[10][64];

	init_task_result_names(commands);
	if ((task->opts | OPTION_Q) != task->opts
		&& (task->opts | OPTION_R) != task->opts)
	{
		ft_putstr(commands[task->cmd]);
		ft_putstr(" (");
		print_task_name(task);
		ft_putstr(") = ");
	}
	ft_putstr(task->digest);
	if ((task->opts | OPTION_Q) != task->opts
		&& (task->opts | OPTION_R) == task->opts)
	{
		ft_putstr(" ");
		print_task_name(task);
	}
	if (verify)
		verify_task_result(task, verify);
	ft_putstr("\n");
}

void		print_task_name(t_task *task)
{
	if ((task->opts | OPTION_S) == task->opts)
	{
		ft_putstr("\"");
		ft_putstr(task->str);
		ft_putstr("\"");
	}
	else
		ft_putstr(task->file);
}

void		init_task_result_names(char commands[10][64])
{
	static int	i = -1;

	if (i == -1)
	{
		while (g_commands[++i])
		{
			ft_strcpy(commands[i], g_commands[i]);
			ft_strtoupper(commands[i]);
		}
	}
}

void		verify_task_result(t_task *task, char *verify)
{
	if (!ft_strcmp(task->digest, verify))
		ft_putstr(" - verified correct");
	else
		ft_putstr(" - verified incorrect");
}
