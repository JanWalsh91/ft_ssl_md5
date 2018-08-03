/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha512_update_state.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 13:28:18 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/03 16:41:50 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha512.h"

void			sha512_update_state(t_sha512_state *state)
{
	state->length += state->ret;
	sha512_transform(state);
	ft_bzero(state->buf, 64 * 2);
}

t_sha512_state	*sha512_pad(t_sha512_state *state)
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
		sha512_transform(state);
		ft_memcpy(state->buf, state->buf + 64, 64);
		ft_bzero(state->buf + 64, 64);
		tmp -= 64;
	}
	state->length *= 8;
	byte_swap((void *)&length, (void *)&state->length, sizeof(length), 1);
	*(uint64_t *)&(state->buf[state->ret + tmp]) = length;
	state->ret = 0;
	return (state);
}

void			sha512_transform(t_sha512_state *state)
{
	uint32_t		state_copy[8];
	uint32_t		w[64];
	int				i;
	uint32_t		s0;
	uint32_t		s1;

	ft_bzero(w, 64 * 4);
	byte_swap((void *)w, (void *)state->buf, 4, 16);
	i = 16;
	while (i < 64)
	{
		s0 = rotate_right(w[i - 15], 7)
			^ rotate_right(w[i - 15], 18) ^ (w[i - 15] >> 3);
		s1 = rotate_right(w[i - 2], 17)
			^ rotate_right(w[i - 2], 19) ^ (w[i - 2] >> 10);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
		++i;
	}
	ft_memcpy(state_copy, state->state, sizeof(state_copy));
	sha512_compression(state_copy, w, &s0, &s1);
	i = -1;
	while (++i < 8)
		state->state[i] += state_copy[i];
}

void			sha512_compression(uint32_t state_copy[8], uint32_t w[64],
				uint32_t *s0, uint32_t *s1)
{
	uint32_t	tmp[4];
	int			i;

	i = -1;
	while (++i < 64)
	{
		*s1 = rotate_right(state_copy[4], 6) ^ rotate_right(state_copy[4], 11)
			^ rotate_right(state_copy[4], 25);
		tmp[0] = (state_copy[4] & state_copy[5])
			^ ((~state_copy[4]) & state_copy[6]);
		tmp[2] = state_copy[7] + *s1 + tmp[0] + g_sha512_k[i] + w[i];
		*s0 = rotate_right(state_copy[0], 2) ^ rotate_right(state_copy[0], 13)
			^ rotate_right(state_copy[0], 22);
		tmp[1] = (state_copy[0] & state_copy[1])
			^ (state_copy[0] & state_copy[2]) ^ (state_copy[1] & state_copy[2]);
		tmp[3] = *s0 + tmp[1];
		state_copy[7] = state_copy[6];
		state_copy[6] = state_copy[5];
		state_copy[5] = state_copy[4];
		state_copy[4] = state_copy[3] + tmp[2];
		state_copy[3] = state_copy[2];
		state_copy[2] = state_copy[1];
		state_copy[1] = state_copy[0];
		state_copy[0] = tmp[2] + tmp[3];
	}
}
