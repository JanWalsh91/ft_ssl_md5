/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 13:59:26 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/25 15:27:06 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Writes the character c to standard output.
*/

#include "ft_ssl_helper_functions.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
