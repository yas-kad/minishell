/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 15:35:25 by ikhadem           #+#    #+#             */
/*   Updated: 2021/07/16 11:46:48 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** @breif	: checks if the passed command and args list is not null
**				and a valid built
** @param	: cmd: list of args and command to execute
** @return	: TRUE if it a builtin other ise FALSE
*/

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

/*
** @breif	: executes the appropriate builtin command
** @param	: cmd:	command node to execute
**			  env: reference to current env
** @return	: exit status of executed command
*/

static int	exec_emd(t_command *cmd, t_env **env)
{
	if (ft_strcmp(cmd->command[0], "echo") == 0)
		return (builtin_echo(cmd->command));
	else if (ft_strcmp(cmd->command[0], "cd") == 0)
		return (builtin_cd(env, cmd->command[1]));
	else if (ft_strcmp(cmd->command[0], "pwd") == 0)
		return (builtin_pwd(*env));
	else if (ft_strcmp(cmd->command[0], "export") == 0)
		return (builtin_export(env, cmd->command));
	else if (ft_strcmp(cmd->command[0], "unset") == 0)
		return (builtin_unset(env, cmd->command));
	else if (ft_strcmp(cmd->command[0], "env") == 0)
		return (builtin_env(*env));
	else if (ft_strcmp(cmd->command[0], "exit") == 0)
		return (builtin_exit(cmd->command));
	return (EXIT_FAILURE);
}

/*
** @breif	: opens redirection files and sets correct redirection
**				and executing current command node
** @param	: cmd:	comcurrent command to execute
**			  env: reference to current envirenment
** @return	:
*/

static int	exec(t_command *cmd, t_env **env)
{
	int		*redirection_fds;
	int		err;
	int		ret;

	redirection_fds = (int *)malloc(sizeof(int) * count_redirection(cmd));
	err = open_redirection_files(cmd, redirection_fds);
	if (err == EXIT_FAILURE)
	{
		printf("%s\n", strerror(errno));
		return (EXIT_FAILURE);
	}
	else if (err == AMBG_REDIR)
		return (EXIT_FAILURE);
	set_redirection(cmd, redirection_fds);
	ret = exec_emd(cmd, env);
	free(redirection_fds);
	return (ret);
}

/*
** @breif	: saves current std_fds executes command and restores std_fds
** @param	: cmd: command list
**			  env: current envirement
** @return	: exit status of executed command
*/

int	execute_builtins(t_command *cmd, t_env **env)
{
	int		save_fds[3];
	int		ret;

	save_fds[0] = dup(STDIN_FILENO);
	save_fds[1] = dup(STDOUT_FILENO);
	save_fds[2] = dup(STDERR_FILENO);
	ret = exec(cmd, env);
	dup2(save_fds[0], STDIN_FILENO);
	dup2(save_fds[1], STDOUT_FILENO);
	dup2(save_fds[2], STDERR_FILENO);
	close(save_fds[0]);
	close(save_fds[1]);
	close(save_fds[2]);
	return (ret);
}
