/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 17:22:15 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/31 16:03:56 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Copies the string src to dst, including the null-terminating character.
** src and dst should not overlap, as behavior is undefined.
*/

char	*ft_strcpy(char *dst, const char *src)
{
	int				i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = src[i];
	return (dst);
}
