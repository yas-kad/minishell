/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 10:38:04 by ikhadem           #+#    #+#             */
/*   Updated: 2021/07/16 11:48:10 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# define ERROR -1
# define TRUE 0
# define FALSE 1
# define NOT_FILE 100
# define AMBG_REDIR 101

# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include "../minishell.h"
# include "../builtins/builtin.h"
# include "env_controle.h"

typedef struct s_execute_data
{
	t_command	*lst;
	t_command	*prev;
	pid_t		*pid;
	int			command_count;
	int			old_fds[2];
	int			new_fds[2];
}				t_execute_data;

int			init_execute_sequence(t_command *cmd, t_env **env);
int			execute_command_list(t_command *cmd, t_env **env);
void		fd_save(int **fd);
void		fd_restore(int **fd);
void		pipe_child_exec(t_execute_data *data, t_command *cmd, t_env **env);
void		pipe_parent_exec(t_execute_data *data, t_command *cmd);
int			ft_execve(t_command *node, t_env **env);
int			set_redirection(t_command *cmd, int *fd_list);
size_t		count_redirection(t_command *cmd);
int			open_redirection_files(t_command *cmd, int *fd_list);

#endif