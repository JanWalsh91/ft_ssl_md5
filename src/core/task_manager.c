/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 16:49:43 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/02 11:21:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_core.h"
#include "ft_ssl_helper_functions.h"
#include "ft_md5.h"
#include "ft_sha256.h"

t_task		*new_task(t_command cmd, int8_t opts, char *str)
{
	// printf("new_task\n");
	t_task	*task;

	if (!(task = ft_memalloc(sizeof(t_task))))
		return (NULL);
	task->cmd = cmd;
	task->opts = opts;
	if ((task->opts | OPTION_S) == task->opts)
	{
		if (str)
			task->str = str;
		else
			ft_strcat(task->error, "option requires an argument -- s");
	}
	else
		task->file = str;
	if ((task->opts | OPTION_INVALID) == task->opts)
	{
		ft_strcat(task->error, "illegal option -- ");
		ft_strcat(task->error, &str[1]);
	}
	else if ((task->cmd | CMD_INVALID) == task->cmd)
	{
		ft_strcat(task->error, "ft_ssl: Error: '");
		ft_strcat(task->error, str);
		ft_strcat(task->error, "' is an invalid command.\n");
	}	
	// printf("new task: %p\n", task);
	return (task);
}

t_task		**add_task(t_task **tasks, t_task *task)
{
	// printf("add_task\n");
	int	i;

	i = 0;
	while (tasks[i])
		++i;
	// printf("i: %d\n", i);
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
}

void		print_tasks(t_task **tasks)
{
	printf("print tasks\n");
	int	i;

	i = 0;
	while (tasks[i])
	{
		printf("task: %p\n", tasks[i]);
		printf("\ttask: %p\n", tasks[i]);
		printf("\tcommand: %s\n", g_commands[tasks[i]->cmd]);
		printf("\topts: %d\n", tasks[i]->opts);
		printf("\toptions: ");
		int y2 = 1;
		for (int y = 0; y < 4; y++)
		{
			if ((tasks[i]->opts | y2) == tasks[i]->opts)
				printf("%s, ", g_options[y]);
			y2 *= 2;
		}
		printf("\t\n");
		printf("\tstr: [%s]\n", tasks[i]->str);
		printf("\tfile: [%s]\n", tasks[i]->file);
		++i;
	}
}

void		print_task_result(t_task *task)
{
	static const char *const	commands[] = {
		"MD5",
		"SHA256",
		NULL
	};
	
	if ((task->opts | OPTION_Q) != task->opts && 
		(task->opts | OPTION_R) != task->opts)
	{
		ft_putstr(commands[task->cmd]);
		ft_putstr(" (");
		print_task_name(task);
		ft_putstr(") = ");
	}
	ft_putstr(task->digest);
	if ((task->opts | OPTION_Q) != task->opts &&
		(task->opts | OPTION_R) == task->opts)
	{
		ft_putstr(" ");
		print_task_name(task);
	}
	ft_putstr("\n");

}

void		print_task_name(t_task *task)
{
	// printf("print_task_name\n");
	if ((task->opts | OPTION_S) == task->opts)
	{
		ft_putstr("\"");
		ft_putstr(task->str);
		ft_putstr("\"");
	}
	else
		ft_putstr(task->file);
}

void	free_task(t_task *task)
{
	if (!task)
		return ;
	if (task->digest)
		free(task->digest);
	free(task);	
}
