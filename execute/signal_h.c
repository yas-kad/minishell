/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_h.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 14:54:48 by yait-kad          #+#    #+#             */
/*   Updated: 2021/07/16 14:54:57 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	sig_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		printf("\n");
		g_dollar_question = 130;
	}
	else if (sig_num == SIGQUIT)
	{
		printf("Quit: 3\n");
		g_dollar_question = 131;
	}
}
