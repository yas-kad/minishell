/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/05 17:42:51 by yait-kad          #+#    #+#             */
/*   Updated: 2021/04/05 17:43:08 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_cmd_arg(t_parce *var)
{
	t_token_list	*first_word;
	int				i;

	(*var).size = 0;
	i = 0;
	(*var).cmd_arg = NULL;
	first_word = (*var).current_token;
	while ((*var).current_token->type == WORD)
	{
		(*var).size++;
		(*var).current_token = (*var).current_token->next;
	}
	if ((*var).cmd_arg == NULL)
	{
		(*var).cmd_arg = (char **)malloc(sizeof(char *) * ((*var).size + 1));
		i = 0;
	}
	(*var).size = i + (*var).size;
	while (i < (*var).size)
	{
		(*var).cmd_arg[i] = ft_strdup(first_word->value);
		first_word = first_word->next;
		i++;
	}
	(*var).cmd_arg[i] = NULL;
}

void	initialize(t_parce *var, t_token_list *token_list)
{
	(*var).size = 0;
	(*var).current_token = token_list;
	(*var).redirection = NULL;
	(*var).cmd_arg = NULL;
	(*var).cmd = NULL;
}

int	is_redir(char *type)
{
	if (ft_strcmp(type, REDIR_GREATER) == 0)
		return (1);
	else if (ft_strcmp(type, REDIR_LESSER) == 0)
		return (1);
	else if (ft_strcmp(type, DOUBLE_LESSER) == 0)
		return (1);
	else if (ft_strcmp(type, DOUBLE_GREATER) == 0)
		return (1);
	return (0);
}

t_command	*ft_parse(t_token_list *token_list, t_env *lenv)
{
	t_parce	var;

	initialize(&var, token_list);
	while (var.current_token)
	{
		if (var.current_token->type == WORD)
			add_cmd_arg(&var);
		if (is_redir(var.current_token->type) == 1)
		{
			if (!var.redirection)
				var.redirection = initial_redirection(var.current_token->type, \
					var.current_token->next->value, lenv);
			else
				add_redirection(var.redirection, var.current_token->type,
					var.current_token->next->value, lenv);
			var.current_token = var.current_token->next;
		}
		if (var.current_token->type == PIPE || \
			var.current_token->type == SEMICOLON || \
				var.current_token->type == NEWLINE)
			create_cmd(&var);
		var.current_token = var.current_token->next;
	}
	return (var.cmd);
}
