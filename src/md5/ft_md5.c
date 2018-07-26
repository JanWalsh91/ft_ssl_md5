/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:46:57 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/26 16:02:41 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"

void	ft_md5(t_task *task)
{
	printf("ft_md5\n");
	(void)task;
	t_md5_buffers *buf;

	if (!(buf = (t_md5_buffers *)ft_memalloc(sizeof(t_md5_buffers))))
		return ;
	buf->A = 0x67452301;
	buf->B = 0xefcdab89;
	buf->C = 0x98badcfe;
	buf->D = 0x10325476;
}

int		md5_f(int x, int y, int z)
{
	return ((x & y) | (~x & z));
}

int		md5_g(int x, int y, int z)
{
	return ((x & z) | (y & ~z));
}

int		md5_h(int x, int y, int z)
{
	return (x ^ y ^ z);
}

int		md5_i(int x, int y, int z)
{
	return (y ^ (x | ~z));
}

