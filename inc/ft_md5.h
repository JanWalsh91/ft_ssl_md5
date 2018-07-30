/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:43:42 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/30 11:14:38 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

# include <math.h>
# include <fcntl.h>
# include <unistd.h>

# include "ft_ssl_core.h"
# include "ft_ssl_helper_functions.h"

# define BUFFER_SIZE 64

typedef	struct	s_md5_state
{
	uint32_t		state[4];
	unsigned char	buf[BUFFER_SIZE * 2 + 1];
	int				ret;
	uint64_t		length;
	// or uint32_t length[2];
}				t_md5_state;

void			ft_md5(t_task *task);
t_md5_state		*md5_init_state(void);
void			md5_update_state(t_md5_state *state);
t_md5_state		*md5_pad(t_md5_state *state);
void			md5_transform(t_md5_state *state);


// helper functions
uint32_t	md5_f(uint32_t x, uint32_t y, uint32_t z);
uint32_t	md5_g(uint32_t x, uint32_t y, uint32_t z);
uint32_t	md5_h(uint32_t x, uint32_t y, uint32_t z);
uint32_t	md5_i(uint32_t x, uint32_t y, uint32_t z);
uint32_t	rotate_left(uint32_t x, uint32_t n);


// void	encode(unsigned char *output, uint32_t *input, unsigned int len);
void	decode(uint32_t *output, unsigned char *input, unsigned int len);

// original
static const uint32_t		g_md5_t[64] = {
	0xd76aa478,
	0xe8c7b756,
	0x242070db,
	0xc1bdceee,
	0xf57c0faf,
	0x4787c62a,
	0xa8304613,
	0xfd469501,
	0x698098d8,
	0x8b44f7af,
	0xffff5bb1,
	0x895cd7be,
	0x6b901122,
	0xfd987193,
	0xa679438e,
	0x49b40821,
	0xf61e2562,
	0xc040b340,
	0x265e5a51,
	0xe9b6c7aa,
	0xd62f105d,
	0x2441453,
	0xd8a1e681,
	0xe7d3fbc8,
	0x21e1cde6,
	0xc33707d6,
	0xf4d50d87,
	0x455a14ed,
	0xa9e3e905,
	0xfcefa3f8,
	0x676f02d9,
	0x8d2a4c8a,
	0xfffa3942,
	0x8771f681,
	0x6d9d6122,
	0xfde5380c,
	0xa4beea44,
	0x4bdecfa9,
	0xf6bb4b60,
	0xbebfbc70,
	0x289b7ec6,
	0xeaa127fa,
	0xd4ef3085,
	0x4881d05,
	0xd9d4d039,
	0xe6db99e5,
	0x1fa27cf8,
	0xc4ac5665,
	0xf4292244,
	0x432aff97,
	0xab9423a7,
	0xfc93a039,
	0x655b59c3,
	0x8f0ccc92,
	0xffeff47d,
	0x85845dd1,
	0x6fa87e4f,
	0xfe2ce6e0,
	0xa3014314,
	0x4e0811a1,
	0xf7537e82,
	0xbd3af235,
	0x2ad7d2bb,
	0xeb86d391
};

// static const uint32_t		g_md5_t[64] = {
// 	0x78a46ad7,
// 	0x56b7c7e8,
// 	0xdb702024,
// 	0xeecebdc1,
// 	0xaf0f7cf5,
// 	0x2ac68747,
// 	0x134630a8,
// 	0x019546fd,
// 	0xd8988069,
// 	0xaff7448b,
// 	0xb15bffff,
// 	0xbed75c89,
// 	0x2211906b,
// 	0x937198fd,
// 	0x8e4379a6,
// 	0x2108b449,
// 	0x62251ef6,
// 	0x40b340c0,
// 	0x515a5e26,
// 	0xaac7b6e9,
// 	0x5d102fd6,
// 	0x53144402,
// 	0x81e6a1d8,
// 	0xc8fbd3e7,
// 	0xe6cde121,
// 	0xd60737c3,
// 	0x870dd5f4,
// 	0xed145a45,
// 	0x05e9e3a9,
// 	0xf8a3effc,
// 	0xd9026f67,
// 	0x8a4c2a8d,
// 	0x4239faff,
// 	0x81f67187,
// 	0x22619d6d,
// 	0x0c38e5fd,
// 	0x44eabea4,
// 	0xa9cfde4b,
// 	0x604bbbf6,
// 	0x70bcbfbe,
// 	0xc67e9b28,
// 	0xfa27a1ea,
// 	0x8530efd4,
// 	0x051d8804,
// 	0x39d0d4d9,
// 	0xe599dbe6,
// 	0xf87ca21f,
// 	0x6556acc4,
// 	0x442229f4,
// 	0x97ff2a43,
// 	0xa72394ab,
// 	0x39a093fc,
// 	0xc3595b65,
// 	0x92cc0c8f,
// 	0x7df4efff,
// 	0xd15d8485,
// 	0x4f7ea86f,
// 	0xe0e62cfe,
// 	0x144301a3,
// 	0xa111084e,
// 	0x827e53f7,
// 	0x35f23abd,
// 	0xbbd2d72a,
// 	0x91d386eb
// };

// static const uint32_t	g_md5_s[4][4] = {
// 	{7, 12, 17, 22},
// 	{5, 9, 14, 20},
// 	{4, 11, 16, 23},
// 	{6, 10, 15, 21}
// };

static const uint32_t	g_md5_s[64] = {
	7, 12, 17, 22,
	7, 12, 17, 22,
	7, 12, 17, 22,
	7, 12, 17, 22,
	5, 9, 14, 20,
	5, 9, 14, 20,
	5, 9, 14, 20,
	5, 9, 14, 20,
	4, 11, 16, 23,
	4, 11, 16, 23,
	4, 11, 16, 23,
	4, 11, 16, 23,
	6, 10, 15, 21,
	6, 10, 15, 21,
	6, 10, 15, 21,
	6, 10, 15, 21
};

#endif