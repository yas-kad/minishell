/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_controle_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 10:07:45 by ikhadem           #+#    #+#             */
/*   Updated: 2021/07/16 17:19:55 by ikhadem          ###   ########.fr       */
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
	name = (char *)malloc(sizeof(char) * size);
	if (arg[i] == '=' && arg[i - 1] == '+')
		ft_strlcpy(name, arg, i);
	else
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

size_t	count_env(t_env *env)
{
	size_t	res;

	res = 0;
	while (env)
	{
		res++;
		env = env->next;
	}
	return (res);
}

static void	join_values(t_env **env, size_t size, size_t pos, char *arg)
{
	char	*name;
	char	*value;
	t_env	*iter;
	size_t	i;

	iter = *env;
	name = (char *)malloc(sizeof(char) * size);
	value = (char *)malloc(sizeof(char) * size);
	ft_strlcpy(value, arg + pos + 1, ft_strlen(arg + pos));
	ft_strlcpy(name, arg, pos);
	i = env_find_index(*env, name);
	free(name);
	if (i < count_env(*env))
	{
		while (i--)
			iter = iter->next;
		name = ft_strjoin(iter->value, value);
		free(value);
		free(iter->value);
		iter->value = name;
	}
}

static void	set_new_value(t_env **env, size_t size, size_t pos, char *arg)
{
	char	*name;
	char	*value;
	t_env	*iter;
	size_t	i;

	iter = *env;
	name = (char *)malloc(sizeof(char) * size);
	value = (char *)malloc(sizeof(char) * size);
	ft_strlcpy(value, arg + pos + 1, ft_strlen(arg + pos));
	ft_strlcpy(name, arg, pos + 1);
	i = env_find_index(*env, name);
	if (i < count_env(*env))
		while (i--)
			iter = iter->next;
	free(name);
	if (i < count_env(*env))
	{
		name = iter->value;
		iter->value = value;
		free(name);
	}
}

/*
** @breif	: replaces the given element in the env
** @param	: env: reference to current env
			  arg: the element to replace
** @return	: N/A
*/

void	env_replace_element(t_env **env, char *arg)
{
	size_t	i;
	size_t	size;

	size = ft_strlen(arg);
	i = corp_name(arg);
	if (arg[i] == '=' && arg[i - 1] == '+')
		join_values(env, size, i, arg);
	else
		set_new_value(env, size, i, arg);
}
