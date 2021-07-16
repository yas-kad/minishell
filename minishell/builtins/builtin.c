/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 15:35:25 by ikhadem           #+#    #+#             */
/*   Updated: 2021/07/16 10:14:51 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	is_bultin(char **cmd)
{
	if (cmd == NULL)
		return (FALSE);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (TRUE);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (TRUE);
	return (FALSE);
}

static int	exec(t_command *cmd, t_env **env)
{
	int		*redirection_fds;

	redirection_fds = (int *)malloc(sizeof(int) * count_redirection(cmd));
	if (open_redirection_files(cmd, redirection_fds) == EXIT_FAILURE)
	{
		printf("%s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	set_redirection(cmd, redirection_fds);
	if (ft_strcmp(cmd->command[0], "echo") == 0)
		return (builtin_echo(cmd->command));
	else if (ft_strcmp(cmd->command[0], "cd") == 0)
		return (builtin_cd(env, cmd->command[1]));
	else if (ft_strcmp(cmd->command[0], "pwd") == 0)
		return (builtin_pwd());
	else if (ft_strcmp(cmd->command[0], "export") == 0)
		return (builtin_export(env, cmd->command));
	else if (ft_strcmp(cmd->command[0], "unset") == 0)
		return (builtin_unset(env, cmd->command));
	else if (ft_strcmp(cmd->command[0], "env") == 0)
		return (builtin_env(*env));
	else if (ft_strcmp(cmd->command[0], "exit") == 0)
		return (builtin_exit(cmd->command));
	free(redirection_fds);
	return (EXIT_SUCCESS);
}

int	execute_builtins(t_command *cmd, t_env **env)
{
	int		save_fds[3];

	save_fds[0] = dup(STDIN_FILENO);
	save_fds[1] = dup(STDOUT_FILENO);
	save_fds[2] = dup(STDERR_FILENO);
	exec(cmd, env);
	dup2(save_fds[0], STDIN_FILENO);
	dup2(save_fds[1], STDOUT_FILENO);
	dup2(save_fds[2], STDERR_FILENO);
	close(save_fds[0]);
	close(save_fds[1]);
	close(save_fds[2]);
	return (EXIT_SUCCESS);
}
