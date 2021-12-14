/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 12:06:00 by yait-kad          #+#    #+#             */
/*   Updated: 2021/04/03 12:06:03 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ex_cmd(char **command, int j, t_env *env_list)
{
	if ((*command)[j] == '$')
		(*command) = take_dollar_name((*command), &j, env_list, 0);
	else if ((*command)[j] == '\\')
		ft_new_str((*command), j);
	else if ((*command)[j] == '"')
	{
		ft_new_str((*command), j);
		j = expand_double_quotes(command, j, env_list);
	}
	else if ((*command)[j] == '\'')
	{
		ft_new_str((*command), j);
		j = expand_single_quote((*command), j);
	}
	return (j);
}

void	expand_command(t_command *cmd_c, t_env *env_list)
{
	int	i;
	int	j;

	i = 0;
	while (cmd_c->command[i] != NULL)
	{
		j = 0;
		while (cmd_c->command[i][j] != '\0')
		{
			j = ex_cmd(&cmd_c->command[i], j, env_list);
			j++;
		}
		i++;
	}
	delete_empty(&cmd_c->command);
}

int	ex_redir(char **file, int i, t_env *env_r)
{
	if ((*file)[i] == '$')
		(*file) = take_dollar_name((*file), &i, env_r, 1);
	else if ((*file)[i] == '\\')
		ft_new_str((*file), i);
	else if ((*file)[i] == '"')
	{
		ft_new_str((*file), i);
		i = i + expand_double_quotes(file, i, env_r);
	}
	else if ((*file)[i] == '\'')
	{
		ft_new_str((*file), i);
		i = i + expand_single_quote((*file), i);
	}
	return (i);
}

void	expand_redirection(t_command *cmd_r, t_env *env_r)
{
	t_redirection	*current_redir_list;
	int				i;

	current_redir_list = cmd_r->redirection;
	while (current_redir_list)
	{
		i = 0;
		if (ft_strcmp(current_redir_list->type, "DOUBLE_LESSER") != 0)
		{
			while (current_redir_list->file[i] != '\0')
			{
				i = ex_redir(&current_redir_list->file, i, env_r);
				i++;
			}
		}
		current_redir_list = current_redir_list->next;
	}
}

void	expanding(t_command *cmd, t_env *env_lst)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd != NULL)
	{
		if (cmd->command != NULL)
			expand_command(cmd, env_lst);
		if (cmd->redirection)
			expand_redirection(cmd, env_lst);
		cmd = cmd->next;
	}
}
