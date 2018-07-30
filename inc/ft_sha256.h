/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 13:28:27 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/30 16:09:49 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHA256_H
# define FT_SHA256_H

# include <math.h>
# include <fcntl.h>
# include <unistd.h>

# include "ft_ssl_core.h"
# include "ft_ssl_helper_functions.h"
# include "ft_md5.h"

# define BUFFER_SIZE 64

typedef	struct	s_sha256_state
{
	uint32_t		state[8];
	unsigned char	buf[BUFFER_SIZE * 2];
	int				ret;
	uint64_t		length;
}				t_sha256_state;

void	ft_sha256(t_task *task);
t_sha256_state	*sha256_init_state(void);
void	sha256_from_file(t_task *task, t_sha256_state *state);
t_sha256_state	*sha256_pad(t_sha256_state *state);
void	sha256_update_state(t_sha256_state *state);
void	sha256_transform(t_sha256_state *state);

// // original 
// static const uint32_t		g_sha256_k[64] = {
// 	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
// 	0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
// 	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
// 	0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
// 	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
// 	0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
// 	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
// 	0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
// 	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
// 	0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
// 	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
// };

// switch endian
static const uint32_t		g_sha256_k[64] = {
	0x982f8a42, 0x91443771, 0xcffbc0b5, 0xa5dbb5e9, 0x5bc25639, 0xf111f159,
	0xa4823f92, 0xd55e1cab, 0x98aa07d8, 0x015b8312, 0xbe853124, 0xc37d0c55,
	0x745dbe72, 0xfeb1de80, 0xa706dc9b, 0x74f19bc1, 0xc1699be4, 0x8647beef,
	0xc69dc10f, 0xcca10c24, 0x6f2ce92d, 0xaa84744a, 0xdca9b05c, 0xda88f976,
	0x52513e98, 0x6dc631a8, 0xc82703b0, 0xc77f59bf, 0xf30be0c6, 0x4791a7d5,
	0x5163ca06, 0x67292914, 0x850ab727, 0x38211b2e, 0xfc6d2c4d, 0x130d3853,
	0x54730a65, 0xbb0a6a76, 0x2ec9c281, 0x852c7292, 0xa1e8bfa2, 0x4b661aa8,
	0x708b4bc2, 0xa3516cc7, 0x19e892d1, 0x240699d6, 0x85350ef4, 0x70a06a10,
	0x16c1a419, 0x086c371e, 0x4c774827, 0xb5bcb034, 0xb30c1c39, 0x4aaad84e,
	0x4fca9c5b, 0xf36f2e68, 0xee828f74, 0x6f63a578, 0x1478c884, 0x0802c78c,
	0xfaffbe90, 0xeb6c50a4, 0xf7a3f9be, 0xf27871c6
};

#endif