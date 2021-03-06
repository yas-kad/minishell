/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 10:05:00 by ikhadem           #+#    #+#             */
/*   Updated: 2021/07/16 13:16:39 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** @breif	: prints current Diroctory
** @param	: N/A
** @return	: exit status
*/

int	builtin_pwd(t_env *env)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
		tmp = env_find(env, "PWD");
	printf("%s\n", tmp);
	return (EXIT_SUCCESS);
}
