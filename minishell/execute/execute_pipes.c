/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 14:09:12 by ikhadem           #+#    #+#             */
/*   Updated: 2021/07/16 10:53:20 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	count_pipes(t_command *cmd)
{
	t_command	*iter;
	int			ret;

	ret = 0;
	iter = cmd;
	while (iter)
	{
		if (iter->seperator == e_pipe)
			ret++;
		iter = iter->next;
	}
	return (ret);
}

void	set_pipes(t_execute_data *data, t_command *cmd)
{
	if (data->prev != NULL)
	{
		dup2(data->old_fds[0], STDIN_FILENO);
		close(data->old_fds[0]);
		close(data->old_fds[1]);
	}
	if (cmd->next != NULL)
	{
		dup2(data->new_fds[1], STDOUT_FILENO);
		close(data->new_fds[0]);
		close(data->new_fds[1]);
	}
}

void	pipe_child_exec(t_execute_data *data, t_command *cmd, t_env **env)
{
	int		*redirection_fds;
	int		err;

	redirection_fds = (int *)malloc(sizeof(int) * count_redirection(cmd));
	err = open_redirection_files(cmd, redirection_fds);
	if (err == EXIT_FAILURE)
	{
		printf("%s\n", strerror(errno));
		exit (EXIT_FAILURE);
	}
	else if (err == AMBG_REDIR)
		exit (EXIT_FAILURE);
	set_pipes(data, cmd);
	set_redirection(cmd, redirection_fds);
	if (is_bultin(cmd->command) == TRUE)
		exit (execute_builtins(cmd, env));
	else if (ft_execve(cmd, env) == NOT_FILE)
		printf("%s: is a directory\n", cmd->command[0]);
	else
		printf("%s: command not found\n", cmd->command[0]);
	exit (EXIT_FAILURE);
}

void	pipe_parent_exec(t_execute_data *data, t_command *cmd)
{
	if (data->prev != NULL)
	{
		close(data->old_fds[0]);
		close(data->old_fds[1]);
	}
	if (cmd->next != NULL)
	{
		data->old_fds[0] = data->new_fds[0];
		data->old_fds[1] = data->new_fds[1];
	}
}
