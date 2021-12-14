/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:15:27 by yait-kad          #+#    #+#             */
/*   Updated: 2021/04/16 15:15:30 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*initial_env_node(char *name, char *value)
{
	t_env	*first_env_node;

	first_env_node = (t_env *)malloc(sizeof(t_env));
	first_env_node->name = name;
	first_env_node->value = value;
	first_env_node->next = NULL;
	return (first_env_node);
}

void	add_env_node(t_env *env_l, char *name, char *value)
{
	t_env	*new_env;

	new_env = env_l;
	while (new_env->next != NULL)
		new_env = new_env->next;
	new_env->next = malloc(sizeof(t_env));
	new_env->next->name = name;
	new_env->next->value = value;
	new_env->next->next = NULL;
}

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_env(t_env *lenv)
{
	t_env	*curr_list;

	curr_list = lenv;
	while (curr_list)
	{
		free(curr_list->name);
		free(curr_list->value);
		curr_list = curr_list->next;
	}
	free(curr_list);
}

t_env	*create_env_list(t_env *l_env, char **env)
{
	char	**str;
	int		i;

	i = 0;
	l_env = NULL;
	if (env[i])
	{
		str = my_split(env[i]);
		l_env = initial_env_node(str[0], str[1]);
		i++;
		free(str);
	}
	while (env[i])
	{
		str = my_split(env[i]);
		add_env_node(l_env, str[0], str[1]);
		free(str);
		i++;
	}
	return (l_env);
}
