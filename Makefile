LIBFT = libft/libft.a
LIBFT_H = libft/libft.h
LIBFT_SRC =	libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_isalnum.c libft/ft_isascii.c libft/ft_isprint.c libft/ft_strlen.c libft/ft_memset.c \
		libft/ft_bzero.c libft/ft_memcpy.c libft/ft_memmove.c libft/ft_strlcpy.c libft/ft_strlcat.c libft/ft_toupper.c libft/ft_tolower.c \
		libft/ft_strchr.c libft/ft_strrchr.c libft/ft_strncmp.c libft/ft_memchr.c libft/ft_memcmp.c libft/ft_strnstr.c libft/ft_atoi.c \
		libft/ft_calloc.c libft/ft_strdup.c libft/ft_substr.c libft/ft_strjoin.c libft/ft_strtrim.c libft/ft_split.c libft/ft_itoa.c \
		libft/ft_strmapi.c libft/ft_striteri.c libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_putendl_fd.c libft/ft_putnbr_fd.c \
		libft/ft_lstnew_bonus.c libft/ft_lstadd_front_bonus.c libft/ft_lstsize_bonus.c libft/ft_lstlast_bonus.c \
		libft/ft_lstadd_back_bonus.c libft/ft_lstdelone_bonus.c libft/ft_lstclear_bonus.c libft/ft_lstiter_bonus.c \
		libft/ft_lstmap_bonus.c

RL_LIB = -L./readline/lib -lreadline -lcurses
RL_H = -I./readline/include

SRC = show_the_tree.c \
		minishell.c ft_signals.c utils.c \
		environ/ft_env.c environ/ft_envinit.c environ/ft_environ.c \
		environ/ft_envp.c environ/ft_getenv.c environ/ft_setenv.c \
		parsing/ft_parser.c parsing/ft_lexer.c parsing/ft_split_line.c parsing/ft_token.c \
		parsing/ft_tokenlen.c parsing/ft_expand_token.c parsing/ft_empty_token.c \
		parsing/ft_split_token.c parsing/ft_qchar.c parsing/ft_tokenlst.c parsing/ft_tokencmd.c \
		parsing/ft_isspace.c parsing/ft_tree_node.c parsing/ft_heredoc.c parsing/ft_free_tree.c \
		execution/execution_entry.c execution/built_ins/echo.c \
		execution/built_ins/env/env.c execution/built_ins/utils.c execution/built_ins/pwd.c \
		execution/built_ins/cd/cd.c execution/built_ins/unset.c \
		execution/built_ins/export/export.c execution/built_ins/export/export_parsing.c \
		execution/built_ins/export/export_change_handling.c execution/built_ins/cd/cd_extra.c \
		execution/external_commands/external_helpers.c execution/external_commands/external_commands.c \
		execution/built_ins/export/export_utils.c execution/allocation_freeing/custom_split.c \
		execution/allocation_freeing/custom_strjoin.c execution/allocation_freeing/gc_malloc.c execution/built_ins/exit/exit.c \
		execution/allocation_freeing/custom_strndup.c execution/built_ins/cd/cd_utils_1.c execution/built_ins/cd/cd_utils_2.c \
		execution/built_ins/cd/cd_utils_3.c execution/built_ins/cd/cd_utils_4.c execution/built_ins/exit/exit_utils.c execution/built_ins/export/export_utils_2.c \
		execution/external_commands/external_commands_utils.c execution/pipeline/pipe_line_1.c execution/pipeline/pipe_line_plus.c \
		execution/pipeline/pipe_line.c execution/redirection/redirection.c execution/redirection/redirection_utils.c

OBJ = $(SRC:.c=.o)

NAME = minishell

CC = cc -Wall -Wextra -Werror -g -fsanitize=address
RM = rm -f

%.o: %.c minishell.h
	$(CC) $(RL_H) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIBFT) $(RL_LIB) -o $(NAME)

$(LIBFT): $(LIBFT_SRC) $(LIBFT_H)
	make -C libft all bonus

clean:
	make -C libft clean
	$(RM) $(OBJ)

fclean: clean
	make -C libft fclean
	$(RM) $(NAME)

re: fclean all
