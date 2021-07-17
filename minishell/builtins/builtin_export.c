/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 15:29:14 by ikhadem           #+#    #+#             */
/*   Updated: 2021/07/17 08:01:32 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void	export_display(t_env *env)
{
	t_env	*iter;

	iter = env;
	while (iter)
	{
		if (ft_strcmp(iter->name, "_") != 0)
		{
			if (iter->value != NULL)
				printf("declare -x %s=\"%s\"\n", iter->name, iter->value);
			else
				printf("declare -x %s\n", iter->name);
		}
		iter = iter->next;
	}
}

/*
** @breif	: inserts passed arguments to the env
**				if no arguments are passed displays the env
** @param	: env: reference to current env
			  args: arguments passed
** @return	: exit status
*/

int	builtin_export(t_env **env, char **args)
{
	size_t	i;

	i = 1;
	if (!args[1])
		export_display(*env);
	else
	{
		while (args[i])
		{
			if (ft_strcmp(args[i], "+=") == 0)
				printf("export: `+=': not a valid identifier\n");
			else if (env_element_exits(*env, args[i]) == FALSE)
				env_add_element(env, args[i]);
			else
				env_replace_element(env, args[i]);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}
