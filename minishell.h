/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:51:47 by zatalbi           #+#    #+#             */
/*   Updated: 2025/05/30 13:23:35 by wnid-hsa         ###   ########.fr       */
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
#include <sys/wait.h>
#include <signal.h>


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

# define PATH_ "PATH=/home/wnid-hsa/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/home/wnid-hsa/.local/bin"
# define PWD_ "/home/wnid-hsa/Desktop/our_minishell"
# define OLDPWD_ "/home/wnid-hsa/Desktop"
 
typedef struct s_environ
{
	char *var;
	char *operator;
	char *value;
	struct s_environ *next;
} t_environ;

int	ft_strcmp(const char *s1, const char *s2);
void cd_execution(char **command, char **PWD, t_environ **environ, char **OLDPWD);
void echo_execution(char **command);
void executing_env(t_environ **environ);
t_environ  *ft_lstnew_environ(char *str);
void	ft_lstadd_back_environ(t_environ **lst, t_environ *new);
t_environ *making_the_environ_struct(void);
void  pwd_execution(char **command, char **PWD);
void recursion(t_tree *tree, char **pwd, char **OLDPWD);
void unset_executing(char **command, t_environ **environ);
void export_execution(char **command, t_environ **environ, char **PWD);
int is_the_var_in_environ(char *variable, t_environ *environ);
char  **split_environ(char *str);
void fill_in_var(char **var, char *str);
int valid_position_export(char *str);
int var_name_end(char *str);
int valid_var_name(char *str, int count);
int ft_is_a_numb(char c);
int is_while_space(char c);
void make_export_struct(char **command, t_environ **environ, char **PWD);
void  cd_oldpwd(t_environ **environ, char **PWD, char **OLDPWD);
char *telda_full_path(char *telda_path);
int is_home_set(t_environ **environ);
void changing_nodes(t_environ **environ, char *var , char *new_value);
int  check_existans_and_permisisons(char *command);
void external_commands_execution(char **command,t_environ **environ);
char	**potential_path(char *command);
void execution_entery(char **command, char **PWD, char **OLDPWD);

#endif