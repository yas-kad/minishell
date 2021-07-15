/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 11:35:25 by yait-kad          #+#    #+#             */
/*   Updated: 2021/07/14 11:35:27 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_error(t_token_list *tokn_lst, t_token_list *old)
{
	int	result;

	result = 0;
	if (tokn_lst->type == NONE)
		result = syntax_error_NONE(tokn_lst, old);
	else if (tokn_lst->type == REDIR_GREATER || tokn_lst->type == REDIR_LESSER
		|| tokn_lst->type == DOUBLE_LESSER || tokn_lst->type == DOUBLE_GREATER)
		result = syntax_error_redir(tokn_lst, old);
	else if (tokn_lst->type == PIPE)
		result = syntax_error_pipe(tokn_lst, old);
	else if (tokn_lst->type == WORD)
		result = syntax_error_word(tokn_lst, old);
	else if (tokn_lst->type == SEMICOLON)
		result = syntax_error_semi(tokn_lst, old);
	return (result);
}

int	check_syntax_error(t_token_list *old)
{
	t_token_list	*token_lst;
	int				result;

	token_lst = old;
	result = 0;
	while (token_lst->type != NEWLINE)
	{
		result = check_error(token_lst, old);
		if (result == 1)
			break ;
		token_lst = token_lst->next;
	}
	return (result);
}
