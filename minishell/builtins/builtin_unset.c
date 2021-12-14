/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 10:33:14 by ikhadem           #+#    #+#             */
/*   Updated: 2021/07/16 13:17:33 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	find_element(t_env *env, char *arg)
{
	while (env)
	{
		if (ft_strcmp(env->name, arg) == 0)
			return (TRUE);
		env = env->next;
	}
	return (FALSE);
}

/*
** @breif	: removes passed param from env
** @param	: l_env: reference to current env
			  args: params to remove
** @return	: exit status
*/

int	builtin_unset(t_env **l_env, char **args)
{
	size_t	i;

	i = 1;
	while (args[i])
	{
		if (find_element(*l_env, args[i]) == TRUE)
			env_delete_element_at(l_env, env_find_index(*l_env, args[i]));
		i++;
	}
	return (EXIT_SUCCESS);
}
