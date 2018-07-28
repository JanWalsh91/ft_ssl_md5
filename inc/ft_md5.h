/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/26 14:43:42 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/28 16:23:50 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MD5_H
# define FT_MD5_H

# include <math.h>
# include <fcntl.h>
# include <unistd.h>

# include "ft_ssl_core.h"
# include "ft_ssl_helper_functions.h"

# define BUFFER_SIZE 64

typedef	struct	s_md5_state
{
	uint32_t		state[4];
	unsigned char	buf[BUFFER_SIZE * 2 + 1];
	int				ret;
	uint64_t		length;
}				t_md5_state;

void			ft_md5(t_task *task);
t_md5_state		*md5_init_state(void);
void			md5_update_state(t_md5_state *state);
t_md5_state		*md5_pad(t_md5_state *state);


// helper functions
uint32_t	md5_f(uint32_t x, uint32_t y, uint32_t z);
uint32_t	md5_g(uint32_t x, uint32_t y, uint32_t z);
uint32_t	md5_h(uint32_t x, uint32_t y, uint32_t z);
uint32_t	md5_i(uint32_t x, uint32_t y, uint32_t z);

// TODO: may need 64
uint32_t				g_md5_t[64];

static const uint32_t	g_md5_s[4][4] = {
	{7, 12, 17, 22},
	{5, 9, 14, 20},
	{4, 11, 16, 23},
	{6, 10, 15, 21}
};

#endif