/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 19:19:46 by yait-kad          #+#    #+#             */
/*   Updated: 2021/07/11 19:19:50 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_backslash_end(char *value)
{
	int	backslash;
	int	i;

	backslash = 0;
	i = 0;
	while (value[i] != '\0')
	{
		while (value[i] == '\\')
		{
			backslash++;
			i++;
		}
		if (value[i] == '\0')
			return (backslash);
		else
			backslash = 0;
		i++;
	}
	return (backslash);
}

int	check_backslash(char *line, int i)
{
	int	backslash;

	backslash = 0;
	while (line[i++] == '\\')
	{
		backslash++;
	}
	return (backslash);
}

void	backslash_impair(char *line, char **token, int *k, int *backslash)
{
	char	*str;
	int		i;
	char	*tmp;

	i = *k;
	str = ft_substr(line, i, *(backslash) + 1);
	tmp = ft_strjoin((*token), str);
	free((*token));
	free(str);
	(*token) = tmp;
	i = i + *(backslash);
	*(backslash) = 0;
	*k = i;
}

void	backslash_exist(char *line, char **token, int *k, int *backslash)
{
	char	*str;
	int		i;
	char	*tmp;

	i = *k;
	str = ft_substr(line, i, *(backslash));
	tmp = ft_strjoin(*(token), str);
	free(*(token));
	free(str);
	(*token) = tmp;
	i = i + *(backslash) - 1;
	*(backslash) = 0;
	*k = i;
}

void	backslash_not_exist(char *line, char **token, int *k)
{
	char	*str;
	int		i;
	char	*tmp;

	i = *k;
	str = ft_substr(line, i, 1);
	tmp = ft_strjoin(*(token), str);
	free(*(token));
	free(str);
	(*token) = tmp;
	*k = i;
}
