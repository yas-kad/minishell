/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 10:41:16 by ikhadem           #+#    #+#             */
/*   Updated: 2021/07/16 10:30:26 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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

int	init_execute_sequence(t_command *cmd, t_env **env)
{
	if (command_count(cmd) == 1 && is_bultin(cmd->command) == TRUE)
		execute_builtins(cmd, env);
	else
		execute_command_list(cmd, env);
	return (EXIT_SUCCESS);
}

int	init_execute_data(t_execute_data *data, t_command *cmd)
{
	data->command_count = command_count(cmd);
	data->pid = (pid_t *)malloc(sizeof(pid_t) * data->command_count);
	if (!data->pid)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	close_and_wait(t_execute_data *data)
{
	int		i;

	i = 0;
	if (data->command_count > 1)
	{
		close(data->old_fds[0]);
		close(data->old_fds[1]);
	}
	while (i < data->command_count)
	{
		waitpid(data->pid[i], 0, 0);
		i++;
	}
}

int	execute_command_list(t_command *cmd, t_env **env)
{
	t_execute_data	data;
	int				counter;

	counter = 0;
	if (init_execute_data(&data, cmd) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (cmd)
	{
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
	close_and_wait(&data);
	return (EXIT_SUCCESS);
}
