/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_controle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 11:06:17 by ikhadem           #+#    #+#             */
/*   Updated: 2021/07/16 13:30:33 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_controle.h"

static size_t	count_env_elements(t_env *env)
{
	size_t	i;
	t_env	*iter;

	i = 0;
	iter = env;
	while (iter)
	{
		i++;
		iter = iter->next;
	}
	return (i);
}

/*
** @breif	: prints the envirenment
** @param	: env: current env
** @return	: N/A
*/

void	print_t_env(t_env *env)
{
	t_env	*iter;

	iter = env;
	while (iter)
	{
		if (iter->value[0] != 0)
			printf("%s=%s\n", iter->name, iter->value);
		iter = iter->next;
	}
}

/*
** @breif	: transforms the env to a 2d array
** @param	: env: current env
** @return	: 2d array holding all the data of the env
*/

char	**env_from_t_env_to_2d_array(t_env *env)
{
	char	**res;
	size_t	size;
	t_env	*iter;
	char	*tmp;

	size = count_env_elements(env);
	res = (char **)malloc(sizeof(char *) * (size + 1));
	if (!res)
		return (NULL);
	res[size] = NULL;
	size = 0;
	iter = env;
	while (iter)
	{
		tmp = ft_strjoin(iter->name, "=");
		res[size] = ft_strjoin(tmp, iter->value);
		size++;
		free(tmp);
		iter = iter->next;
	}
	return (res);
}

/*
** @breif	: returns the value of a certain element in the env
** @param	: env: current env
			  key" the key witch ae are looking for
** @return	: the new char * holding the value
*/

char	*env_find(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strcmp(key, env->name) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

/*
** @breif	: frees 2d array
** @param	: arr: reference to the double pointer array
** @return	: N/A
*/

void	free_2d_array(char ***arr)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = *arr;
	while (tmp[i] != NULL)
	{
		if (tmp[i])
			free(tmp[i]);
	}
	free(tmp);
}
