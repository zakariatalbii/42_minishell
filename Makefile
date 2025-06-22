LIBFT = libft/libft.a
LIBFT_H = libft/libft.h

SRC = show_the_tree.c \
		test.c ft_signals.c utils.c \
		parsing/ft_parser.c parsing/ft_lexer.c parsing/ft_split_line.c parsing/ft_token.c \
		parsing/ft_tokenlen.c parsing/ft_expand_token.c parsing/ft_empty_token.c \
		parsing/ft_tree_node.c parsing/ft_heredoc.c parsing/ft_free_tree.c parsing/utils.c \
		execution/execution_entry.c execution/built_ins/echo.c execution/built_ins/env/var_restoring.c \
		execution/built_ins/env/env.c execution/built_ins/utils.c execution/built_ins/pwd.c \
		execution/built_ins/cd/cd.c execution/built_ins/unset.c \
		execution/built_ins/export/export.c execution/built_ins/export/export_parsing.c \
		execution/built_ins/export/export_change_handling.c execution/built_ins/cd/cd_extra.c \
		execution/external_commands/external_helpers.c execution/external_commands/external_commands.c execution/pipe_line.c \
		execution/redirection.c 

OBJ = $(SRC:.c=.o)

NAME = minishell

CC = cc -Wall -Wextra -Werror #-fsanitize=address
RM = rm -f

%.o: %.c minishell.h $(LIBFT_H)
	$(CC) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	make -C libft all bonus

clean:
	make -C libft clean
	$(RM) $(OBJ)

fclean: clean
	make -C libft fclean
	$(RM) $(NAME)

re: fclean all
