/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_controle_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 10:07:45 by ikhadem           #+#    #+#             */
/*   Updated: 2021/07/16 13:27:47 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_controle.h"

/*
** @breif	: confirms whether an elemts is present inside the env
** @param	: env: current env
			  arg: the element to confirm
** @return	: True if exits False if not
*/

int	env_element_exits(t_env *env, char *arg)
{
	char	*name;
	size_t	i;
	size_t	size;

	size = ft_strlen(arg);
	i = corp_name(arg);
	if (i == size)
		return (FALSE);
	name = (char *)malloc(sizeof(char) * size);
	if (!name)
		return (FALSE);
	ft_strlcpy(name, arg, i + 1);
	while (env)
	{
		if (ft_strcmp(name, env->name) == 0)
		{
			free(name);
			return (TRUE);
		}
		env = env->next;
	}
	free(name);
	return (FALSE);
}

/*
** @breif	: replaces the given element in the env
** @param	: env: reference to current env
			  arg: the element to replace
** @return	: N/A
*/

void	env_replace_element(t_env **env, char *arg)
{
	char	*name;
	t_env	*iter;
	char	*value;
	size_t	i;
	size_t	size;

	size = ft_strlen(arg);
	i = corp_name(arg);
	iter = *env;
	if (i == size)
		return ;
	name = (char *)malloc(sizeof(char) * size);
	value = (char *)malloc(sizeof(char) * size);
	ft_strlcpy(name, arg, i + 1);
	ft_strlcpy(value, arg + i + 1, ft_strlen(arg + i));
	i = env_find_index(*env, name);
	while (i--)
		iter = iter->next;
	free(name);
	name = iter->value;
	iter->value = value;
	free(name);
}
