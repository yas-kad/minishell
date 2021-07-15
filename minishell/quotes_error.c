/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 11:35:46 by yait-kad          #+#    #+#             */
/*   Updated: 2021/07/14 11:35:48 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quotes_end(char *value, int *k)
{
	int	backslash;
	int	j;

	j = *k;
	j++;
	backslash = 0;
	while (value[j] != '\0' && value[j] != '"')
	{
		if (value[j] == '\\')
		{
			backslash = check_backslash(value, j);
			if (backslash % 2 != 0)
				j = j + backslash;
			else
				j = j + backslash - 1;
			backslash = 0;
		}
		j++;
	}
	*k = j;
	if (value[j] == '"')
		return (1);
	else
		return (-1);
}

int	single_quote_end(char *value, int *k)
{
	int	j;

	j = *k;
	j++;
	while (value[j] != '\0' && value[j] != '\'')
		j++;
	*k = j;
	if (value[j] == '\'')
		return (1);
	else
		return (-1);
}

int	check_quotes(char *value)
{
	int	j;
	int	backslash;
	int	result;

	j = 0;
	backslash = 0;
	result = 0;
	while (value[j])
	{
		if (value[j] == '\"')
		{
			result = quotes_end(value, &j);
		}
		else if (value[j] == '\'')
		{
			result = single_quote_end(value, &j);
		}
		else if (value[j] == '\\')
		{
			if (check_backslash(value, j) % 2 != 0)
				j++;
		}
		j++;
	}
	return (result);
}
