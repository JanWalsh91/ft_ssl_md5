/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:46:57 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/03 11:59:37 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"

void	ft_md5(t_task *task)
{
	t_md5_state *state;

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

void	md5_from_file(t_task *task, t_md5_state *state)
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

void	md5_from_string(t_task *task, t_md5_state *state)
{
	char			*p;
	size_t			copy_length;

	p = task->str;
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

void	md5_from_stdin(t_task *task, t_md5_state *state)
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

void	md5_update_state(t_md5_state *state)
{
	state->length += state->ret;
	md5_transform(state);
	ft_bzero(state->buf, 64 * 2);
}

t_md5_state	*md5_pad(t_md5_state *state)
{
	size_t		tmp;
	uint64_t	length;
	// char		*lp;

	state->length += state->ret;
	state->buf[state->ret] = 0x80;
	if ((state->ret + 1) % 64 < 56)
	{
		tmp = 56 - (state->length % 64);
		ft_memset(&state->buf[state->ret + 1], 0, tmp);
	}
	else
	{
		tmp = 64 + 56 - (state->length % 64);
		ft_memset(&state->buf[state->ret + 1], 0, tmp);
		md5_transform(state);
		ft_memcpy(state->buf, state->buf + 64, 64);
		ft_bzero(state->buf + 64, 64);
		tmp -= 64;
	}

	// version 1
	length = state->length * 8;
	// lp = (char *)&length;
	// state->buf[state->ret + tmp + 0] = lp[0];
	// state->buf[state->ret + tmp + 1] = lp[1];
	// state->buf[state->ret + tmp + 2] = lp[2];
	// state->buf[state->ret + tmp + 3] = lp[3];
	// state->buf[state->ret + tmp + 4] = lp[4];
	// state->buf[state->ret + tmp + 5] = lp[5];
	// state->buf[state->ret + tmp + 6] = lp[6];
	// state->buf[state->ret + tmp + 7] = lp[7];
	// hex_dump("1", state->buf + state->ret + tmp, 64);

	// version 2 WORKS
	ft_memcpy(state->buf + state->ret + tmp, &length, 8);
	// hex_dump("2", state->buf + state->ret + tmp, 64);
	
	
	state->ret = 0;
	return (state);
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

/*
** MD5 helper functions
*/

uint32_t	md5_f(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & y) | (~x & z));
}

uint32_t	md5_g(uint32_t x, uint32_t y, uint32_t z)
{
	return ((x & z) | (y & ~z));
}

uint32_t	md5_h(uint32_t x, uint32_t y, uint32_t z)
{
	return (x ^ y ^ z);
}

uint32_t	md5_i(uint32_t x, uint32_t y, uint32_t z)
{
	return (y ^ (x | ~z));
}

void	md5_transform(t_md5_state *state)
{
	uint32_t	state_copy[4];
	uint32_t	i;
	uint32_t	f;
	uint32_t	g;
	uint32_t	x[16];

	state_copy[0] = state->state[0];
	state_copy[1] = state->state[1];
	state_copy[2] = state->state[2];
	state_copy[3] = state->state[3];
	decode(x, state->buf, 64);
	i = 0;
	while (i < 64)
	{
		if (i <= 15)
		{
			f = md5_f(state_copy[1], state_copy[2], state_copy[3]);
			g = i;
		}
		else if (16 <= i && i <= 31)
		{
			f = md5_g(state_copy[1], state_copy[2], state_copy[3]);
			g = (5 * i + 1) % 16;
		}
		else if (32 <= i && i <= 47)
		{
			f = md5_h(state_copy[1], state_copy[2], state_copy[3]);
			g = (3 * i + 5) % 16;
		}
		else if (48 <= i && i <= 63)
		{
			f = md5_i(state_copy[1], state_copy[2], state_copy[3]);
			g = (7 * i) % 16;
		}
		else
			return ;
		f = f + state_copy[0] + g_md5_t[i] + x[g];
		state_copy[0] = state_copy[3];
		state_copy[3] = state_copy[2];
		state_copy[2] = state_copy[1];
		state_copy[1] = state_copy[1] + rotate_left(f, g_md5_s[i]);
		i++;
	}
	state->state[0] += state_copy[0];
	state->state[1] += state_copy[1];
	state->state[2] += state_copy[2];
	state->state[3] += state_copy[3];
}

void	decode(uint32_t *output, unsigned char *input, unsigned int len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (j < len)
	{
		output[i] = ((uint32_t)input[j]) | (((uint32_t)input[j + 1]) << 8)
			| (((uint32_t)input[j + 2]) << 16) | (((uint32_t)input[j + 3])
			<< 24);
		++i;
		j += 4;
	}
}
