/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set_controle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 12:52:35 by ikhadem           #+#    #+#             */
/*   Updated: 2021/07/16 17:22:06 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_controle.h"
#include "../libft/libft.h"

/*
** @breif	: returns the index to a certain value
** @param	: env: current env
			  value: the desired value
** @return	: index in env of that value
*/

size_t	env_find_index(t_env *env, char *value)
{
	t_env	*iter;
	size_t	res;

	iter = env;
	res = 0;
	while (iter)
	{
		if (ft_strcmp(iter->name, value) == 0)
			return (res);
		res++;
		iter = iter->next;
	}
	return (INDEX_NOT_FOUND);
}

/*
** @breif	: returns the index of the first occurence of =
** @param	: str: string on witch we want the =
** @return	: the index of the = sign
*/

size_t	corp_name(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	return (i);
}

/*
** @breif	: adds the given arg to the current env
** @param	: env: reference to the env
			  arg: variable to add to env
** @return	: N/A
*/

static void	alloc_data(t_env **data, size_t size)
{
	t_env *new = *data;

	new->next = NULL;
	new->name = (char *)malloc(sizeof(char) * size);
	new->value = (char *)malloc(sizeof(char) * size);
}

void	env_add_element(t_env **env, char *arg)
{
	t_env	*new;
	t_env	*iter;
	size_t	i;
	size_t	size;

	size = ft_strlen(arg);
	iter = *env;
	i = corp_name(arg);
	if (arg[i] == '=' && arg[i - 1] == '+')
		return ;
	new = (t_env *)malloc(sizeof(t_env));
	alloc_data(&new, size);
	ft_strlcpy(new->name, arg, i + 1);
	if (i < size)
		ft_strlcpy(new->value, arg + i + 1, ft_strlen(arg + i));
	else
		new->value[0] = 0;
	if (*env == NULL)
		*env = new;
	else
	{
		while (iter->next != NULL)
			iter = iter->next;
		iter->next = new;
	}
}

/*
** @breif	: removes element at index from env
** @param	: env: reference to the env
			  index: index of the element to remove
** @return	: N/A
*/

void	env_delete_element_at(t_env **env, size_t index)
{
	t_env	*iter;
	t_env	*prev;

	iter = *env;
	prev = NULL;
	while (index--)
	{
		prev = iter;
		iter = iter->next;
	}
	if (prev)
		prev->next = iter->next;
	else
		*env = iter->next;
	free(iter->name);
	free(iter->value);
	free(iter);
	iter = NULL;
}
