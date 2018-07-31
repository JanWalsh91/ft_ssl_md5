/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 13:28:18 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/31 12:19:30 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha256.h"

void	ft_sha256(t_task *task)
{
	printf("ft_sha256\n");
	(void)task;
	t_sha256_state *state;

	// initialize sha256 state/context
	if (!(state = sha256_init_state()))
		return ;
	
	// if OPTION_S: read from string
	// if ((task->opts | OPTION_S) == task->opts)
	// 	sha256_from_string(task, state);
	// else if ((task->opts | OPTION_STDIN) == task->opts)
	// 	sha256_from_stdin(task, state);
	// else if (task->file)
	if (task->file)
		sha256_from_file(task, state);
	else
		printf("no file\n");
	
	// else
		// sha256_from_stdin(task, state);

	// if OPTION_P: read from stdin
	// else read from string

	
	// TODO: print result
	// TODO: close, free state
}

t_sha256_state		*sha256_init_state(void)
{
	printf("sha256_init_state\n");
	t_sha256_state *state;

	if (!(state = (t_sha256_state *)ft_memalloc(sizeof(t_sha256_state))))
		return (NULL);
		
	// original
	state->state[0] = 0x6a09e667;
	state->state[1] = 0xbb67ae85;
	state->state[2] = 0x3c6ef372;
	state->state[3] = 0xa54ff53a;
	state->state[4] = 0x510e527f;
	state->state[5] = 0x9b05688c;
	state->state[6] = 0x1f83d9ab;
	state->state[7] = 0x5be0cd19;
	// // switch endian
	// state->state[0] = 0x67e6096a;
	// state->state[1] = 0x85ae67bb;
	// state->state[2] = 0x72f36e3c;
	// state->state[3] = 0x3af54fa5;
	// state->state[4] = 0x7f520e51;
	// state->state[5] = 0x8c68059b;
	// state->state[6] = 0xabd9831f;
	// state->state[7] = 0x19cde05b;
	// ft_bzero(state->buf, BUFFER_SIZE);
	hex_dump("init state", state->state, 16);
	hex_dump("buf", state->buf, 64 * 2);
	printf("sha256_init_state END:\n");
	// printf("\tA = %u\n", state->state[0]);
	// printf("\tB = %u\n", state->state[1]);
	// printf("\tC = %u\n", state->state[2]);
	// printf("\tD = %u\n", state->state[3]);

	return (state);
}

void	sha256_from_file(t_task *task, t_sha256_state *state)
{
	printf("sha256_from_file\n");
	int			fd;

	// TODO: check for opening error
	fd = open(task->file, O_RDONLY);
	if (fd == -1)
	{
		printf("error opening\n");
		exit(0);
	}
	// TODO: use return value to check for errors

	hex_dump("first state", state->state, 32);
	while ((state->ret = read(fd, &state->buf, BUFFER_SIZE)) == BUFFER_SIZE)
		sha256_update_state(state);
	sha256_update_state(sha256_pad(state));


	hex_dump("final state", state->state, 64);

	// char hash[32];

	// for (int i = 0; i < 4; ++i) {
	// 	hash[i]      = (state->state[0] >> (24 - i * 8)) & 0x000000ff;
	// 	hash[i + 4]  = (state->state[1] >> (24 - i * 8)) & 0x000000ff;
	// 	hash[i + 8]  = (state->state[2] >> (24 - i * 8)) & 0x000000ff;
	// 	hash[i + 12] = (state->state[3] >> (24 - i * 8)) & 0x000000ff;
	// 	hash[i + 16] = (state->state[4] >> (24 - i * 8)) & 0x000000ff;
	// 	hash[i + 20] = (state->state[5] >> (24 - i * 8)) & 0x000000ff;
	// 	hash[i + 24] = (state->state[6] >> (24 - i * 8)) & 0x000000ff;
	// 	hash[i + 28] = (state->state[7] >> (24 - i * 8)) & 0x000000ff;
	// }

	// hex_dump("final hash", hash, 32);
}

