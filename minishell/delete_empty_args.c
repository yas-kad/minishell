/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_empty_args.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/17 08:45:27 by yait-kad          #+#    #+#             */
/*   Updated: 2021/07/17 08:45:48 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_empty(char ***args)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while ((*args)[i] != NULL)
	{
		if (ft_strcmp((*args)[i], "") == 0)
		{
			j = i;
			tmp = (*args)[i];
			while ((*args)[j] != NULL)
			{
				(*args)[j] = (*args)[j + 1];
				j++;
			}
			free(tmp);
		}
		i++;
	}
}
