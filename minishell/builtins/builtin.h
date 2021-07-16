/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 13:52:49 by ikhadem           #+#    #+#             */
/*   Updated: 2021/07/16 10:15:27 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# define ERROR -1
# define TRUE 0
# define FALSE 1

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
# include "../minishell.h"
# include "../execute/env_controle.h"
# include "../execute/execute.h"

int		is_bultin(char **cmd);
int		builtin_cd(t_env **env, char *line);
int		builtin_echo(char **args);
int		builtin_pwd(void);
int		builtin_unset(t_env **l_env, char **args);
int		builtin_env(t_env *env);
int		builtin_export(t_env **env, char **args);
int		builtin_exit(char **args);
int		execute_builtins(t_command *cmd, t_env **env);
int		is_null_or_empty(char *str);

#endif