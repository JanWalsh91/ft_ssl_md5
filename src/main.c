/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 13:42:17 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/31 10:33:16 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_core.h"
#include "ft_ssl_helper_functions.h"

int	main(int ac, char **av)
{
	t_task		**tasks;
	int			i;


	// typedef union	u_test {
	// 	uint32_t	i;
	// 	unsigned char c[4];
	// }				t_test;

	// t_test test;
	// test.i = 0xff345678;

	// printf("i: %x\n", test.i);
	// printf("c: %x%x%x%x\n", test.c[0], test.c[1], test.c[2], test.c[3]);
	// printf("c[3]: %1$x, %1$c, %1$d, %1$u\n", test.c[3]);
	// printf("sizeof(t_test): %lu\n", sizeof(t_test));
	// test.c[3] = (char)0xff;
	// printf("c[3]: %1$x, %1$c, %1$d, %1$u\n", test.c[3]);

	// exit(0);
	if (ac <= 1)
	{
		print_usage();
		return (0);
	}
	tasks = handle_arguments(ac, av);
	if (!tasks)
	{
		printf("no tasks found\n");
		return (0);
	}
	print_tasks(tasks);
	i = 0;
	while (tasks[i])
		execute_task(tasks[i++]);
	return (0);
}
