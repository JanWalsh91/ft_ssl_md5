/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:46:57 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/28 16:23:29 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"

void	ft_md5(t_task *task)
{
	printf("ft_md5\n");
	(void)task;
	t_md5_state *state;
	int			fd;

	// initialize md5 state/context
	if (!(state = md5_init_state()))
		return ;
	
	
	
	// A. read from file
	if (!task->file)
		return ;
	// TODO: check for opening error
	fd = open(task->file, O_RDONLY);

	// read [16 * 32 bits] / [16 * 4] at a time 
	// for each full block
	// int ret;
	// TODO: use return value to check for errors

	while ((state->ret = read(fd, &state->buf, BUFFER_SIZE - 1)) == BUFFER_SIZE - 1)
		md5_update_state(state);
	md5_update_state(md5_pad(state));

	// print result
}


void	md5_update_state(t_md5_state *state)
{
	printf("md5_update_state\n");
	state->length += state->ret;
	(void)state;
}

t_md5_state	*md5_pad(t_md5_state *state)
{
	size_t		tmp;
	// uint8_t		*p;

	printf("md5_pad\n");
	state->length += state->ret;
	printf("length: %llu\n", state->length);
	printf("ret: %d\n", state->ret);
	hex_dump("buffer", state->buf, state->ret);
	// pad state->buf with 1 and 0's until length(state->buf) % (512/8) == 448/8
	state->buf[state->ret] = 0x80;
	hex_dump("buffer", state->buf, state->ret + 1);
	if ((state->ret + 1) % 64 < 56)
	{
		tmp = 56 - (state->length % 64);
		ft_memset(&state->buf[state->ret + 1], 0, tmp);
	}
	else
	{
		tmp = 64 + 56 - (state->length % 64);
		ft_memset(&state->buf[state->ret], 0, tmp);
	}
	int i = 0;

	// then add total length of message (before padding) as unint64_t
	while (i < 8)
	{
		// printf("state->length >> %d*8: %llx\n", i, state->length >> (i*8));
		state->buf[state->ret + tmp + 7 - i] = (uint8_t)(state->length >> (i*8));
		++i;
	}
	hex_dump("buffer", state->buf, state->ret + tmp + 8);
	printf("final size: %lu\n", state->ret + tmp + 8);
	state->ret = 0;
	return (state);
}

t_md5_state		*md5_init_state(void)
{
	t_md5_state *state;
	int i;

	if (!(state = (t_md5_state *)ft_memalloc(sizeof(t_md5_state))))
		return (NULL);
	state->state[0] = 0x67452301;
	state->state[1] = 0xefcdab89;
	state->state[2] = 0x98badcfe;
	state->state[3] = 0x10325476;
	i = 0;
	while (i < 64)
	{
		g_md5_t[i] = 4294967296 * fabs(sin(i));
		// printf("g_md5_t[%d] = %x\n", i, g_md5_t[i]);
		++i;
	}
	ft_bzero(state->buf, BUFFER_SIZE);
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

// #define FF(a, b, c, d, x, s, ac) { \
//  (a) += F ((b), (c), (d)) + (x) + (UINT4)(ac); \
//  (a) = ROTATE_LEFT ((a), (s)); \
//  (a) += (b); \
//   }

// uint32_t	md5_ff(uint32_t a, )

// ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

// uint32_t	rotate_left(uint32_t x, uint32_t n)
// {
		
// }





