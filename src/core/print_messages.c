/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 12:13:45 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/02 12:23:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_core.h"

void	print_usage()
{
	ft_putstr("usage: ft_ssl command [command opts] [command args]\n");
}

void	print_commands()
{
	ft_putstr("Standard commands:\n");
	ft_putstr("\n");
	ft_putstr("Message Digest commands:\n");
	ft_putstr("md5\n");
	ft_putstr("sha256\n");
	ft_putstr("\n");
	ft_putstr("Cipher commands:\n");
}

int		show_error_message(t_task *task)
{
	ft_putstr(task->error);
	ft_putchar('\n');
	if ((task->cmd | CMD_INVALID) == task->cmd)
		print_commands();
	return (0);	
}
