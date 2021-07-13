NAME = minishell

CFLAGS = -Wall -Wextra -Werror

src = shell.c get_symbole.c backslash.c t_word.c\
		lexer.c expanding.c parse.c env.c

libft = ./libft/libft.a

HDRS = ./minishell.h

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