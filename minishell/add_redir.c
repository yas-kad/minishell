/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:15:15 by yait-kad          #+#    #+#             */
/*   Updated: 2021/07/15 17:15:17 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_redirection_list(t_redirection *redirection)
{
	t_redirection	*curr_redir;

	curr_redir = redirection;
	while (curr_redir)
	{
		if (curr_redir->file)
		{
			free(curr_redir->file);
			curr_redir->file = NULL;
		}
		if (curr_redir->type)
		{
			free(curr_redir->type);
			curr_redir->type = NULL;
		}
		free(curr_redir);
		curr_redir = curr_redir->next;
	}
	free(curr_redir);
}

t_redirection	*initial_redirection(char *type, char *value, t_env *lenv)
{
	t_redirection	*new_redirection;

	new_redirection = malloc(sizeof(t_redirection));
	if (type == DOUBLE_LESSER)
	{
		new_redirection->type = ft_strdup(type);
		new_redirection->file = treat_heredocs(value, lenv);
		new_redirection->next = NULL;
	}
	else
	{
		new_redirection->type = ft_strdup(type);
		new_redirection->file = ft_strdup(value);
		new_redirection->next = NULL;
	}
	return (new_redirection);
}

void	add_redirection(t_redirection *rdr, char *type, char *val, t_env *lenv)
{
	t_redirection	*new_redirection;

	new_redirection = rdr;
	while (new_redirection->next != NULL)
		new_redirection = new_redirection->next;
	new_redirection->next = malloc(sizeof(t_redirection));
	if (type == DOUBLE_LESSER)
	{
		new_redirection->next->type = ft_strdup(type);
		new_redirection->next->file = treat_heredocs(val, lenv);
		new_redirection->next->next = NULL;
	}
	else
	{
		new_redirection->next->type = ft_strdup(type);
		new_redirection->next->file = ft_strdup(val);
		new_redirection->next->next = NULL;
	}
}
