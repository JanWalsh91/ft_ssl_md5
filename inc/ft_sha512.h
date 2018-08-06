/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha512.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 13:28:27 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/06 16:55:26 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHA512_H
# define FT_SHA512_H

# include <math.h>
# include <fcntl.h>
# include <unistd.h>

# include "ft_ssl_core.h"
# include "ft_ssl_helper_functions.h"

# define BUFFER_SIZE 64

typedef	struct			s_sha512_state
{
	uint32_t			state[8];
	unsigned char		buf[BUFFER_SIZE * 2];
	int					ret;
	uint64_t			length;
}						t_sha512_state;

void					ft_sha512(t_task *task);
t_sha512_state			*sha512_init_state(void);
void					sha512_from_file(t_task *task, t_sha512_state *state);
void					sha512_from_string(t_task *task, t_sha512_state *state);
void					sha512_from_stdin(t_task *task, t_sha512_state *state);
t_sha512_state			*sha512_pad(t_sha512_state *state);
void					sha512_update_state(t_sha512_state *state);
void					sha512_transform(t_sha512_state *state);
void					sha512_compression(uint32_t state_copy[8],
							uint32_t w[64], uint32_t *s0, uint32_t *s1);

static const uint32_t	g_sha512_k[64] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

#endif
