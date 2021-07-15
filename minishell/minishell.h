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

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define GREEN "\e[1;32m"
# define RESET "\e[0m"
# define RED "\e[1;91m"
# define CYAN "\e[1;36m"
# define YELLOW "\e[1;33m"
# define PURPLE "\e[1;35m"
# define BLUE "\e[1;34m"

# define NONE "NONE"
# define PIPE "PIPE"
# define SEMICOLON "SEMICOLON"
# define REDIR_GREATER "REDIR_GREATER"
# define REDIR_LESSER "REDIR_LESSER"
# define DOUBLE_GREATER "DOUBLE_GREATER"
# define DOUBLE_LESSER "DOUBLE_LESSER"
# define WORD "WORD"
# define NEWLINE "NEWLINE"
int	g_dollar_question;

typedef struct s_minishell
{
	char				*type;
	char				*value;
	struct s_minishell	*next;
}			t_token_list;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}			t_env;

typedef struct s_lexer
{
	int		i;
	char	*token;
	char	*tmp;
}			t_var;

typedef struct s_dollar_var
{
	char	*name;
	char	*tmp;
	char	*old_comd;
	char	*after_dollar;
	int		i;
	int		t;
	size_t	len;
}			t_d_var;

typedef struct s_redirection
{
	char					*type;
	char					*file;
	struct s_redirection	*next;
}			t_redirection;

typedef enum e_type {e_pipe, e_semicolon, e_newline}	t_type;

typedef struct s_command
{
	char				**command;
	t_redirection		*redirection;
	t_type				seperator;
	struct s_command	*next;
}			t_command;

typedef struct s_main
{
	t_token_list	*var;
	t_command		*cmd;
	t_env			*lenv;
	char			*line;
	int				syntax_rslt;
}			t_main;

typedef struct s_parce
{
	t_command		*cmd;
	t_redirection	*redirection;
	t_token_list	*current_token;
	char			**cmd_arg;
	int				size;
}				t_parce;

typedef struct s_treat_her
{
	char	*line;
	char	*buffer;
	char	*tmp;
	char	*tmp1;
	int		q_exist;
}				t_trt_her;

typedef struct s_herdocs
{
	char	*before_dollar;
	char	*env_name;
	char	*after_dollar;
	char	*tmp;
	int		i;
	size_t	len;
}				t_herdocs;

t_env			*create_env_list(t_env *lenv, char **env);
t_token_list	*ft_lexer(char *line);
char			*treat_heredocs(char *delimiter, t_env *lenv);
char			*check_name_hdc(char *buffer, int *k);
void			expand_herdocs(char **buffer, t_env *lenv);
char			*remove_quotes(char *delimiter, int *qt);
void			initial(t_trt_her *var, char **delimiter);
void			add_cmd(t_command *cmd, char **cmd_arg,
					t_redirection *redr, char *sep);
t_command		*initial_cmd(char **cmd_arg, t_redirection *redirection,
					char *sep);
void			add_separator(t_command *cmd, char *sep);
void			add_redirection(t_redirection *rdr, char *type, char *val,
					t_env *lenv);
t_redirection	*initial_redirection(char *type, char *value, t_env *lenv);
void			destroy_redirection_list(t_redirection *redirection);
int				tab_size(char **cmd_args);
void			create_cmd(t_parce *var);
void			free_env(t_env *lenv);
t_token_list	*initialize_list(void);
void			add_token(t_token_list *var, char *type, char *value);
char			*Treat_Quotes(int *index, char *line, char type);
void			quotes(char **token, int *k, char *line, char type);
char			*get_word(char *line, int *k);
void			get_symbole(t_token_list *var, char *line, int *index);
int				get_rl_symbole(t_token_list *var, char *line, int i);
int				get_rg_symbole(t_token_list *var, char *line, int i);
int				get_semi_symbole(t_token_list *var, char *line, int i);
int				get_pipe_symbole(t_token_list *var, char *line, int i);
void			display_token(t_token_list *var);
int				check_backslash(char *line, int i);
void			backslash_impair(char *line, char **token, int *k,
					int *backslash);
void			backslash_exist(char *line, char **token, int *k,
					int *backslash);
void			backslash_not_exist(char *line, char **token, int *k);
int				check_backslash_end(char *value);
int				check_syntax_error(t_token_list *old);
int				check_error(t_token_list *tokn_lst, t_token_list *old);
int				syntax_error_semi(t_token_list *token_semi, t_token_list *head);
int				syntax_error_word(t_token_list *token_word, t_token_list *head);
int				syntax_error_pipe(t_token_list *token_pipe, t_token_list *head);
int				syntax_error_redir(t_token_list *token_redir,
					t_token_list *head);
int				syntax_error_NONE(t_token_list *token_none, t_token_list *head);
void			destroy_list(t_token_list *lst);
void			display_error(char *value);
int				quotes_end(char *value, int *k);
int				single_quote_end(char *value, int *k);
int				check_quotes(char *value);
void			display_commands(t_command *cmd);
void			expanding(t_command *cmd, t_env *env_lst);
void			expand_name(char *comd, int *k, char type);
int				check_name(char **comd, int *k, char **name, char type_f);
void			name_empty(char **comd, char *old_comd, size_t *k);
char			*take_dollar_name(char *comd, int *k, t_env *envl, int type);
void			destroy_redirection_list(t_redirection *redirection);
t_command		*ft_parse(t_token_list *token_list, t_env *lenv);
void			free_list(t_token_list *var);
void			ft_new_str(char *str, int index);
char			*get_dollar_name(char *command, int *j);
size_t			dollar_val(char **comd, char *name, char *old_comd,
					t_env *envl);
void			dollar_q(char **comd, char *old_comd, size_t *k);
void			dollar_zero(char **comd, char *old_comd, size_t *k);
char			*after_dollar_value(char *command1, int i);
int				expand_single_quote(char *str, int index);
int				expand_double_quotes(char **str, int index, t_env *env_list);

#endif