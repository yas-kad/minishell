/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:37:02 by ikhadem           #+#    #+#             */
/*   Updated: 2021/07/16 10:18:17 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int count_args(char **args)
{
	int		res;

	res = 0;
	while (args[res])
		res++;
	return (res);
}

int	builtin_exit(char **args)
{
	if (count_args(args) > 2)
		printf("exit: too many arguments");
	else if (count_args(args) < 2)
		exit (0);
	else exit (ft_atoi(args[1]));
	return (EXIT_FAILURE);
}
