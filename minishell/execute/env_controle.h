/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_controle.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 12:38:16 by ikhadem           #+#    #+#             */
/*   Updated: 2021/07/16 17:13:00 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_CONTROLE_H
# define ENV_CONTROLE_H

# include "../minishell.h"
# include <string.h>
# include <limits.h>

# define INDEX_NOT_FOUND INT_MAX
# define TRUE 0
# define FALSE 1

char	**env_from_t_env_to_2d_array(t_env *env);
void	print_t_env(t_env *env);
size_t	env_find_index(t_env *env, char *value);
void	env_delete_element_at(t_env **env, size_t index);
void	env_add_element(t_env **env, char *args);
char	*env_find(t_env *env, char *key);
void	free_2d_array(char ***arr);
int		env_element_exits(t_env *env, char *arg);
void	env_replace_element(t_env **env, char *arg);
size_t	corp_name(char *str);

#endif