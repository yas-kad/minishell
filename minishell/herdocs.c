/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdocs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:15:28 by yait-kad          #+#    #+#             */
/*   Updated: 2021/07/15 17:15:31 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*check_name_hdc(char *buffer, int *k)
{
	char	*name;
	int		i;

	i = *k;
	if (ft_isalnum(buffer[i + 1]) == 1 || buffer[i + 1] == '_')
		ft_new_str(buffer, i);
	if (ft_isdigit(buffer[i]) == 1)
		name = ft_substr(buffer, i++, 1);
	else
		name = get_dollar_name(buffer, &i);
	*k = i;
	return (name);
}

void	expand_herdocs(char **buffer, t_env *lenv)
{
	t_herdocs	var;

	var.i = 0;
	while ((*buffer)[var.i] != '\0')
	{
		if ((*buffer)[var.i] == '$' && (ft_isalnum((*buffer)[var.i + 1]) == 1
			|| (*buffer)[var.i + 1] == '_'))
		{
			var.before_dollar = ft_substr((*buffer), 0, var.i);
			var.env_name = check_name_hdc((*buffer), &var.i);
			var.after_dollar = after_dollar_value((*buffer), var.i);
			var.len = dollar_val(&(*buffer), var.env_name, \
				var.before_dollar, lenv);
			var.tmp = ft_strjoin((*buffer), var.after_dollar);
			free((*buffer));
			(*buffer) = var.tmp;
			free(var.before_dollar);
			free(var.env_name);
			free(var.after_dollar);
			var.i = var.len - 1;
		}
		var.i++;
	}
}

char	*remove_quotes(char *delimiter, int *qt)
{
	int		i;
	char	state;

	i = 0;
	while (delimiter[i] != '\0')
	{
		if (delimiter[i] == '"' || delimiter[i] == '\'')
		{
			*qt = 1;
			state = delimiter[i];
			ft_new_str(delimiter, i);
			while (delimiter[i] != '\0' && delimiter[i] != state)
				i++;
			if (delimiter[i] == state)
				ft_new_str(delimiter, i);
			i--;
		}
		i++;
	}
	return (delimiter);
}

void	initial(t_trt_her *var, char **delimiter)
{
	(*var).q_exist = 0;
	(*var).buffer = ft_strdup("");
	signal(SIGINT, SIG_IGN);
	(*delimiter) = remove_quotes((*delimiter), &(*var).q_exist);
}

char	*treat_heredocs(char *delimiter, t_env *lenv)
{
	t_trt_her	var;

	initial(&var, &delimiter);
	while (1)
	{
		var.line = readline(">>");
		if (var.line == NULL)
			break ;
		if (ft_strcmp(var.line, delimiter) == 0)
		{
			free(var.line);
			var.line = NULL;
			break ;
		}
		var.tmp1 = ft_strjoin(var.line, "\n");
		free(var.line);
		var.line = var.tmp1;
		var.tmp = ft_strjoin(var.buffer, var.line);
		free(var.line);
		free(var.buffer);
		var.buffer = var.tmp;
	}
	if (var.q_exist == 0)
		expand_herdocs(&var.buffer, lenv);
	return (var.buffer);
}
