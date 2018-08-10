/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sha512_test_suite.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 13:19:44 by jwalsh            #+#    #+#             */
/*   Updated: 2018/08/09 11:14:10 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_sha512.h"

void		sha512_test_suite(void)
{
	int		i;
	t_task	**tasks;

	ft_putstr("sha512 test suite:\n");
	if (!(tasks = (t_task**)ft_memalloc(sizeof(t_task**) * (SHA512_TESTS + 1))))
		return ;
	i = -1;
	while (++i < SHA512_TESTS)
		tasks = add_task(tasks, new_task(CMD_SHA512, OPTION_S,
			sha512_get_test_strings()[i]));
	i = -1;
	while (++i < SHA512_TESTS)
	{
		ft_sha512(tasks[i]);
		print_task_result(tasks[i], sha512_get_result_strings()[i]);
		free_task(tasks[i]);
	}
	free(tasks);
}

char		**sha512_get_test_strings(void)
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
	tests[7] = "sha512 has not yet (2001-09-03) been broken, but sufficient att"
				"acks have been made that its security is in some doubt";
	tests[8] = NULL;
	return (tests);
}

static char	**sha512_get_result_strings2(char *result_strings[9])
{
	result_strings[5] = "1e07be23c26a86ea37ea810c8ec7809352515a970e9253c26f536c"
							"fc7a9996c45c8370583e0a78fa4a90041d71a4ceab7423f19c"
							"71b9d5a3e01249f0bebd5894";
	result_strings[6] = "72ec1ef1124a45b047e8b7c75a932195135bb61de24ec0d1914042"
							"246e0aec3a2354e093d76f3048b456764346900cb130d2a4fd"
							"5dd16abb5e30bcb850dee843";
	result_strings[7] = "d928c12d26d1d0a52920f00a5b89e4cc7374022fb22d2f3e284156"
							"34636020e1a38e5e0028440718ff98a37ecf727e4d84d7f42c"
							"1d8bccded65afd49a43a6acd";
	result_strings[8] = NULL;
	return (result_strings);
}

char		**sha512_get_result_strings(void)
{
	static char	*result_strings[9];

	result_strings[0] = "cf83e1357eefb8bdf1542850d66d8007d620e4050b5715dc83f4a9"
							"21d36ce9ce47d0d13c5d85f2b0ff8318d2877eec2f63b931bd"
							"47417a81a538327af927da3e";
	result_strings[1] = "1f40fc92da241694750979ee6cf582f2d5d7d28e18335de05abc54"
							"d0560e0f5302860c652bf08d560252aa5e74210546f369fbbb"
							"ce8c12cfc7957b2652fe9a75";
	result_strings[2] = "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eee"
							"e64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423"
							"643ce80e2a9ac94fa54ca49f";
	result_strings[3] = "107dbf389d9e9f71a3a95f6c055b9251bc5268c2be16d6c13492ea"
							"45b0199f3309e16455ab1e96118e8a905d5597b72038ddb372"
							"a89826046de66687bb420e7c";
	result_strings[4] = "4dbff86cc2ca1bae1e16468a05cb9881c97f1753bce3619034898f"
							"aa1aabe429955a1bf8ec483d7421fe3c1646613a59ed5441fb"
							"0f321389f77f48a879c7b1f1";
	return (sha512_get_result_strings2(result_strings));
}
