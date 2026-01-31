LIBFT_L = libft/libft.a

LIBFT_I = -Ilibft/include

LIBFT_H = libft/include/libft.h

LIBFT_S = libft/src/ft_isalpha.c libft/src/ft_isdigit.c libft/src/ft_isalnum.c libft/src/ft_isascii.c \
			libft/src/ft_isprint.c libft/src/ft_strlen.c libft/src/ft_memset.c libft/src/ft_bzero.c \
			libft/src/ft_memcpy.c libft/src/ft_memmove.c libft/src/ft_strlcpy.c libft/src/ft_strlcat.c \
			libft/src/ft_toupper.c libft/src/ft_tolower.c libft/src/ft_strchr.c libft/src/ft_strrchr.c \
			libft/src/ft_strncmp.c libft/src/ft_memchr.c libft/src/ft_memcmp.c libft/src/ft_strnstr.c \
			libft/src/ft_atoi.c libft/src/ft_calloc.c libft/src/ft_strdup.c libft/src/ft_substr.c \
			libft/src/ft_strjoin.c libft/src/ft_strtrim.c libft/src/ft_split.c libft/src/ft_itoa.c \
			libft/src/ft_strmapi.c libft/src/ft_striteri.c libft/src/ft_putchar_fd.c libft/src/ft_putstr_fd.c \
			libft/src/ft_putendl_fd.c libft/src/ft_putnbr_fd.c libft/src/ft_lstnew_bonus.c \
			libft/src/ft_lstadd_front_bonus.c libft/src/ft_lstsize_bonus.c libft/src/ft_lstlast_bonus.c \
			libft/src/ft_lstadd_back_bonus.c libft/src/ft_lstdelone_bonus.c libft/src/ft_lstclear_bonus.c \
			libft/src/ft_lstiter_bonus.c libft/src/ft_lstmap_bonus.c

RL_L = -L$(HOME)/.brew/opt/readline/lib -lreadline

RL_I = -I$(HOME)/.brew/opt/readline/include

SRC = src/minishell.c src/ft_signals.c src/utils.c \
		src/environ/ft_env.c src/environ/ft_envinit.c src/environ/ft_environ.c \
		src/environ/ft_envp.c src/environ/ft_getenv.c src/environ/ft_setenv.c \
		src/parsing/ft_parser.c src/parsing/ft_lexer.c src/parsing/ft_split_line.c \
		src/parsing/ft_token.c src/parsing/ft_tokenlen.c src/parsing/ft_expand_token.c \
		src/parsing/ft_empty_token.c src/parsing/ft_split_token.c src/parsing/ft_qchar.c \
		src/parsing/ft_tokenlst.c src/parsing/ft_tokencmd.c src/parsing/ft_isspace.c \
		src/parsing/ft_tree_node.c src/parsing/ft_heredoc.c src/parsing/ft_free_tree.c \
		src/execution/execution_entry.c src/execution/built_ins/echo.c src/execution/built_ins/env/env.c \
		src/execution/built_ins/utils.c src/execution/built_ins/pwd.c src/execution/built_ins/cd/cd.c \
		src/execution/built_ins/unset.c src/execution/built_ins/export/export.c \
		src/execution/built_ins/export/export_parsing.c src/execution/built_ins/export/export_change_handling.c \
		src/execution/built_ins/cd/cd_extra.c src/execution/external_commands/external_helpers.c \
		src/execution/external_commands/external_commands.c src/execution/built_ins/export/export_utils.c \
		src/execution/allocation_freeing/custom_split.c src/execution/allocation_freeing/custom_strjoin.c \
		src/execution/allocation_freeing/gc_malloc.c src/execution/built_ins/exit/exit.c \
		src/execution/allocation_freeing/custom_strndup.c src/execution/built_ins/cd/cd_utils_1.c \
		src/execution/built_ins/cd/cd_utils_2.c src/execution/built_ins/cd/cd_utils_3.c \
		src/execution/built_ins/cd/cd_utils_4.c src/execution/built_ins/exit/exit_utils.c \
		src/execution/built_ins/export/export_utils_2.c src/execution/external_commands/external_commands_utils.c \
		src/execution/pipeline/pipe_line_1.c src/execution/pipeline/pipe_line_plus.c \
		src/execution/pipeline/pipe_line.c src/execution/redirection/redirection.c \
		src/execution/redirection/redirection_utils.c

OBJ = $(SRC:.c=.o)

NAME = minishell

CC = cc -Wall -Wextra -Werror

RM = rm -f

%.o: %.c include/minishell.h
	$(CC) -c $< -Iinclude $(LIBFT_I) $(RL_I) -o $@

all: $(NAME)

$(NAME): $(LIBFT_L) $(OBJ)
	$(CC) $(OBJ) $(LIBFT_L) $(RL_L) -o $(NAME)

$(LIBFT_L): $(LIBFT_S) $(LIBFT_H)
	make -C libft all bonus

clean:
	make -C libft clean
	$(RM) $(OBJ)

fclean: clean
	make -C libft fclean
	$(RM) $(NAME)

re: fclean all