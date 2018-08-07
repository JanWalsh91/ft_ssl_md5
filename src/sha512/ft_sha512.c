/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha512.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 13:28:18 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/07 09:45:37 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha512.h"

void			ft_sha512(t_task *task)
{
	t_sha512_state	*state;
	uint64_t		state_copy[8];

	if ((task->opts | OPTION_X) == task->opts)
	{
		sha512_test_suite();
		return ;
	}
	if (!(state = sha512_init_state()))
		return ;
	if ((task->opts | OPTION_S) == task->opts)
		sha512_from_string(task, state);
	else if ((task->opts | OPTION_STDIN) == task->opts)
		sha512_from_stdin(task, state);
	else if (task->file)
		sha512_from_file(task, state);
	else
		sha512_from_stdin(task, state);
	byte_swap(state_copy, state->state, 8, 8);
	ft_memcpy(state->state, state_copy, 8 * 8);
	task->digest = ft_bytetohex(state->state, 64);
	free(state);
}

t_sha512_state	*sha512_init_state(void)
{
	t_sha512_state	*state;

	if (!(state = (t_sha512_state *)ft_memalloc(sizeof(t_sha512_state))))
		return (NULL);
	state->state[0] = 0x6a09e667f3bcc908;
	state->state[1] = 0xbb67ae8584caa73b;
	state->state[2] = 0x3c6ef372fe94f82b;
	state->state[3] = 0xa54ff53a5f1d36f1;
	state->state[4] = 0x510e527fade682d1;
	state->state[5] = 0x9b05688c2b3e6c1f;
	state->state[6] = 0x1f83d9abfb41bd6b;
	state->state[7] = 0x5be0cd19137e2179;
	return (state);
}

void			sha512_from_file(t_task *task, t_sha512_state *state)
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
	while ((state->ret = read(fd, &state->buf, SHA512_BUFFER_SIZE)) == SHA512_BUFFER_SIZE)
		sha512_update_state(state);
	if (state->ret == -1)
	{
		ft_strcat(task->error, task->file);
		ft_strcat(task->error, ": ");
		ft_strcat(task->error, strerror(errno));
		close(fd);
		return ;
	}
	sha512_update_state(sha512_pad(state));
	close(fd);
}

void			sha512_from_string(t_task *task, t_sha512_state *state)
{
	char			*p;
	size_t			copy_length;

	p = task->str;
	if (!*p)
		sha512_update_state(sha512_pad(state));
	while (*p)
	{
		copy_length = ft_strlen(p) >= SHA512_BUFFER_SIZE ? SHA512_BUFFER_SIZE : ft_strlen(p);
		ft_memcpy(state->buf, p, copy_length);
		state->ret = copy_length;
		p += copy_length;
		if (state->ret == SHA512_BUFFER_SIZE)
			sha512_update_state(state);
		else
			sha512_update_state(sha512_pad(state));
		ft_bzero(state->buf, 64);
	}
}

void			sha512_from_stdin(t_task *task, t_sha512_state *state)
{
	while ((state->ret = read(0, &state->buf, SHA512_BUFFER_SIZE)) == SHA512_BUFFER_SIZE)
	{
		if ((task->opts | OPTION_P) == task->opts && state->ret)
			ft_putstr((char *)state->buf);
		sha512_update_state(state);
	}
	if ((task->opts | OPTION_P) == task->opts && state->ret)
		ft_putstr((char *)state->buf);
	sha512_update_state(sha512_pad(state));
}
