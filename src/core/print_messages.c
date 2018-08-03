/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 12:13:45 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/03 11:32:01 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_core.h"

void	print_usage(void)
{
	ft_putstr("usage: ft_ssl [md5, sha256] [-pqr] [-s string] [files ...]\n");
}

void	print_commands(void)
{
	int	i;

	ft_putstr("Standard commands:\n");
	ft_putstr("\n");
	ft_putstr("Message Digest commands:\n");
	i = -1;
	while (g_commands[++i])
	{
		ft_putstr(g_commands[i]);
		ft_putstr("\n");
	}
	ft_putstr("\n");
	ft_putstr("Cipher commands:\n");
}

int		show_error_message(t_task *task)
{
	ft_putstr(task->error);
	ft_putchar('\n');
	if ((task->cmd | CMD_INVALID) == task->cmd)
		print_commands();
	if ((task->opts | OPTION_INVALID) == task->opts)
		print_usage();
	return (0);
}
