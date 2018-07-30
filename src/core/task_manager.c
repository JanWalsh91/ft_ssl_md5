/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 16:49:43 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/30 13:29:54 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_core.h"
#include "ft_ssl_helper_functions.h"
#include "ft_md5.h"
#include "ft_sha256.h"

t_task		*new_task(t_command cmd, int8_t opts, char *str)
{
	printf("new_task\n");
	t_task	*task;

	if (!(task = ft_memalloc(sizeof(t_task))))
		return (NULL);
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
	printf("new task: %p\n", task);
	return (task);
}

t_task		**add_task(t_task **tasks, t_task *task)
{
	printf("add_task\n");
	int	i;

	i = 0;
	while (tasks[i])
		++i;
	printf("i: %d\n", i);
	tasks[i] = task;
	return (tasks);	
}

void		execute_task(t_task *task)
{
	typedef	void(*task_executor)(t_task *);
	static const task_executor tasks[2] = {
		&ft_md5,
		&ft_sha256
	};

	tasks[task->cmd](task);

	// ft_md5(task);
	(void)tasks;
	(void)task;
	// iterate over command, call on list of function pointer?
}

void		print_tasks(t_task **tasks)
{
	printf("print tasks\n");
	int	i;
	static const char *const	commands[] = {
		"md5",
		"sha256",
		"invalid"
	};
	static const char *const	options[] = {
		"-s",
		"-p",
		"-q",
		"-r"
	};
	
	i = 0;
	while (tasks[i])
	{
		printf("task: %p\n", tasks[i]);
		printf("\ttask: %p\n", tasks[i]);
		printf("\tcommand: %s\n", commands[tasks[i]->cmd]);
		printf("\topts: %d\n", tasks[i]->opts);
		printf("\toptions: ");
		int y2 = 1;
		for (int y = 0; y < 4; y++)
		{
			if ((tasks[i]->opts | y2) == tasks[i]->opts)
				printf("%s, ", options[y]);
			y2 *= 2;
		}
		printf("\t\n");
		printf("\tstr: [%s]\n", tasks[i]->str);
		printf("\tfile: [%s]\n", tasks[i]->file);
		++i;
	}
}
