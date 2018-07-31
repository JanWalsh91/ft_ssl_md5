/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 14:50:36 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/31 16:47:49 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Convert a lower-case letter to the corresponding upper-case letter.
** Otherwise, the argument is returned unchanged.
*/

#include "ft_ssl_helper_functions.h"

int	ft_toupper(int c)
{
	if (ft_islower(c))
		c -= 32;
	return (c);
}
