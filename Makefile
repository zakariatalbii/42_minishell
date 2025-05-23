LIBFT = libft/libft.a

LIBFT_H = libft/libft.h

SRC = test.c ft_parser.c ft_tree.c ft_tree_node.c ft_expand_tokens.c ft_expand_token.c ft_tokenlen.c ft_split_line.c ft_free_tree.c ft_heredoc.c ft_token.c utils.c

OBJ = $(SRC:.c=.o)

NAME = test

CC =	cc -Wall -Wextra -Werror
RM =	rm -f

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
