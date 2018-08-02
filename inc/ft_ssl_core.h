/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_core.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 12:21:51 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/02 13:04:20 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_CORE_H
# define FT_SSL_CORE_H

# include <stdio.h> ///////////
# include <stdlib.h>
# include <stdint.h>
# include <errno.h>
# include <string.h>

#include "ft_ssl_helper_functions.h"

typedef enum	e_option {
	OPTION_S		= 0b00000001,
	OPTION_P		= 0b00000010,
	OPTION_Q		= 0b00000100,
	OPTION_R		= 0b00001000,
	OPTION_STDIN	= 0b00010000,
	OPTION_INVALID	= 0b10000000,
	OPTION_NOT		= 0b01000000
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
	char		*digest;
	char		error[512];
}				t_task;

/*
** Print messages
*/

void		print_usage();
void		print_commands();
int			show_error_message(t_task *task);

/*
** Parsing
*/

t_task		**handle_arguments();
t_task	**handle_options(t_task **tasks, t_command command, char **av);
t_task	**handle_p_opt(t_task **tasks, t_command command, int8_t *options);
t_command	parse_command(char *arg);
t_option	parse_option(char *arg);
void		read_from_stdin();

/*
** Task manager
*/

t_task		*new_task(t_command cmd, int8_t opts, char *str);
t_task		**add_task(t_task **tasks, t_task *task);
void		print_tasks(t_task **tasks);
void		execute_task(t_task *task);
void		print_task_result(t_task *task);
void		print_task_name(t_task *task);
void		free_task(t_task *task);

/*
** Bitwise operations
*/

uint32_t	rotate_left(uint32_t x, uint32_t n);
uint32_t	rotate_right(uint32_t x, uint32_t n);
void    	byte_swap(void *output, void *input, size_t batch_size, size_t len);

/*
** Globals: commands and options
*/

static const char *const	g_commands[] = {
	"md5",
	"sha256",
	NULL
};

static const char *const	g_options[] = {
	"-s",
	"-p",
	"-q",
	"-r",
	NULL
};

#endif
