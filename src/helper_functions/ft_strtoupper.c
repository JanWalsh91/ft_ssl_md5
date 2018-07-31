/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoupper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 18:39:37 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/31 16:47:43 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
** Puts the lowercase chars in a char string to uppercase.
*/

#include "ft_ssl_helper_functions.h"

void	ft_strtoupper(char *s)
{
	int	i;

	i = -1;
	while (s && s[++i])
		ft_islower(s[i]) ? s[i] = ft_toupper(s[i]) : 0;
}
