/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_symb.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 11:36:27 by yait-kad          #+#    #+#             */
/*   Updated: 2021/07/14 11:36:29 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_error_NONE(t_token_list *token_none, t_token_list *head)
{
	int	result;

	result = 0;
	if (token_none->next->type == PIPE || token_none->next->type == SEMICOLON)
	{
		display_error(token_none->next->value);
		destroy_list(head);
		result = 1;
	}
	else if (token_none->next->type == NEWLINE)
	{
		destroy_list(head);
		result = 1;
	}
	return (result);
}

int	syntax_error_redir(t_token_list *token_redir, t_token_list *head)
{
	int	result;

	result = 0;
	if (token_redir->next->type != WORD)
	{
		display_error(token_redir->next->value);
		destroy_list(head);
		result = 1;
	}
	return (result);
}

int	syntax_error_pipe(t_token_list *token_pipe, t_token_list *head)
{
	int	result;

	result = 0;
	if (token_pipe->next->type == PIPE || token_pipe->next->type == SEMICOLON)
	{
		display_error(token_pipe->next->value);
		destroy_list(head);
		result = 1;
	}
	else if (token_pipe->next->type == NEWLINE)
	{
		display_error(token_pipe->next->value);
		destroy_list(head);
		result = 1;
	}
	return (result);
}

int	syntax_error_word(t_token_list *token_word, t_token_list *head)
{
	int	result;

	result = 0;
	if (((check_backslash_end(token_word->value))) % 2 != 0)
	{
		printf("%ssyntax error multiple line not allowed\n%s", RED, RESET);
		g_dollar_question = 258;
		destroy_list(head);
		result = 1;
	}
	if (check_quotes(token_word->value) == -1)
	{
		printf("%ssyntax error multiple line not allowed\n%s", RED, RESET);
		g_dollar_question = 258;
		destroy_list(head);
		result = 1;
	}
	return (result);
}

int	syntax_error_semi(t_token_list *token_semi, t_token_list *head)
{
	int	result;

	result = 0;
	if (ft_strcmp(token_semi->value, ";;") == 0)
	{
		display_error(token_semi->value);
		destroy_list(head);
		result = 1;
	}
	else if (token_semi->next->type == PIPE || \
		token_semi->next->type == SEMICOLON)
	{
		display_error(token_semi->next->value);
		destroy_list(head);
		result = 1;
	}
	return (result);
}
