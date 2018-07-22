/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 14:01:33 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/22 15:44:23 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Writes the string s to the standard output.
*/

#include "helper_functions.h"

void	ft_putstr(char const *s)
{
	write(1, s, ft_strlen(s));
}
