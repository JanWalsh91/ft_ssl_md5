/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitwise_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 14:36:22 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/06 17:12:52 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_core.h"

uint32_t	rotate_left_32(uint32_t x, uint32_t n)
{
	return (((x) << (n)) | ((x) >> (32 - (n))));
}

uint32_t	rotate_right_32(uint32_t x, uint32_t n)
{
	return (((x) >> (n)) | ((x) << (32 - (n))));
}

uint64_t	rotate_left_64(uint64_t x, uint64_t n)
{
	return (((x) << (n)) | ((x) >> (64 - (n))));
}

uint64_t	rotate_right_64(uint64_t x, uint64_t n)
{
	return (((x) >> (n)) | ((x) << (64 - (n))));
}

/*
** Reverses the order of 'batch_size' bytes at a time 'len' times
** Stored result in output.
** Batch_size must be a multiple of 2.
*/

void		byte_swap(void *output, void *input, size_t batch_size, size_t len)
{
	uint8_t	*input_p;
	uint8_t	*output_p;
	size_t	len_i;
	size_t	batch_size_i;

	input_p = (uint8_t *)input;
	output_p = (uint8_t *)output;
	if (batch_size % 2 != 0)
	{
		ft_putstr("batch_size must be even number\n");
		return ;
	}
	len_i = -1;
	while (++len_i < len)
	{
		batch_size_i = -1;
		while (++batch_size_i < batch_size)
		{
			output_p[len_i * batch_size + batch_size_i] =
				input_p[(len_i + 1) * batch_size - batch_size_i - 1];
		}
	}
}
