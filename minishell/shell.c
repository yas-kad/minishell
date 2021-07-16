/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikhadem <ikhadem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:40:13 by yait-kad          #+#    #+#             */
/*   Updated: 2021/07/16 10:16:39 by ikhadem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "execute/execute.h"

void	free_list(t_token_list *var)
{
	t_token_list	*curr;

	curr = var;
	while (curr)
	{
		if (curr->value)
		{
			free(curr->value);
			curr->value = NULL;
		}
		free(curr);
		curr = curr->next;
	}
	free(curr);
}

void	destroy_list_cmd(t_command *cmd)
{
	t_command	*curr_cmd;
	int			j;

	curr_cmd = cmd;
	while (curr_cmd)
	{
		if (curr_cmd->command)
		{
			j = 0;
			while (curr_cmd->command[j])
			{
				free(curr_cmd->command[j]);
				j++;
			}
			free(curr_cmd->command);
		}
		if (curr_cmd->redirection)
		{
			destroy_redirection_list(curr_cmd->redirection);
		}
		free(curr_cmd);
		curr_cmd = curr_cmd->next;
	}
	free(curr_cmd);
}

void	signal_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		(void)sig_num;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	initialize_var(t_main *var, int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(*var).cmd = NULL;
	(*var).var = NULL;
	(*var).line = NULL;
	(*var).lenv = NULL;
	(*var).lenv = create_env_list((*var).lenv, env);
	g_dollar_question = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_main	v_main;

	initialize_var(&v_main, argc, argv, env);
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		v_main.line = readline("My_Minishell$ ");
		if (v_main.line == NULL)
			break ;
		add_history(v_main.line);
		v_main.var = ft_lexer(v_main.line);
		v_main.syntax_rslt = check_syntax_error(v_main.var);
		if (v_main.syntax_rslt != 1)
		{
			v_main.cmd = ft_parse(v_main.var, v_main.lenv);
			expanding(v_main.cmd, v_main.lenv);
			g_dollar_question = init_execute_sequence(v_main.cmd, &v_main.lenv);
			destroy_list_cmd(v_main.cmd);
			free_list(v_main.var);
		}
		free(v_main.line);
	}
	return (0);
}
