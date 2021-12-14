/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 13:38:23 by yait-kad          #+#    #+#             */
/*   Updated: 2021/07/14 13:38:25 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar_outside_quotes(char *comd, int *k, int *tmp)
{
	char	*name;
	char	type;
	int		i;

	i = *k;
	(name) = ft_strdup("");
	type = (comd)[i + 1];
	ft_new_str((comd), i);
	ft_new_str((comd), i);
	expand_name((comd), &i, type);
	*tmp = 1;
	*k = i;
	return (name);
}

int	check_name(char **comd, int *k, char **name, char type_f)
{
	int	tmp;
	int	i;

	i = *k;
	tmp = 0;
	if ((*comd)[i + 1] == '?')
	{
		ft_new_str((*comd), i);
		(*name) = ft_substr((*comd), i++, 1);
	}
	else if (((*comd)[i + 1] == '"' || (*comd)[i + 1] == '\'') && type_f != 3)
		(*name) = dollar_outside_quotes((*comd), &i, &tmp);
	else
	{
		if (ft_isalnum((*comd)[i + 1]) == 1 || (*comd)[i + 1] == '_')
			ft_new_str((*comd), i);
		if (ft_isdigit((*comd)[i]) == 1)
			(*name) = ft_substr((*comd), i++, 1);
		else
			(*name) = get_dollar_name((*comd), &i);
	}
	*k = i;
	return (tmp);
}

void	free_tvar(t_d_var dvar)
{
	free(dvar.old_comd);
	free(dvar.after_dollar);
	free(dvar.name);
}

int	vallue_dollar(t_d_var dvar, t_env *envl, char **comd)
{
	int	k;

	if (ft_strcmp(dvar.name, "") == 0 && dvar.t == 0)
		dvar.i++;
	k = dvar.i;
	if (ft_strcmp(dvar.name, "") != 0 && dvar.t == 0)
	{
		if (ft_strcmp(dvar.name, "?") == 0)
			dollar_q(comd, dvar.old_comd, &dvar.len);
		else if (ft_strcmp(dvar.name, "0") == 0)
			dollar_zero(comd, dvar.old_comd, &dvar.len);
		else
			dvar.len = dollar_val(comd, dvar.name, dvar.old_comd, envl);
		k = dvar.len - 1;
	}
	else if (dvar.t == 0)
		name_empty(comd, dvar.old_comd, &dvar.len);
	dvar.tmp = ft_strjoin((*comd), dvar.after_dollar);
	free((*comd));
	(*comd) = dvar.tmp;
	return (k);
}

char	*take_dollar_name(char *comd, int *k, t_env *envl, int type)
{
	t_d_var	dvar;

	dvar.i = *k;
	dvar.len = 0;
	dvar.old_comd = ft_substr(comd, 0, dvar.i);
	dvar.t = check_name(&comd, &dvar.i, &dvar.name, type);
	dvar.after_dollar = after_dollar_value(comd, dvar.i);
	if (dvar.t == 0)
	{
		*k = vallue_dollar(dvar, envl, &comd);
		if (ft_strcmp(comd, "") == 0 && type == 1)
		{
			printf("\e[1;91m$%s: ambiguous redirect\e[0m\n", dvar.name);
			dvar.tmp = ft_strdup("\n");
			free(comd);
			comd = dvar.tmp;
			g_dollar_question = 1;
		}
	}
	else
		*k = dvar.i;
	free_tvar(dvar);
	return (comd);
}
