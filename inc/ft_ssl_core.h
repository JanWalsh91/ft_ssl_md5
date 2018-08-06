/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_core.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/25 12:21:51 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/06 17:14:47 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_CORE_H
# define FT_SSL_CORE_H

# include <stdlib.h>
# include <stdint.h>
# include <errno.h>
# include <string.h>

# include "ft_ssl_helper_functions.h"

typedef enum				e_option {
	OPTION_S		= 0b000000001,
	OPTION_P		= 0b000000010,
	OPTION_Q		= 0b000000100,
	OPTION_R		= 0b000001000,
	OPTION_X		= 0b000010000,
	OPTION_STDIN	= 0b001000000,
	OPTION_INVALID	= 0b010000000,
	OPTION_NOT		= 0b100000000
}							t_option;

typedef enum				e_command {
	CMD_MD5,
	CMD_SHA256,
	CMD_SHA512,
	CMD_INVALID
}							t_command;

typedef struct				s_task {
	t_command				cmd;
	int16_t					opts;
	char					*str;
	char					*file;
	char					*digest;
	char					error[512];
}							t_task;

typedef void(*t_task_executor)(t_task *);

/*
** Print messages
*/

void						print_usage(void);
void						print_commands(void);
int							show_error_message(t_task *task);

/*
** Parsing
*/

t_task						**handle_arguments(int ac, char **av);
t_task						**handle_options(t_task **tasks, t_command command,
								char **av);
t_task						**handle_px_opts(t_task **tasks, t_command command,
								int16_t *options);
t_command					parse_command(char *arg);
t_option					parse_option(char *arg);
void						read_from_stdin(void);

/*
** Task manager
*/

t_task						*new_task(t_command cmd, int16_t opts, char *str);
int							invalid_cmd_opt(t_task *task, char *str);
t_task						**add_task(t_task **tasks, t_task *task);
void						print_task_result(t_task *task, char *verify);
void						print_task_name(t_task *task);
void						free_task(t_task *task);
void						init_task_result_names(char commands[3][64]);
void						verify_task_result(t_task *task, char *verify);

/*
** Bitwise operations
*/

uint32_t					rotate_left_32(uint32_t x, uint32_t n);
uint32_t					rotate_right_32(uint32_t x, uint32_t n);
uint64_t					rotate_left_64(uint64_t x, uint64_t n);
uint64_t					rotate_right_64(uint64_t x, uint64_t n);
void						byte_swap(void *output, void *input,
								size_t batch_size, size_t len);

/*
** Globals: commands and options
*/

static const char *const	g_commands[] = {
	"md5",
	"sha256",
	"sha512",
	NULL
};

static const char *const	g_options[] = {
	"-s",
	"-p",
	"-q",
	"-r",
	"-x",
	NULL
};

#endif
