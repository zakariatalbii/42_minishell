
LIBFT = libft/libft.a
LIBFT_H = libft/libft.h

SRC = test.c ft_parser.c ft_lexer.c ft_tree_node.c ft_split_line.c ft_tokenlen.c \
	ft_expand_token.c ft_empty_token.c ft_heredoc.c ft_token.c ft_free_tree.c utils.c \
	execution/execution_entry.c execution/built_ins/echo.c execution/built_ins/env.c \
	execution/built_ins/utils.c execution/built_ins/pwd.c execution/built_ins/cd/cd.c execution/built_ins/unset.c \
	execution/built_ins/export/export.c execution/built_ins/export/export_parsing.c \
	execution/built_ins/export/export_change_handling.c execution/built_ins/cd/cd_extra.c \
	execution/external_commands/external_helpers.c execution/external_commands/external_commands.c execution/pipe_line.c \

OBJ = $(SRC:.c=.o)

NAME = minishell

CC = cc #-fsanitize=address -Wall -Wextra -Werror
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
