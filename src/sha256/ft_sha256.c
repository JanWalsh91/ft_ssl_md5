/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 13:28:18 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/10 13:35:00 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha256.h"

void			ft_sha256(t_task *task)
{
	t_sha256_state	*state;
	uint32_t		state_copy[8];

	if ((task->opts | OPTION_X) == task->opts)
	{
		sha256_test_suite();
		return ;
	}
	if (!(state = sha256_init_state()))
		return ;
	if ((task->opts | OPTION_S) == task->opts)
		sha256_from_string(task, state);
	else if ((task->opts | OPTION_STDIN) == task->opts)
		sha256_from_stdin(task, state);
	else if (task->file)
		sha256_from_file(task, state);
	else
		sha256_from_stdin(task, state);
	byte_swap(state_copy, state->state, 4, 8);
	ft_memcpy(state->state, state_copy, 4 * 8);
	task->digest = ft_bytetohex(state->state, 32);
	free(state);
}

t_sha256_state	*sha256_init_state(void)
{
	t_sha256_state	*state;

	if (!(state = (t_sha256_state *)ft_memalloc(sizeof(t_sha256_state))))
		return (NULL);
	state->state[0] = 0x6a09e667;
	state->state[1] = 0xbb67ae85;
	state->state[2] = 0x3c6ef372;
	state->state[3] = 0xa54ff53a;
	state->state[4] = 0x510e527f;
	state->state[5] = 0x9b05688c;
	state->state[6] = 0x1f83d9ab;
	state->state[7] = 0x5be0cd19;
	return (state);
}

void			sha256_from_file(t_task *task, t_sha256_state *state)
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
	while ((state->ret = read(fd, &state->buf, SHA256_BUFFER_SIZE))
		== SHA256_BUFFER_SIZE)
		sha256_update_state(state);
	if (state->ret == -1)
	{
		ft_strcat(task->error, task->file);
		ft_strcat(task->error, ": ");
		ft_strcat(task->error, strerror(errno));
		close(fd);
		return ;
	}
	sha256_update_state(sha256_pad(state));
	close(fd);
}

void			sha256_from_string(t_task *task, t_sha256_state *state)
{
	char			*p;
	size_t			copy_length;

	p = task->str;
	if (!*p)
		sha256_update_state(sha256_pad(state));
	while (*p)
	{
		copy_length = ft_strlen(p) >= SHA256_BUFFER_SIZE ? SHA256_BUFFER_SIZE
			: ft_strlen(p);
		ft_memcpy(state->buf, p, copy_length);
		state->ret = copy_length;
		p += copy_length;
		if (state->ret == SHA256_BUFFER_SIZE)
			sha256_update_state(state);
		else
			sha256_update_state(sha256_pad(state));
		ft_bzero(state->buf, 64);
	}
}

void			sha256_from_stdin(t_task *task, t_sha256_state *state)
{
	while ((state->ret = read(0, &state->buf, SHA256_BUFFER_SIZE))
		== SHA256_BUFFER_SIZE)
	{
		if ((task->opts | OPTION_P) == task->opts && state->ret)
			ft_putstr((char *)state->buf);
		sha256_update_state(state);
	}
	if ((task->opts | OPTION_P) == task->opts && state->ret)
		ft_putstr((char *)state->buf);
	sha256_update_state(sha256_pad(state));
}
