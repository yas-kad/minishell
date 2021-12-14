/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 17:15:05 by yait-kad          #+#    #+#             */
/*   Updated: 2021/07/15 17:15:07 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_separator(t_command *cmd, char *sep)
{
	if (sep == PIPE)
		cmd->seperator = e_pipe;
	else if (sep == SEMICOLON)
		cmd->seperator = e_semicolon;
	else
		cmd->seperator = e_newline;
}

t_command	*initial_cmd(char **cmd_arg, t_redirection *redirection, char *sep)
{
	t_command	*first_cmd;
	int			size;
	int			i;

	first_cmd = malloc(sizeof(t_command));
	i = 0;
	first_cmd->command = NULL;
	if (cmd_arg != NULL)
	{
		size = tab_size(cmd_arg);
		first_cmd->command = (char **)malloc(sizeof(char *) * (size + 1));
		while (cmd_arg[i] != NULL)
		{
			first_cmd->command[i] = ft_strdup(cmd_arg[i]);
			i++;
		}
		first_cmd->command[i] = NULL;
	}
	first_cmd->redirection = redirection;
	add_separator(first_cmd, sep);
	first_cmd->next = NULL;
	return (first_cmd);
}

void	add_cmd(t_command *cmd, char **cmd_arg, t_redirection *redr, char *sep)
{
	t_command	*new_cmd;
	int			size;
	int			i;

	new_cmd = cmd;
	i = 0;
	while (new_cmd->next != NULL)
		new_cmd = new_cmd->next;
	new_cmd->next = malloc(sizeof(t_command));
	new_cmd->next->command = NULL;
	if (cmd_arg != NULL)
	{
		size = tab_size(cmd_arg);
		new_cmd->next->command = (char **)malloc(sizeof(char *) * (size + 1));
		while (cmd_arg[i] != NULL)
		{
			new_cmd->next->command[i] = cmd_arg[i];
			i++;
		}
		new_cmd->next->command[i] = NULL;
	}
	new_cmd->next->redirection = redr;
	add_separator(new_cmd->next, sep);
	new_cmd->next->next = NULL;
}
