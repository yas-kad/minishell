/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_controle_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 10:07:45 by ikhadem           #+#    #+#             */
/*   Updated: 2021/07/15 15:00:26 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_controle.h"

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
