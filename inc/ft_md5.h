/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:43:42 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/26 15:46:12 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

# include "ft_ssl_core.h"
# include "ft_ssl_helper_functions.h"

typedef	struct	s_md5_buffers
{
	int		A;
	int		B;
	int		C;
	int		D;
}				t_md5_buffers;

void	ft_md5(t_task *task);
int		md5_f(int x, int y, int z);


#endif