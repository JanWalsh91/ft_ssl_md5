/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_core.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 12:21:51 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/25 17:05:59 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_CORE_H
# define FT_SSL_CORE_H

# include <stdio.h> ///////////
# include <stdlib.h>
# include <stdint.h>

typedef enum	e_option {
	OPTION_S = 0b00000001,
	OPTION_P = 0b00000010,
	OPTION_Q = 0b00000100,
	OPTION_R = 0b00001000,
	OPTION_INVALID = 0b10000000
	// OPTION_ILLEGAL or return 0...
}				t_option;

typedef enum	e_command {
	CMD_MD5,
	CMD_SHA256,
	CMD_INVALID
}				t_command;

typedef struct	s_task {
	t_command	cmd;
	int8_t		opts;
	char		*str;
	char		*file;
}				t_task;

/*
** Parsing
*/

void		handle_arguments();
t_command	parse_command(char *arg);
t_option	parse_option(char *arg);
void		read_from_stdin();

/*
** Task manager
*/

t_task		*new_task(t_command cmd, int8_t opts, char *str);

#endif
