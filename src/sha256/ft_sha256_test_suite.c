/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha256_test_suite.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 13:19:44 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/06 14:36:45 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha256.h"

void	sha256_test_suite(void)
{
	int		i;
	t_task	**tasks;

	ft_putstr("sha256 test suite:\n");
	if (!(tasks = (t_task**)ft_memalloc(sizeof(t_task**) * (SHA256_TESTS + 1))))
		return ;
	i = -1;
	while (++i < SHA256_TESTS)
		tasks = add_task(tasks, new_task(CMD_SHA256, OPTION_S,
			sha256_get_test_strings()[i]));
	i = -1;
	while (++i < SHA256_TESTS)
	{
		ft_sha256(tasks[i]);
		print_task_result(tasks[i], sha256_get_result_strings()[i]);
		free_task(tasks[i]);
	}
	free(tasks);
}

char	**sha256_get_test_strings(void)
{
	static char	*tests[] = 
	{
		"",
		"a",
		"abc",
		"message digest",
		"abcdefghijklmnopqrstuvwxyz",
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789",
		"1234567890123456789012345678901234567890123456789012345678901234567890\
1234567890",
		"sha256 has not yet (2001-09-03) been broken, but sufficient attacks have \
been made that its security is in some doubt",
		NULL
	};
	return (tests);
}

char	**sha256_get_result_strings(void)
{
	static char	*result_strings[] = 
	{
		"e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855",
		"ca978112ca1bbdcafac231b39a23dc4da786eff8147c4e72b9807785afee48bb",
		"ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad",
		"f7846f55cf23e14eebeab5b4e1550cad5b509e3348fbc4efa3a1413d393cb650",
		"71c480df93d6ae2f1efad1447c66c9525e316218cf51fc8d9ed832f2daf18b73",
		"db4bfcbd4da0cd85a60c3c37d3fbd8805c77f15fc6b1fdfe614ee0a7c8fdb4c0",
		"f371bc4a311f2b009eef952dd83ca80e2b60026c8e935592d0f9c308453c813e",
		"456be9a79fe35a3027c4363aac858524f6b6f40a2bf56b0342b998010e6a4c41"
	};
	return (result_strings);
}
