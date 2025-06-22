/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:51:47 by zatalbi           #+#    #+#             */
/*   Updated: 2025/06/22 02:10:55 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE
# define _POSIX_C_SOURCE 199309L
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <errno.h>
# include <sys/wait.h>
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
int		ft_heredoc(char **delimiter, int status);
void	ft_store_fds(int fd);

/* *** free the tree *** */
void	ft_free_tree(t_tree *tree);
void	ft_free_argv(char **argv);

/* ************************************** */

/* *************** signals ************** */

typedef struct sigaction	t_sigaction;

void	ft_signals(int flag);
int		ft_heredoc_i(int f, int *fds);

/* ************************************** */

/* **************** main **************** */

/* *** utils *** */
int		ft_count_lines(int flag);
int		ft_status(int s);

/* ************************************** */

/* **************** exec **************** */

# define PATH_ "/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:"

typedef struct s_environ
{
	char				*var;
	char				*operator;
	char				*value;
	struct s_environ	*next;
}	t_environ;

typedef struct s_env_var
{
	char				*pwd;
	char 				*oldpwd;
	int					*status;
	int					*env_flag;
}	t_env_var;

int		ft_strcmp(const char *s1, const char *s2);
void	cd_execution(char **command, char **PWD, t_environ **environ, char **OLDPWD, int *status);
void	echo_execution(char **command, int *status);

t_environ	*ft_lstnew_environ(char *str);
void	ft_lstadd_back_environ(t_environ **lst, t_environ *new);
t_environ	*making_the_environ_struct(int *flag, char *pwd);
void	pwd_execution(char **command, char **PWD, int *status);
// void	recursion(t_tree *tree, t_env_var **env_vars);
void	recursion(t_tree *tree, char **PWD, char **OLDPWD, int *status);
void	unset_executing(char **command, t_environ **environ, int *status);
int		is_the_var_in_environ(char *variable, t_environ *environ);
char	**split_environ(char *str);
void	fill_in_var(char **var, char *str);
int		valid_position_export(char *str, int *status);
int		var_name_end(char *str);
int		valid_var_name(char *str, int count);
int		ft_is_a_numb(char c);
int		is_while_space(char c);
void	make_export_struct(char **command, t_environ **environ, char **PWD, int *status);
void  	cd_oldpwd(t_environ **environ, char **PWD, char **OLDPWD, int *status);
char	*telda_full_path(char *telda_path);
int		is_it_set(t_environ **environ, char *path);
void	changing_nodes(t_environ **environ, char *var, char *new_value);
int 	check_existans_and_permisisons(char *command, int *status);
void	external_commands_execution(char **command, t_environ **environ, int *status);
char	**potential_path(char *command);
void	no_pipe_execution(char **command, char **PWD, char **OLDPWD, t_environ *environ, int *status);
void	error_handling(int return_value,char *failed_function);
void	infile_handling(t_tree *tree, char **PWD, char **OLDPWD, int *status);
void	outfile_handling(t_tree *tree, char **PWD, char **OLDPWD, int *status);
void	heredoc_handling(t_tree *tree, char **PWD, char **OLDPWD, int *status);
void	append_handling(t_tree *tree, char **PWD, char **OLDPWD, int *status);
void 	execute_the_builtin(char **command, char **PWD, t_environ **s_environ, char **OLDPWD, int *status);
int  	is_built_in(char **command);
void	executing_env(t_environ **environ,int *status);
void	export_execution(char **command, t_environ **environ, char **PWD, int *status);
void	cd_errno_handling(int ernum, char *path);
char 	*restore_user(char *pwd);
char	*restore_path(char *pwd);
void	restore_variables(t_environ **s_environ, char *pwd);
/* ************************************** */

#endif