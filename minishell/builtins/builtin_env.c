/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 15:28:08 by ikhadem           #+#    #+#             */
/*   Updated: 2021/07/16 13:41:53 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/*
** @breif	: prints the env to the STDOUT
** @param	: env: current env
** @return	: returns exit status
*/

int	builtin_env(t_env *env)
{
	print_t_env(env);
	return (EXIT_SUCCESS);
}
