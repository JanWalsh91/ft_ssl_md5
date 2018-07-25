/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 16:49:43 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/25 17:01:37 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_core.h"

t_task		*new_task(t_command cmd, int8_t opts, char *str)
{
	t_task	*task;

	if (!(task = malloc(sizeof(t_task))))
		exit(0);
	
	task->cmd = cmd;
	task->opts = opts;
	if ((task->opts | OPTION_S) == task->opts)
	{
		task->str = str;
		task->file = NULL;
	}
	else
	{
		task->str = NULL;
		task->file = str;
	}
	return (task);
}
