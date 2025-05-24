/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:51:47 by zatalbi           #+#    #+#             */
/*   Updated: 2025/05/24 19:59:36 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

# define MAX_HEREDOC 16

/* *** token types *** */
# define STR 0
# define PIPE 1
# define INRED 2
# define OUTRED 3
# define HEREDOC 4
# define OUTRED_A 5
# define CMD STR

/* *************** lexing *************** */

/* *** token struct *** */
typedef struct s_token
{
	char	*token;
	int		type;
}	t_token;

/* *** lexer *** */
t_list	*ft_lexer(char *line, int status);
t_list	*ft_split_line(char *line);
size_t	ft_tokenlen(char *str, int status, int flag);
void	ft_expand_token(char *dst, char *src, int status, int flag);
int		ft_empty_token(t_list **list, t_list **head, char *str, int ptype);

/* *** token *** */
t_token	*ft_new_token(char *token);
void	ft_free_token(void *ptr);

/* *** utils *** */
char	*ft_strndup(const char *s1, size_t n);
char	*ft_getenv(const char *name, size_t len);

/* ************************************** */

/* *************** parsing ************** */

/* *** file union *** */
typedef union u_file
{
	char	*name;
	int		fd;
}	t_file;

/* *** tree struct *** */
typedef struct s_tree
{
	union	u_data
	{
		char	**argv;
		struct s_red
		{
			struct s_tree	*ntree;
			t_file			file;
		}	red;
		struct s_pipe
		{
			struct s_tree	*rtree;
			struct s_tree	*ltree;
		}	pipe;
	}	data;
	int	type;
}	t_tree;

/* *** parser *** */
t_tree	*ft_parser(char *line, int status);
char	**ft_argv(t_list *lst);
t_tree	*ft_cmd_node(char **argv);
t_tree	*ft_red_node(int type, t_file file, t_tree *ntree);
t_tree	*ft_pipe_node(t_tree *rtree, t_tree *ltree);

/* *** heredoc *** */
int		ft_heredoc(char **delimiter, int status, int flag);
void	ft_store_fd(int fd);

/* *** free the tree *** */
void	ft_free_tree(t_tree *tree);
void	ft_free_argv(char **argv);

/* ************************************** */

#endif