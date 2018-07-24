/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 13:42:17 by jwalsh            #+#    #+#             */
/*   Updated: 2018/07/24 11:09:55 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
		

	if (ac == 1)
		print_usage();

	if (ac > 1)
	{
		ft_putstr("arg: ");
		ft_putstr(av[1]);
		ft_putstr("\n");
	}

	if (ac > 3 && ft_strcmp(ac[2], "md5")
	{
		ft_putstr("md5\n")
		ft_md5(av[2]);
	}

	return (0);	
}
