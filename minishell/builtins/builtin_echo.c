/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 09:29:23 by ikhadem           #+#    #+#             */
/*   Updated: 2021/07/16 10:16:00 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static size_t	check_n(char **args)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (args[++j])
	{
		i = 0;
		if (args[j][i] == '-')
		{
			i++;
			while (args[j][i] != '\0')
			{
				if (args[j][i] != 'n')
					return (j);
				i++;
			}
		}
		else
			return (j);
	}
	return (j);
}

int	is_null_or_empty(char *str)
{
	if (str == NULL || str[0] == '\0')
		return (TRUE);
	return (FALSE);
}

int	builtin_echo(char **args)
{
	size_t	i;

	i = check_n(args);
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (is_null_or_empty(args[i]) != TRUE && args[i + 1])
			write(1, " ", 1);
		i++;
	}
	i = check_n(args);
	if (i == 1)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
