/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:40:13 by yait-kad          #+#    #+#             */
/*   Updated: 2021/03/20 14:40:16 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    banner()
{
    printf("\e[1;32m ██████   ██████ █████ ██████   █████ █████  █████████  █████   █████ ██████████ █████       █████      \e[0m\n");
    printf("\e[1;32m░░██████ ██████ ░░███ ░░██████ ░░███ ░░███  ███░░░░░███░░███   ░░███ ░░███░░░░░█░░███       ░░███       \e[0m\n");
    printf("\e[1;32m ░███░█████░███  ░███  ░███░███ ░███  ░███ ░███    ░░░  ░███    ░███  ░███  █ ░  ░███        ░███       \e[0m\n");
    printf("\e[1;32m ░███░░███ ░███  ░███  ░███░░███░███  ░███ ░░█████████  ░███████████  ░██████    ░███        ░███       \e[0m\n");
    printf("\e[1;32m ░███ ░░░  ░███  ░███  ░███ ░░██████  ░███  ░░░░░░░░███ ░███░░░░░███  ░███░░█    ░███        ░███       \e[0m\n");
    printf("\e[1;32m ░███      ░███  ░███  ░███  ░░█████  ░███  ███    ░███ ░███    ░███  ░███ ░   █ ░███      █ ░███      █\e[0m\n");
    printf("\e[1;32m █████     █████ █████ █████  ░░█████ █████░░█████████  █████   █████ ██████████ ███████████ ███████████\e[0m\n");
    printf("\e[1;32m░░░░░     ░░░░░ ░░░░░ ░░░░░    ░░░░░ ░░░░░  ░░░░░░░░░  ░░░░░   ░░░░░ ░░░░░░░░░░ ░░░░░░░░░░░ ░░░░░░░░░░░ \e[0m\n");
}


void    free_list(t_token_list *var)
{
    t_token_list *curr = var;

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

void    destroy_list_cmd(t_command *cmd)
{
    t_command *curr_cmd;

    curr_cmd = cmd;
    while (curr_cmd)
    {
        if (curr_cmd->command)
        {
            int j = 0;
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

int     main(int argc, char **argv, char **env)
{
    t_token_list *var;
    t_command *cmd = NULL;
    t_env *lenv;
    char *line;
    int syntax_rslt;

    (void)argc;
    (void)argv;
    var = NULL;
    line = NULL;
    lenv = NULL;
    banner();
    lenv = create_env_list(lenv, env);
	dollar_question = 0;
    while (1)
    {
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		
		line = readline("My_Minishell $ ");
		if (line == NULL)
			exit(0);
		add_history(line);
        var = ft_lexer(line);
        display_token(var);
        syntax_rslt = check_syntax_error(var);
        if (syntax_rslt != 1)
        {
            cmd = ft_parse(var, lenv);
            expanding(cmd, lenv);
            display_commands(cmd);
            destroy_list_cmd(cmd);
            free_list(var);
        }
		//free_env(lenv);
        free(line);
        if (ft_strcmp((const char*)line,"exit") == 0)
        {
            //free(line);
            break;
        }
    }
    return 0;
}
