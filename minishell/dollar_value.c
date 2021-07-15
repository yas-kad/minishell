/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 13:59:45 by yait-kad          #+#    #+#             */
/*   Updated: 2021/07/14 13:59:48 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_name(char *comd, int *k, char type)
{
	int	i;

	i = *k;
	while (comd[i] != '\0')
	{
		if (comd[i] == type)
		{
			ft_new_str((comd), i);
			i--;
			break ;
		}
		i++;
	}
	*k = i;
}

void	dollar_zero(char **comd, char *old_comd, size_t *k)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(old_comd) + ft_strlen("My_Minishell");
	tmp = ft_strjoin(old_comd, "My_Minishell");
	free(*(comd));
	*(comd) = tmp;
	*k = len;
}

void	dollar_q(char **comd, char *old_comd, size_t *k)
{
	size_t	len;
	char	*str;
	char	*tmp;

	str = ft_itoa(g_dollar_question);
	g_dollar_question = 0;
	len = ft_strlen(old_comd) + ft_strlen(str);
	tmp = ft_strjoin(old_comd, str);
	free((*comd));
	(*comd) = tmp;
	*k = len;
}

size_t	dollar_val(char **comd, char *name, char *old_comd, t_env *envl)
{
	char	*tmp;
	int		len;

	len = 0;
	while (envl != NULL)
	{
		if (ft_strcmp(name, envl->name) == 0)
		{
			len = ft_strlen(old_comd) + ft_strlen(envl->value);
			tmp = ft_strjoin(old_comd, envl->value);
			free(*(comd));
			*(comd) = tmp;
			break ;
		}
		else
		{
			len = ft_strlen(old_comd);
			tmp = ft_strjoin(old_comd, "");
			free(*(comd));
			*(comd) = tmp;
		}
		envl = envl->next;
	}
	return (len);
}

void	name_empty(char **comd, char *old_comd, size_t *k)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(old_comd);
	tmp = ft_strjoin(old_comd, "");
	free(*(comd));
	*(comd) = tmp;
	*k = len;
}
