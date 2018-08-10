/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 17:18:09 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/09 11:43:24 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Allocates memory for and returns a string of size size,
** with all characters initilized at \0.
** Returns NULL if allocation fails.
*/

#include "ft_ssl_helper_functions.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	if (!(str = ft_memalloc(size + 1)))
		return (NULL);
	ft_bzero(str, size);
	return (str);
}
