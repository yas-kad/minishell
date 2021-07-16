NAME = minishell

CFLAGS = -Wall -Wextra -Werror

src = new_str.c add_cmd.c add_redir.c herdocs.c create_cmd_parce.c \
		shell.c get_symbole.c backslash.c t_word.c\
		lexer.c expanding.c parse.c env.c\
		syntax_error.c syntax_error_symb.c\
		quotes_error.c dollar_name.c print_error.c dollar_value.c\
		expand_quotes.c new_str.c add_cmd.c add_redir.c herdocs.c \
		execute/execute.c \
		execute/env_controle.c \
		execute/env_controle_2.c \
		execute/env_set_controle.c \
		execute/execute_pipes.c \
		execute/fork.c \
		execute/execute_redirections.c \
		builtins/builtin.c \
		builtins/builtin_cd.c \
		builtins/builtin_env.c \
		builtins/builtin_echo.c \
		builtins/builtin_pwd.c \
		builtins/builtin_unset.c \
		builtins/builtin_export.c \
		builtins/builtin_exit.c \


libft = ./libft/libft.a

HDRS = ./minishell.h # ./builtins/builtin.h ./execute/execute.h \
# 		./execute/env_controle.h

OBJ = $(src:.c=.o)

all : $(NAME)

$(NAME): $(OBJ)
	@make -sC libft
	@gcc $(CFLAGS) $^ $(libft) -o $(NAME) -lreadline $(LDFLAGS) -lncurses
	@echo "\033[1;32m                        _ _          _ \033[0m"
	@echo "\033[1;32m                       (_) |        | |\033[0m"
	@echo "\033[1;32m  ____ ___  ____  ____  _| | ____ _ | |\033[0m"
	@echo "\033[1;32m / ___) _ \|    \|  _ \| | |/ _  ) || |\033[0m"
	@echo "\033[1;32m( (__| |_| | | | | | | | | ( (/ ( (_| |\033[0m"
	@echo "\033[1;32m \____)___/|_|_|_| ||_/|_|_|\____)____|\033[0m"
	@echo "\033[1;32m                 |_|                   \033[0m"

%.o: %.c $(HDRS)
	@gcc $(CFLAGS) -c $< -o $@ $(CPPFLAGS)

clean:
	@rm -f $(OBJ)
	@make -sC libft clean

fclean: clean
	@rm -f $(NAME)
	@make -sC libft fclean
	@echo "\033[1;32m##########CLEANED SUCCESSFULY##########\033[0m"

re: fclean all

.PHONY: all clean fclean re