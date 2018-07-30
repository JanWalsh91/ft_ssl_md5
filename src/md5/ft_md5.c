/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:46:57 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/30 11:19:29 by jwalsh           ###   ########.fr       */
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

	// TODO: use return value to check for errors

	hex_dump("first state", state->state, 16);
	while ((state->ret = read(fd, &state->buf, BUFFER_SIZE - 1)) == BUFFER_SIZE - 1)
		md5_update_state(state);
	md5_update_state(md5_pad(state));
	hex_dump("final state", state->state, 16);
	// print result
}


void	md5_update_state(t_md5_state *state)
{
	printf("md5_update_state\n");
	state->length += state->ret;
	(void)state;

	md5_transform(state);
}

t_md5_state	*md5_pad(t_md5_state *state)
{
	size_t		tmp;
	// uint8_t		*p;

	printf("md5_pad\n");
	hex_dump("buffer before padding", state->buf, 64);
	state->length += state->ret;
	// printf("length: %llu\n", state->length);
	// printf("ret: %d\n", state->ret);
	// hex_dump("buffer", state->buf, state->ret);
	// pad state->buf with 1 and 0's until length(state->buf) % (512/8) == 448/8
	state->buf[state->ret] = 0x80;
	// hex_dump("buffer", state->buf, state->ret + 1);
	if ((state->ret + 1) % 64 < 56)
	{
		printf("length less than 56\n");
		tmp = 56 - (state->length % 64);
		ft_memset(&state->buf[state->ret + 1], 0, tmp);
	}
	else
	{
		printf("length more than 56\n");
		tmp = 64 + 56 - (state->length % 64);
		ft_memset(&state->buf[state->ret], 0, tmp);
	}
	// int i = 0;

	// then add total length of message (before padding) as unint64_t
	uint64_t length = state->length * 8;
	char	*lp = (char *)&length;
	// while (i < 4)
	// {
	// 	// printf("state->length >> %d*8: %llx\n", i, state->length >> (i*8));
	// 	state->buf[state->ret + tmp + 3 - i] = (uint8_t)(length >> (i*8));
	// 	++i;
	// }
	hex_dump("length", &length, 8);
	state->buf[state->ret + tmp + 0] = lp[0];
	state->buf[state->ret + tmp + 1] = lp[1];
	state->buf[state->ret + tmp + 2] = lp[2];
	state->buf[state->ret + tmp + 3] = lp[3];

	state->buf[state->ret + tmp + 4] = lp[4];
	state->buf[state->ret + tmp + 5] = lp[5];
	state->buf[state->ret + tmp + 6] = lp[6];
	state->buf[state->ret + tmp + 7] = lp[7];
	printf("length: %llu\n", length);

	hex_dump("state->state[0]", &state->state[0], 4);
	// printf("final size: %lu\n", state->ret + tmp + 8);
	state->ret = 0;
	hex_dump("buffer after padding", state->buf, 64);
	return (state);
}

