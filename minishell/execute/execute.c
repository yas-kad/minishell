/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 10:41:16 by ikhadem           #+#    #+#             */
/*   Updated: 2021/07/16 11:57:05 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/*
** @breif	: counts number of command nodes
**
** @param	: cmd:	commands linked list
** @return	: the number of commands
*/

int	command_count(t_command *cmd)
{
	int	res;

	res = 0;
	while (cmd)
	{
		res++;
		cmd = cmd->next;
	}
	return (res);
}

/*
** @breif	: starts the execution of commands from list while checking for
**				builtin or externals
**
** @param	: cmd: commands linked list
**			  env: reference to current envirenment list
** @return	: exit status
*/

int	init_execute_sequence(t_command *cmd, t_env **env)
{
	if (command_count(cmd) == 1 && is_bultin(cmd->command) == TRUE)
		return (execute_builtins(cmd, env));
	else
		return (execute_command_list(cmd, env));
	return (EXIT_FAILURE);
}

/*
** @breif	: inits the data used by the execute command list function
** @param	: data: reference to the data structure used by execute function
			  cmd:	commands linked list
** @return	: exit status of the memory allocation
*/

int	init_execute_data(t_execute_data *data, t_command *cmd)
{
	data->prev = NULL;
	data->command_count = command_count(cmd);
	data->pid = (pid_t *)malloc(sizeof(pid_t) * data->command_count);
	if (!data->pid)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
** @breif	: closes the latest pipe opened in execute list
**				and frees the pid list allocated in init_execute_data
** @param	: data:	reference to the data used by execute function
** @return	: exit status of the last child process
*/

static int	close_and_wait(t_execute_data *data)
{
	int		i;
	int		status;
	int		ret;

	i = 0;
	ret = 0;
	if (data->command_count > 1)
	{
		close(data->old_fds[0]);
		close(data->old_fds[1]);
	}
	while (i < data->command_count)
	{
		waitpid(data->pid[i], &status, 0);
		i++;
	}
	free(data->pid);
	if (WIFEXITED(status))
		ret = WEXITSTATUS(status);
	return (ret);
}

/*
** @breif	: inits data used for execute set signal handlers
**				creates pipes if needed and creates a fork foreach command
** @param	: cmd:	command list
** @return	: exit status of the last executeed command
*/

int	execute_command_list(t_command *cmd, t_env **env)
{
	t_execute_data	data;
	int				counter;

	counter = 0;
	if (init_execute_data(&data, cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (cmd)
	{
		signal(SIGINT, sig_handler);
		signal(SIGQUIT, sig_handler);
		if (cmd->next != NULL)
			if (pipe(data.new_fds) == -1)
				return (EXIT_FAILURE);
		data.pid[counter] = fork();
		if (data.pid[counter] == 0)
			pipe_child_exec(&data, cmd, env);
		else if (data.pid[counter] < 0)
			printf("ERROR: %s\n", strerror(errno));
		else
			pipe_parent_exec(&data, cmd);
		counter++;
		data.prev = cmd;
		cmd = cmd->next;
	}
	return (close_and_wait(&data));
}
