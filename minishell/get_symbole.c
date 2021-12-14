/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_symbole.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/11 18:45:10 by yait-kad          #+#    #+#             */
/*   Updated: 2021/07/11 18:45:18 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_pipe_symbole(t_token_list *var, char *line, int i)
{
	char	*token;

	if (line[i + 1] == '|')
	{
		token = ft_strdup("||");
		i++;
	}
	else
	{
		token = strdup("|");
	}
	add_token(var, PIPE, token);
	return (i);
}

int	get_semi_symbole(t_token_list *var, char *line, int i)
{
	char	*token;

	if (line[i + 1] == ';')
	{
		token = ft_strdup(";;");
		i++;
	}
	else
		token = ft_strdup(";");
	add_token(var, SEMICOLON, token);
	return (i);
}

int	get_rg_symbole(t_token_list *var, char *line, int i)
{
	char	*token;

	if (line[i + 1] == '>')
	{
		token = ft_strdup(">>");
		add_token (var, DOUBLE_GREATER, token);
		i++;
	}
	else
	{
		token = ft_strdup(">");
		add_token (var, REDIR_GREATER, token);
	}
	return (i);
}

int	get_rl_symbole(t_token_list *var, char *line, int i)
{
	char	*token;

	if (line[i + 1] == '<')
	{
		token = ft_strdup("<<");
		add_token (var, DOUBLE_LESSER, token);
		i++;
	}
	else
	{
		token = ft_strdup("<");
		add_token (var, REDIR_LESSER, token);
	}
	return (i);
}

void	get_symbole(t_token_list *var, char *line, int *index)
{
	int	i;

	i = *index;
	if (line[i] == '|')
		i = get_pipe_symbole(var, line, i);
	if (line[i] == ';')
		i = get_semi_symbole(var, line, i);
	if (line[i] == '>')
		i = get_rg_symbole(var, line, i);
	if (line[i] == '<')
		i = get_rl_symbole(var, line, i);
	*index = i;
}
