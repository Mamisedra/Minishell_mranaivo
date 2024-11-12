NAME = minishell
CC= cc
FLAGS = -Wall -Wextra -Werror -g
PFLAGS = -lreadline
RM = rm -rf
SRCS =  srcs/parsing/main.c  srcs/parsing/utlis.c srcs/parsing/clean_code.c srcs/parsing/lexer.c  srcs/parsing/parsing.c\
		srcs/parsing/shell_list.c  srcs/parsing/print_parsing.c srcs/parsing/parsing_utils.c\
		srcs/parsing/token_list.c srcs/parsing/check_syntax.c srcs/parsing/code_status.c srcs/parsing/libft.c srcs/parsing/pipe_file.c\
		srcs/expand/expand_list.c srcs/expand/expand_shell.c srcs/expand/parse_expand.c srcs/expand/expand_env.c srcs/expand/expand_utils.c
OBJS = ${SRCS:.c=.o}
LIB_DIR = ./lib/libft/

all:${NAME}

.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}

libft:
	@printf "\033[1;33m \t Compilatiion libft \033[0m\n"
	@make -C ${LIB_DIR}

${NAME}: ${OBJS} libft
	@${CC} ${OBJS} ${LIB_DIR}/libft.a ${PFLAGS} -o ${NAME}
	@printf "\033[1;33m \t 🏁 Compilation Success 🏁 \033[0m\n"
	@printf "\033[3;32m \t 🆗 Run ./minishell 🆗\033[0m\n"

clean:
	@${RM} ${OBJS}
	@make clean -C ${LIB_DIR}
fclean: clean
	@${RM} ${NAME} .vscode
	@make fclean -C ${LIB_DIR}
addc:
	@git add includes/ srcs/ Makefile lib/
	@printf "\033[3;32m \t Ajout vers vogsphere Success \033[0m\n"

addm:
	@git add includes/ srcs/ documents Makefile
	@printf "\033[3;32m \t Ajout vers github Success \033[0m\n"
run:
	@make re && make clean
	@clear
	@valgrind --track-origins=yes --leak-check=full --suppressions=readline_suppr.supp ./minishell
valgrind:
	@valgrind --track-origins=yes --leak-check=full --suppressions=readline_suppr.supp -s ./minishell
re : fclean all
.PHONY: all re fclean clean
