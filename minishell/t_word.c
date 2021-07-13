/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_word.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 19:20:32 by yait-kad          #+#    #+#             */
/*   Updated: 2021/07/11 19:20:38 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*Treat_Quotes(int *index, char *line, char type)
{
	char	*Double_Quote;
	int		backslash;
	int		j;
	int		i;

	i = *index;
	j = i;
	j++;
	while (line[j] != '\0' && line[j] != type)
	{
		if (line[j] == '\\')
		{
			backslash = check_backslash(line, j);
			if (backslash % 2 != 0)
				j = j + backslash;
			else
				j = j + backslash - 1;
			backslash = 0;
		}
		j++;
	}
	Double_Quote = ft_substr(line, i, (j - i + 1));
	*index = j;
	return (Double_Quote);
}

void	quotes(char **token, int *k, char *line, char type)
{
	char	*trt;
	char	*tmp;
	int		i;

	i = *k;
	trt = Treat_Quotes(&i, line, type);
	tmp = ft_strjoin(*(token), trt);
	free(*(token));
	*(token) = tmp;
	free(trt);
	*k = i;
}

char	*get_word(char *line, int *k)
{
	char	*token;
	int		backslash;
	int		i;

	token = ft_strdup("");
	backslash = 0;
	i = *k;
	while ((line[i] != '\0') && (ft_strchr("|;> <\t", line[i]) == NULL))
	{
		backslash = check_backslash(line, i);
		if (backslash % 2 != 0)
			backslash_impair(line, &token, &i, &backslash);
		else if (line[i] == '"' || line[i] == '\'')
			quotes(&token, &i, line, line[i]);
		else
		{
			if (backslash > 0)
				backslash_exist(line, &token, &i, &backslash);
			else
				backslash_not_exist(line, &token, &i);
		}
		i++;
	}
	*k = i;
	return (token);
}