t_md5_state		*md5_init_state(void)
{
	printf("md5_init_state\n");
	t_md5_state *state;

	if (!(state = (t_md5_state *)ft_memalloc(sizeof(t_md5_state))))
		return (NULL);
	// state->state[0] = 0x01234567;
	// state->state[1] = 0x89abcdef;
	// state->state[2] = 0xfedcba98;
	// state->state[3] = 0x76543210;
	// original
	state->state[0] = 0x67452301;
	state->state[1] = 0xefcdab89;
	state->state[2] = 0x98badcfe;
	state->state[3] = 0x10325476;
	ft_bzero(state->buf, BUFFER_SIZE);
	hex_dump("init state", state->state, 16);
	printf("md5_init_state END:\n");
	printf("\tA = %u\n", state->state[0]);
	printf("\tB = %u\n", state->state[1]);
	printf("\tC = %u\n", state->state[2]);
	printf("\tD = %u\n", state->state[3]);
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

uint32_t	rotate_left(uint32_t x, uint32_t n)
{
	return (((x) << (n)) | ((x) >> (32-(n))));
	// printf("rotate_left %x by %u = %x\n", x, n, r);
	// return r;
}


// #define FF(a, b, c, d, x, s, ac) { \
//  (a) += F ((b), (c), (d)) + (x) + (UINT4)(ac); \
//  (a) = ROTATE_LEFT ((a), (s)); \
//  (a) += (b); \
//   }
// #define GG(a, b, c, d, x, s, ac) { \
//  (a) += G ((b), (c), (d)) + (x) + (UINT4)(ac); \
//  (a) = ROTATE_LEFT ((a), (s)); \
//  (a) += (b); \
//   }
// #define HH(a, b, c, d, x, s, ac) { \
//  (a) += H ((b), (c), (d)) + (x) + (UINT4)(ac); \
//  (a) = ROTATE_LEFT ((a), (s)); \
//  (a) += (b); \
//   }
// #define II(a, b, c, d, x, s, ac) { \
//  (a) += I ((b), (c), (d)) + (x) + (UINT4)(ac); \
//  (a) = ROTATE_LEFT ((a), (s)); \
//  (a) += (b); \
//   }

void	md5_transform(t_md5_state *state)
{
	printf("=====md5_transform======\n");
	uint32_t	state_copy[4];
	// uint32_t	x[16];
	uint32_t	i;
	uint32_t	f;
	uint32_t	g;

	state_copy[0] = state->state[0];
	state_copy[1] = state->state[1];
	state_copy[2] = state->state[2];
	state_copy[3] = state->state[3];
	printf("initial state_copy:\n");
	printf("\tA = %u\n", state_copy[0]);
	printf("\tB = %u\n", state_copy[1]);
	printf("\tC = %u\n", state_copy[2]);
	printf("\tD = %u\n", state_copy[3]);
	// for (int y = 0; y < 16; y++)
	// {
	// 	printf("[%d]: %d\n", y, *(((int*)(state->buf)) + y) );
	// }

	uint32_t x[16];
	hex_dump("state->buf", &state->buf, 4);
	decode(x, state->buf, 64);
	hex_dump("x", x, 4);
	// return ;
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
			// update A every time
		f = f + state_copy[0] + g_md5_t[i] + x[g];
		// f = f + state_copy[0] + g_md5_t[i] + state->buf[g];
		// uint32_t	tmp = state_copy[3]
			// 'rotate' state to update next one
		state_copy[0] = state_copy[3];
		state_copy[3] = state_copy[2];
		state_copy[2] = state_copy[1];

		// hex_dump("f before rotate", &f, 4);
		// printf("f before rotate: %u\n", f);
		// TODO: i can go up to 64, but g_md5_s does not!
		state_copy[1] = state_copy[1] + rotate_left(f, g_md5_s[i]);
		// f = rotate_left(f, g_md5_s[i]);
		// printf("rotate by %d\n", g_md5_s[i]);
		// printf("f after rotate: %u\n", f);
		// hex_dump("f after rotate", &f, 4);
		// return ;
		// hex_dump("state", state_copy, 16);
		// printf("sizeof(state_copy): %lu\n", sizeof(state_copy));
		printf("Round %d: \n", i);
		printf("\tA = %u\n", state_copy[0]);
		printf("\tB = %u\n", state_copy[1]);
		printf("\tC = %u\n", state_copy[2]);
		printf("\tD = %u\n", state_copy[3]);
		// printf("\tA = %x\t", state_copy[0]);
		// printf("\tB = %x\n", state_copy[1]);
		// printf("\tC = %x\t", state_copy[2]);
		// printf("\tD = %x\n", state_copy[3]);
		i++;
		// if (i > 4)
		// 	return ;
	}
	state->state[0] += state_copy[0];
	state->state[1] += state_copy[1];
	state->state[2] += state_copy[2];
	state->state[3] += state_copy[3];
}

/* Encodes input (uint32_t) into output (unsigned char). Assumes len is
  a multiple of 4.
 */
// void	encode(unsigned char *output, uint32_t *input, unsigned int len)
// {
// 	unsigned int	i;
// 	unsigned int	j;

// 	i = 0;
// 	j = 0;
// 	while (j < len)
// 	{
// 		output[j] = (unsigned char)(input[i] & 0xff);
// 		output[j+1] = (unsigned char)((input[i] >> 8) & 0xff);
// 		output[j+2] = (unsigned char)((input[i] >> 16) & 0xff);
// 		output[j+3] = (unsigned char)((input[i] >> 24) & 0xff);
// 		i++;
// 		j += 4;
// 	}
// }

/* Decodes input (unsigned char) into output (uint32_t). Assumes len is
  a multiple of 4.
 */
void	decode(uint32_t *output, unsigned char *input, unsigned int len)
{
	printf("decode\n");
	unsigned int	i;
	unsigned int	j;
	
	i = 0;
	j = 0;
	while (j < len)
	{
		printf("check\n");
 		output[i] = ((uint32_t)input[j]) | (((uint32_t)input[j + 1]) << 8) |
  			(((uint32_t)input[j + 2]) << 16) | (((uint32_t)input[j + 3]) << 24);
		++i;
		j += 4;
	}
}
