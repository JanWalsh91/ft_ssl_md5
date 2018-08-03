/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bytetohex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 13:02:21 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/03 11:34:58 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_helper_functions.h"

/*
** Returns a string representing bytes in hex format at address addr of len
** bytes.
*/

char	*ft_bytetohex(void *addr, size_t len)
{
	uint8_t	*p;
	int		i;
	char	*result;

	if (!(result = (char *)ft_memalloc(len * 2 + 1)))
		return (NULL);
	p = (uint8_t *)addr;
	i = -1;
	while (++i < (int)len)
	{
		result[i * 2] = (*p / 16) < 10 ? (*p / 16) + '0' : (*p / 16) + 'a' - 10;
		result[i * 2 + 1] = (*p % 16) < 10 ? (*p % 16) + '0' : (*p % 16) + 'a'
			- 10;
		++p;
	}
	return (result);
}
