/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_parce.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 19:31:59 by yait-kad          #+#    #+#             */
/*   Updated: 2021/07/15 19:32:00 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tab_size(char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i] != NULL)
		i++;
	return (i);
}

void	create_cmd(t_parce *var)
{
	int	i;

	i = 0;
	if ((*var).cmd != NULL)
	{
		add_cmd((*var).cmd, (*var).cmd_arg, (*var).redirection,
			(*var).current_token->type);
		free((*var).cmd_arg);
		(*var).cmd_arg = NULL;
		(*var).redirection = NULL;
	}
	else
	{
		(*var).cmd = initial_cmd((*var).cmd_arg, (*var).redirection,
				(*var).current_token->type);
		while (i < (*var).size)
		{
			free((*var).cmd_arg[i]);
			i++;
		}
		free((*var).cmd_arg);
		(*var).cmd_arg = NULL;
		(*var).redirection = NULL;
	}
}
