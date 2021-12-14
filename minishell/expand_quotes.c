/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 14:06:41 by yait-kad          #+#    #+#             */
/*   Updated: 2021/07/14 14:06:43 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_double_quotes(char **str, int index, t_env *env_list)
{
	while ((*str)[index] != '\0')
	{
		if ((*str)[index] == '\\')
		{
			if (ft_strchr("\\`$\"", (*str)[index + 1]) != NULL)
			{
				ft_new_str((*str), index);
			}
		}
		else if ((*str)[index] == '$' &&
			(ft_strchr("\" \t", (*str)[index + 1]) == NULL))
			(*str) = take_dollar_name((*str), &index, env_list, 3);
		if ((*str)[index] == '"')
		{
			ft_new_str((*str), index);
			index--;
			break ;
		}
		index++;
	}
	return (index);
}

int	expand_single_quote(char *str, int index)
{
	while (str[index] != '\0')
	{
		if (str[index] == '\'')
		{
			ft_new_str(str, index);
			index--;
			break ;
		}
		index++;
	}
	return (index);
}

char	*get_dollar_name(char *command, int *j)
{
	char	*name;
	char	*ptr;
	char	*tmp;
	int		i;

	i = *j;
	name = ft_strdup("");
	while (command[i] != '\0' && (ft_isalnum(command[i]) == 1 \
	|| command[i] == '_'))
	{
		ptr = ft_substr(command, i, 1);
		tmp = ft_strjoin(name, ptr);
		free(name);
		name = tmp;
		free(ptr);
		i++;
	}
	*j = i;
	return (name);
}

char	*after_dollar_value(char *command1, int i)
{
	char	*after_dollar;
	int		j;
	int		start;

	j = 0;
	start = i;
	while (command1[i++] != '\0')
		j++;
	after_dollar = ft_substr(command1, start, j);
	return (after_dollar);
}
