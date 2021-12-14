/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/12 15:51:45 by ikhadem           #+#    #+#             */
/*   Updated: 2021/07/16 13:39:20 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static void	ft_dup_and_close(int fd1, int fd2)
{
	dup2(fd1, fd2);
	close(fd1);
}

static void	ft_dup_heredoc(char *file)
{
	int	heredoc_pipe[2];

	pipe(heredoc_pipe);
	write(heredoc_pipe[1], file, ft_strlen(file));
	dup2(heredoc_pipe[0], STDIN_FILENO);
	close(heredoc_pipe[0]);
	close(heredoc_pipe[1]);
}

/*
** @breif	: sets the appropriate rederiction from the list of
**				fds based on it's tag
** @param	: cmd: current command node
			  fd_list: list of file dicriptors to redirect to / from
** @return	: exit status
*/

int	set_redirection(t_command *cmd, int *fd_list)
{
	t_redirection	*iter;
	size_t			counter;

	counter = 0;
	iter = cmd->redirection;
	if (cmd->redirection != NULL)
	{
		while (iter)
		{
			if (strcmp(iter->type, REDIR_LESSER) == 0)
				ft_dup_and_close(fd_list[counter], STDIN_FILENO);
			else if (strcmp(iter->type, DOUBLE_LESSER) == 0)
				ft_dup_heredoc(iter->file);
			else if (strcmp(iter->type, REDIR_GREATER) == 0)
				ft_dup_and_close(fd_list[counter], STDOUT_FILENO);
			else if (strcmp(iter->type, DOUBLE_GREATER) == 0)
				ft_dup_and_close(fd_list[counter], STDOUT_FILENO);
			counter++;
			iter = iter->next;
		}
	}
	return (EXIT_SUCCESS);
}

/*
** @breif	: counts the number of file discreptors needed
** @param	: cmd: current command node
** @return	: the number of fd needed
*/

size_t	count_redirection(t_command *cmd)
{
	t_redirection	*iter;
	size_t			counter;

	counter = 0;
	iter = cmd->redirection;
	while (iter)
	{
		if (ft_strcmp(iter->type, DOUBLE_LESSER) != 0)
			counter++;
		iter = iter->next;
	}
	return (counter);
}

/*
** @breif	: opens the fd needed for redirection
** @param	: cmd: current command node
**			  fd_list: list to hold opened fds
** @return	:
*/

int	open_redirection_files(t_command *cmd, int *fd_list)
{
	t_redirection	*iter;
	size_t			counter;

	iter = cmd->redirection;
	counter = 0;
	while (iter)
	{
		if (ft_strcmp(iter->file, "\n") == 0)
			return (AMBG_REDIR);
		else if (ft_strcmp(iter->type, REDIR_LESSER) == 0)
			fd_list[counter] = open(iter->file, O_RDONLY);
		else if (cmd->command != NULL
			&& ft_strcmp(iter->type, REDIR_GREATER) == 0)
			fd_list[counter] = open(iter->file,
					O_CREAT | O_TRUNC | O_WRONLY, 0644);
		else if (ft_strcmp(iter->type, DOUBLE_GREATER) == 0)
			fd_list[counter] = open(iter->file,
					O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (fd_list[counter] == -1)
			return (EXIT_FAILURE);
		counter++;
		iter = iter->next;
	}
	return (EXIT_SUCCESS);
}
