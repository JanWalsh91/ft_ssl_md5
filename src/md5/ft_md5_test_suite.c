/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_md5_test_suite.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 13:19:44 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/09 11:08:48 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_md5.h"

void	md5_test_suite(void)
{
	int		i;
	t_task	**tasks;

	ft_putstr("MD5 test suite:\n");
	if (!(tasks = (t_task**)ft_memalloc(sizeof(t_task**) * (MD5_TESTS + 1))))
		return ;
	i = -1;
	while (++i < MD5_TESTS)
		tasks = add_task(tasks, new_task(CMD_MD5, OPTION_S,
			md5_get_test_strings()[i]));
	i = -1;
	while (++i < MD5_TESTS)
	{
		ft_md5(tasks[i]);
		print_task_result(tasks[i], md5_get_result_strings()[i]);
		free_task(tasks[i]);
	}
	free(tasks);
}

char	**md5_get_test_strings(void)
{
	static char	*tests[9];

	tests[0] = "";
	tests[1] = "a";
	tests[2] = "abc";
	tests[3] = "message digest";
	tests[4] = "abcdefghijklmnopqrstuvwxyz";
	tests[5] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	tests[6] = "123456789012345678901234567890123456789012345678901234567890123"
				"45678901234567890";
	tests[7] = "MD5 has not yet (2001-09-03) been broken, but sufficient attack"
				"s have been made that its security is in some doubt";
	tests[8] = NULL;
	return (tests);
}

char	**md5_get_result_strings(void)
{
	static char	*result_strings[9] = {
		"d41d8cd98f00b204e9800998ecf8427e",
		"0cc175b9c0f1b6a831c399e269772661",
		"900150983cd24fb0d6963f7d28e17f72",
		"f96b697d7cb7938d525a2f31aaf161d0",
		"c3fcd3d76192e4007dfb496cca67e13b",
		"d174ab98d277d9f5a5611c2c9f419d9f",
		"57edf4a22be3c955ac49da2e2107b67a",
		"b50663f41d44d92171cb9976bc118538",
		NULL
	};

	return (result_strings);
}
