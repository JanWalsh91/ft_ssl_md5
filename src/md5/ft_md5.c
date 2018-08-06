/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:46:57 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/06 16:54:59 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"

void			ft_md5(t_task *task)
{
	// printf("ft_md5\n");
	t_md5_state *state;

	if ((task->opts | OPTION_X) == task->opts)
	{
		md5_test_suite();
		return ;
	}
	if (!(state = md5_init_state()))
		return ;
	if ((task->opts | OPTION_S) == task->opts)
		md5_from_string(task, state);
	else if ((task->opts | OPTION_STDIN) == task->opts)
		md5_from_stdin(task, state);
	else if (task->file)
		md5_from_file(task, state);
	else
		md5_from_stdin(task, state);
	task->digest = ft_bytetohex(state->state, 16);
	free(state);
}

void			md5_from_file(t_task *task, t_md5_state *state)
{
	int			fd;

	fd = open(task->file, O_RDONLY);
	if (fd == -1)
	{
		ft_strcat(task->error, task->file);
		ft_strcat(task->error, ": ");
		ft_strcat(task->error, strerror(errno));
		return ;
	}
	while ((state->ret = read(fd, &state->buf, BUFFER_SIZE)) == BUFFER_SIZE)
		md5_update_state(state);
	if (state->ret == -1)
	{
		ft_strcat(task->error, task->file);
		ft_strcat(task->error, ": ");
		ft_strcat(task->error, strerror(errno));
		close(fd);
		return ;
	}
	md5_update_state(md5_pad(state));
	close(fd);
}

void			md5_from_string(t_task *task, t_md5_state *state)
{
	char			*p;
	size_t			copy_length;

	p = task->str;
	if (!*p)
		md5_update_state(md5_pad(state));
	while (*p)
	{
		copy_length = ft_strlen(p) >= BUFFER_SIZE ? BUFFER_SIZE : ft_strlen(p);
		ft_memcpy(state->buf, p, copy_length);
		state->ret = copy_length;
		p += copy_length;
		if (state->ret == BUFFER_SIZE)
			md5_update_state(state);
		else
			md5_update_state(md5_pad(state));
		ft_bzero(state->buf, 64);
	}
}

void			md5_from_stdin(t_task *task, t_md5_state *state)
{
	while ((state->ret = read(0, &state->buf, BUFFER_SIZE)) == BUFFER_SIZE)
	{
		if ((task->opts | OPTION_P) == task->opts && state->ret)
			ft_putstr((char *)state->buf);
		md5_update_state(state);
	}
	if ((task->opts | OPTION_P) == task->opts && state->ret)
		ft_putstr((char *)state->buf);
	md5_update_state(md5_pad(state));
	(void)task;
}

t_md5_state		*md5_init_state(void)
{
	t_md5_state *state;

	if (!(state = (t_md5_state *)ft_memalloc(sizeof(t_md5_state))))
		return (NULL);
	state->state[0] = 0x67452301;
	state->state[1] = 0xefcdab89;
	state->state[2] = 0x98badcfe;
	state->state[3] = 0x10325476;
	return (state);
}
