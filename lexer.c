/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:13:17 by yait-kad          #+#    #+#             */
/*   Updated: 2021/03/23 16:13:35 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_list	*initialize_list(void)
{
	t_token_list	*first_token;

	first_token = malloc(sizeof(t_token_list));
	first_token->type = NONE;
	first_token->value = ft_strdup("NONE");
	first_token->next = NULL;
	return (first_token);
}

void	add_token(t_token_list *var, char *type, char *value)
{
	t_token_list	*new_token;

	new_token = var;
	while (new_token->next != NULL)
		new_token = new_token->next;
	new_token->next = (t_token_list *)malloc(sizeof(t_token_list));
	new_token->next->type = type;
	new_token->next->value = value;
	new_token->next->next = NULL;
}

t_token_list	*ft_lexer(char *ln)
{
	t_token_list	*var;
	t_var			lexr;

	lexr.i = 0;
	var = initialize_list();
	while (ln[lexr.i])
	{
		lexr.token = ft_strdup("");
		lexr.tmp = lexr.token;
		while ((ln[lexr.i] == ' ' || ln[lexr.i] == '\t'))
			lexr.i++;
		if (ln[lexr.i] == '|' || ln[lexr.i] == ';'
			|| ln[lexr.i] == '>' || ln[lexr.i] == '<')
		{
			get_symbole(var, ln, &lexr.i);
			lexr.i++;
		}
		free(lexr.tmp);
		if ((ln[lexr.i] != '\0') && (ft_strchr("|;> <\t", ln[lexr.i]) == NULL))
			lexr.token = get_word(ln, &lexr.i);
		if (ft_strcmp(lexr.token, "") != 0)
			add_token(var, WORD, lexr.token);
	}
	add_token(var, NEWLINE, ft_strdup("NEWLINE"));
	return (var);
}
