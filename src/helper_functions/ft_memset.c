/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 15:29:40 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/26 12:37:29 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** ft_memset writes len bytes of value c (converted to unsigned char)
** to the string b and returns b.
*/

#include "ft_ssl_helper_functions.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
		((char *)b)[i++] = (unsigned char)(c);
	return (b);
}