t_sha256_state	*sha256_pad(t_sha256_state *state)
{
	size_t		tmp;
	// uint8_t		*p;

	printf("sha256_pad\n");
	hex_dump("buffer before padding", state->buf, 64);
	state->length += state->ret;
	// printf("length: %llu\n", state->length);
	// printf("ret: %d\n", state->ret);
	hex_dump("buffer", state->buf, BUFFER_SIZE * 2);
	// pad state->buf with 1 and 0's until length(state->buf) % (512/8) == 448/8
	state->buf[state->ret] = 0x80;
	hex_dump("buffer", state->buf, BUFFER_SIZE * 2);
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
		ft_memset(&state->buf[state->ret + 1], 0, tmp);
		sha256_transform(state);
		hex_dump("buffer before cpy", state->buf, BUFFER_SIZE * 2);
		ft_memcpy(state->buf, state->buf + 64, 64);
		hex_dump("buffer after cpy", state->buf, BUFFER_SIZE * 2);
		ft_bzero(state->buf + 64, 64);
		hex_dump("buffer after bzero", state->buf, BUFFER_SIZE * 2);
		tmp -= 64;
	}
	// int i = 0;

	// then add total length of message (before padding) as unint64_t
	// while (i < 4)
	// {
	// 	// printf("state->length >> %d*8: %llx\n", i, state->length >> (i*8));
	// 	state->buf[state->ret + tmp + 3 - i] = (uint8_t)(length >> (i*8));
	// 	++i;
	// }
	// TODO: MAY BE DIFFERENT FOR SHA256
	
	// hex_dump("length", &length, 8);
	
	// // == add length to end, method 1 == //  
	// uint64_t length = state->length * 8;

	// char	*lp = (char *)&length;
	// state->buf[state->ret + tmp + 0] = lp[0];
	// state->buf[state->ret + tmp + 1] = lp[1];
	// state->buf[state->ret + tmp + 2] = lp[2];
	// state->buf[state->ret + tmp + 3] = lp[3];

	// state->buf[state->ret + tmp + 4] = lp[4];
	// state->buf[state->ret + tmp + 5] = lp[5];
	// state->buf[state->ret + tmp + 6] = lp[6];
	// state->buf[state->ret + tmp + 7] = lp[7];
	// printf("length: %llu\n", length);

	// == add length to end, method 2 == //  
	// state->buf[7] = (uint8_t) (length << 3);
	// length >>= 5;
	// for (int i = 6; i >= 0; i--) {
	// 	state->buf[i] = (uint8_t) length;
	// 	length >>= 8;
	// }

	// == add length to end, method 3 == // 
	uint64_t length;
	state->length *= 8;

	byte_swap((void *)&length, (void *)&state->length, sizeof(length), 1);
	*(uint64_t *)&(state->buf[state->ret + tmp]) = length;


	hex_dump("state->state[0]", &state->state[0], 4);
	// printf("final size: %lu\n", state->ret + tmp + 8);
	state->ret = 0;
	hex_dump("buffer after padding", state->buf, 64);
	return (state);
}

void	sha256_update_state(t_sha256_state *state)
{
	printf("sha256_update_state\n");
	state->length += state->ret;
	sha256_transform(state);
	// empty buffer
	ft_bzero(state->buf, 64 * 2);
}

void	sha256_transform(t_sha256_state *state)
{
	static int count = 0;
	printf("===== sha256_transform: section %d ======\n", count);
	uint32_t		state_copy[8];
	uint32_t		w[64];
	int				i;
	uint32_t		s0;
	uint32_t		s1;
	// for state->buf, create 64-entry message

	hex_dump("state->buf", state->buf, 64);
	ft_bzero(w, 64 * 4);
	hex_dump("w after bzero", w, 64 * 4);
	// copy chunk into first 16 words w[0..15] of the message schedule array
	// ft_memcpy(w, state->buf, BUFFER_SIZE);
	// decode(w, state->buf, 64);
	byte_swap((void *)w, (void *)state->buf, 4, 16);
	hex_dump("state->buf", state->buf, 4 * 64);
	hex_dump("w", w, 4 * 64);
	
	// exit(0);
	// Extend the first 16 words into the remaining 48 words w[16..63] of the message schedule array:
	i = 16;
	while (i < 64)
	{
		s0 = rotate_right(w[i-15], 7) ^ rotate_right(w[i-15], 18) ^ (w[i-15] >> 3);
		s1 = rotate_right(w[i-2], 17) ^ rotate_right(w[i-2], 19) ^ (w[i-2] >> 10);
		w[i] = w[i-16] + s0 + w[i-7] + s1;
		++i;		
	}

	// Initialize working variables to current hash value:
	state_copy[0] = state->state[0]; // a
	state_copy[1] = state->state[1]; // b
	state_copy[2] = state->state[2]; // c
	state_copy[3] = state->state[3]; // d
	state_copy[4] = state->state[4]; // e
	state_copy[5] = state->state[5]; // f
	state_copy[6] = state->state[6]; // g
	state_copy[7] = state->state[7]; // h

	// Compression function main loop:
	i = 0;
	while (i < 64)
	{
		s1 = rotate_right(state_copy[4], 6) ^ rotate_right(state_copy[4], 11) ^ rotate_right(state_copy[4], 25);
        uint32_t ch = (state_copy[4] & state_copy[5]) ^ ((~state_copy[4]) & state_copy[6]);
        uint32_t temp1 = state_copy[7] + s1 + ch + g_sha256_k[i] + w[i];
        s0 = rotate_right(state_copy[0], 2) ^ rotate_right(state_copy[0], 13) ^ rotate_right(state_copy[0], 22);
        uint32_t maj = (state_copy[0] & state_copy[1]) ^ (state_copy[0] & state_copy[2]) ^ (state_copy[1] & state_copy[2]);
        uint32_t temp2 = s0 + maj;
 
        state_copy[7] = state_copy[6];
        state_copy[6] = state_copy[5];
        state_copy[5] = state_copy[4];
        state_copy[4] = state_copy[3] + temp1;
        state_copy[3] = state_copy[2];
        state_copy[2] = state_copy[1];
        state_copy[1] = state_copy[0];
        state_copy[0] = temp1 + temp2;

		++i;
	}
	state->state[0] += state_copy[0]; // a
	state->state[1] += state_copy[1]; // b
	state->state[2] += state_copy[2]; // c
	state->state[3] += state_copy[3]; // d
	state->state[4] += state_copy[4]; // e
	state->state[5] += state_copy[5]; // f
	state->state[6] += state_copy[6]; // g
	state->state[7] += state_copy[7]; // h

	count++;
}
