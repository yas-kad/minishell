/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-kad <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 19:18:37 by yait-kad          #+#    #+#             */
/*   Updated: 2021/03/20 19:18:39 by yait-kad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_h
# define MINISHELL_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

#include <curses.h>
#include <term.h>

#define GREEN "\e[1;32m"
#define RESET "\e[0m"
#define RED "\e[1;91m"
#define CYAN "\e[1;36m"
#define YELLOW "\e[1;33m"
#define PURPLE "\e[1;35m"
#define BLUE "\e[1;34m"
#define Purple "\033[0;35m"
#define Cyan "\033[0;36m"

#define NONE "NONE"
#define PIPE "PIPE"
#define SEMICOLON "SEMICOLON"
#define REDIR_GREATER "REDIR_GREATER"
#define REDIR_LESSER "REDIR_LESSER"
#define DOUBLE_GREATER "DOUBLE_GREATER"
#define DOUBLE_LESSER "DOUBLE_LESSER"
#define WORD "WORD"
#define NEWLINE "NEWLINE"
int	dollar_question;


typedef struct s_minishell
{
    //int index;
    char *type;
    char *value;
    struct s_minishell *next;
    
}               t_token_list;

typedef struct s_env
{
    char *name;
    char *value;
    struct s_env *next;
}               t_env;


typedef struct s_lexer
{
    int i;
    char *token;
    char *tmp;
}               t_var;

typedef struct s_dollar_var
{
    char *name;
    char *tmp;
    char *old_comd;
    char *after_dollar;
    int i;
	int t;
    size_t len;
}               t_d_var;

// expanding outside "" an expandind inside ""

typedef struct s_redirection 
{
    char *type; // <<
    char *file; // xd1    heredoc = treat_heredoc  file = herdoc
    struct s_redirection *next;
    
}               t_redirection;

typedef enum e_type {e_pipe, e_semicolon, e_newline} t_type;

typedef struct s_command 
{
    char **command;
    t_redirection *redirection;
    t_type seperator;

    struct s_command *next;

}               t_command;

t_token_list        *ft_lexer(char *line);
char	*treat_heredocs(char *delimiter, t_env *lenv);

void	free_env(t_env *lenv);

t_token_list	*initialize_list(void);
void	add_token(t_token_list *var, char *type, char *value);

char	*Treat_Quotes(int *index, char *line, char type);
void	quotes(char **token, int *k, char *line, char type);
char	*get_word(char *line, int *k);

void	get_symbole(t_token_list *var, char *line, int *index);
int	get_rl_symbole(t_token_list *var, char *line, int i);
int	get_rg_symbole(t_token_list *var, char *line, int i);
int	get_semi_symbole(t_token_list *var, char *line, int i);
int	get_pipe_symbole(t_token_list *var, char *line, int i);

void	display_token(t_token_list *var);

int	check_backslash(char *line, int i);
void	backslash_impair(char *line, char **token, int *k, int *backslash);
void	backslash_exist(char *line, char **token, int *k, int *backslash);
void	backslash_not_exist(char *line, char **token, int *k);

int                 check_syntax_error(t_token_list *token_lst);
void                display_commands(t_command *cmd);
void                expanding(t_command *cmd, t_env *env_lst);
t_env               *create_env_list(t_env *lenv, char **env);
char                *take_dollar_name(char *comd, int *k, t_env *envl, int type);
void                destroy_redirection_list(t_redirection *redirection);

t_command           *ft_parse(t_token_list *token_list, t_env *lenv);
void    free_list(t_token_list *var);
void    ft_new_str(char *str, int index);
char            *get_dollar_name(char *command,int *j);
size_t          dollar_val(char **comd, char *name, char *old_comd, t_env *envl);
char            *after_dollar_value(char *command1, int i);

#endif