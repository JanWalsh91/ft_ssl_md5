/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5_update_state.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:46:57 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/06 16:52:34 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"

void		md5_update_state(t_md5_state *state)
{
	state->length += state->ret;
	md5_transform(state);
	ft_bzero(state->buf, 64 * 2);
}

t_md5_state	*md5_pad(t_md5_state *state)
{
	size_t		tmp;
	uint64_t	length;

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
	length = state->length * 8;
	ft_memcpy(state->buf + state->ret + tmp, &length, 8);
	state->ret = 0;
	return (state);
}

void		md5_transform(t_md5_state *state)
{
	uint32_t	state_copy[4];
	uint32_t	i;
	uint32_t	f;
	uint32_t	g;
	uint32_t	x[16];

	ft_memcpy(state_copy, state->state, sizeof(state_copy));
	decode(x, state->buf, 64);
	i = 0;
	while (i < 64)
	{
		get_f_and_g(&f, &g, state_copy, i);
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

void		get_f_and_g(uint32_t *f, uint32_t *g,
			uint32_t state_copy[4], uint32_t i)
{
	if (i <= 15)
	{
		*f = md5_f(state_copy[1], state_copy[2], state_copy[3]);
		*g = i;
	}
	else if (16 <= i && i <= 31)
	{
		*f = md5_g(state_copy[1], state_copy[2], state_copy[3]);
		*g = (5 * i + 1) % 16;
	}
	else if (32 <= i && i <= 47)
	{
		*f = md5_h(state_copy[1], state_copy[2], state_copy[3]);
		*g = (3 * i + 5) % 16;
	}
	else if (48 <= i && i <= 63)
	{
		*f = md5_i(state_copy[1], state_copy[2], state_copy[3]);
		*g = (7 * i) % 16;
	}
}
