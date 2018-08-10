/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha512_update_state.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 13:28:18 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/09 11:19:02 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha512.h"

void			sha512_update_state(t_sha512_state *state)
{
	if (8 * state->ret + state->length[1] < state->length[1])
		++state->length[0];
	state->length[1] += 8 * state->ret;
	sha512_transform(state);
	ft_bzero(state->buf, 64 * 4);
}

t_sha512_state	*sha512_pad(t_sha512_state *state)
{
	size_t		tmp;

	if (8 * state->ret + state->length[1] < state->length[1])
		++state->length[0];
	state->length[1] += 8 * state->ret;
	state->buf[state->ret] = 0x80;
	if ((state->ret + 1) % 128 < 112)
	{
		tmp = 112 - ((state->length[1] / 8) % 128);
		ft_memset(&state->buf[state->ret + 1], 0, tmp);
	}
	else
	{
		tmp = 128 + 112 - ((state->length[1] / 8) % 128);
		ft_memset(&state->buf[state->ret + 1], 0, tmp);
		sha512_transform(state);
		ft_memcpy(state->buf, state->buf + 128, 128);
		ft_bzero(state->buf + 128, 128);
		tmp -= 128;
	}
	sha512_append_length(state, tmp);
	return (state);
}

void			sha512_append_length(t_sha512_state *state, size_t tmp)
{
	uint64_t	length[2];

	byte_swap((void *)&length, (void *)&state->length,
		sizeof(state->length[0]), 2);
	*(uint64_t *)&(state->buf[state->ret + tmp]) = length[0];
	*(uint64_t *)&(state->buf[state->ret + tmp + 8]) = length[1];
	state->ret = 0;
}

void			sha512_transform(t_sha512_state *state)
{
	uint64_t		state_copy[8];
	uint64_t		w[80];
	int				i;
	uint64_t		s0;
	uint64_t		s1;

	ft_bzero(w, 64 * 8);
	byte_swap((void *)w, (void *)state->buf, 8, 16);
	i = 16;
	while (i < 80)
	{
		s0 = rotate_right_64(w[i - 15], 1)
			^ rotate_right_64(w[i - 15], 8) ^ (w[i - 15] >> 7);
		s1 = rotate_right_64(w[i - 2], 19)
			^ rotate_right_64(w[i - 2], 61) ^ (w[i - 2] >> 6);
		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
		++i;
	}
	ft_memcpy(state_copy, state->state, sizeof(state_copy));
	sha512_compression(state_copy, w, &s0, &s1);
	i = -1;
	while (++i < 8)
		state->state[i] += state_copy[i];
}

void			sha512_compression(uint64_t copy[8], uint64_t w[80],
				uint64_t *s0, uint64_t *s1)
{
	uint64_t	tmp[4];
	int			i;

	i = -1;
	while (++i < 80)
	{
		*s1 = rotate_right_64(copy[4], 14) ^ rotate_right_64(copy[4], 18)
			^ rotate_right_64(copy[4], 41);
		tmp[0] = (copy[4] & copy[5])
			^ ((~copy[4]) & copy[6]);
		tmp[2] = copy[7] + *s1 + tmp[0] + g_sha512_k[i] + w[i];
		*s0 = rotate_right_64(copy[0], 28) ^ rotate_right_64(copy[0], 34)
			^ rotate_right_64(copy[0], 39);
		tmp[1] = (copy[0] & copy[1])
			^ (copy[0] & copy[2]) ^ (copy[1] & copy[2]);
		tmp[3] = *s0 + tmp[1];
		copy[7] = copy[6];
		copy[6] = copy[5];
		copy[5] = copy[4];
		copy[4] = copy[3] + tmp[2];
		copy[3] = copy[2];
		copy[2] = copy[1];
		copy[1] = copy[0];
		copy[0] = tmp[2] + tmp[3];
	}
}
