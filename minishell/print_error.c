/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 13:26:30 by yait-kad          #+#    #+#             */
/*   Updated: 2021/07/14 13:26:32 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_error(char *value)
{
	printf("\e[1;91mMy_Minishell: syntax error near");
	printf(" unexpected token %s\e[0m\n", value);
	g_dollar_question = 258;
}

void	destroy_list(t_token_list *lst)
{
	t_token_list	*tmp;

	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->value);
		free(tmp);
		tmp = NULL;
	}
	free(lst);
}
