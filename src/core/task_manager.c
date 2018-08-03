/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 16:49:43 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/03 11:31:37 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_core.h"

t_task		*new_task(t_command cmd, int8_t opts, char *str)
{
	t_task	*task;

	if (!(task = ft_memalloc(sizeof(t_task))))
		return (NULL);
	task->cmd = cmd;
	task->opts = opts;
	if (invalid_cmd_opt(task, str))
		return (task);
	if ((task->opts | OPTION_S) == task->opts)
	{
		if (str)
			task->str = str;
		else
		{
			ft_strcat(task->error, "option requires an argument -- s");
			return (task);
		}
	}
	else
		task->file = str;
	return (task);
}

int			invalid_cmd_opt(t_task *task, char *str)
{
	if ((task->opts | OPTION_INVALID) == task->opts)
	{
		ft_strcat(task->error, "illegal option -- ");
		ft_strcat(task->error, &str[1]);
		return (1);
	}
	else if ((task->cmd | CMD_INVALID) == task->cmd)
	{
		ft_strcat(task->error, "ft_ssl: Error: '");
		ft_strcat(task->error, str);
		ft_strcat(task->error, "' is an invalid command.\n");
		return (1);
	}
	return (0);
}

t_task		**add_task(t_task **tasks, t_task *task)
{
	int	i;

	i = 0;
	while (tasks[i])
		++i;
	tasks[i] = task;
	return (tasks);
}

void		free_task(t_task *task)
{
	if (!task)
		return ;
	if (task->digest)
		free(task->digest);
	free(task);
}
