/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:51:47 by zatalbi           #+#    #+#             */
/*   Updated: 2025/08/02 16:33:13 by wnid-hsa         ###   ########.fr       */
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
# include <limits.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/stat.h>
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

/* *************** environ *************** */

extern char					**environ;

/* *** env struct *** */
typedef struct s_env
{
	char			*var;
	char			*val;
	struct s_env	*next;
}	t_env;

t_env		*ft_envnew(char *var, char *val, int varf, int valf);
void		ft_envadd(t_env **env, t_env *new);
int			ft_envsize(t_env *env);
void		ft_envclear(t_env **env);
t_env		*ft_envinit(void);
t_env		*ft_environ(t_env ***penv, t_env *env, int flag);
void		ft_environ_clear(void);
int			ft_setenv(char *var, char *val, int flag);
void		ft_unsetenv(char *var);
char		*ft_getenv(char *var);
char		*ft_getlenv(char *var, size_t len);
char		**ft_envp(void);
void		ft_envp_clear(char **envp);

/* *************************************** */

/* *************** lexing *************** */

/* *** token struct *** */
typedef struct s_token
{
	char	*token;
	int		type;
}	t_token;

/* *** lexer *** */
t_list		*ft_lexer(char *line, int status);
t_list		*ft_split_line(char *line);
size_t		ft_tokenlen(char *str, int status, int flag);
void		ft_expand_token(char *dst, char *src, int status, int flag);
int			ft_empty_token(t_list **list, t_list **head, char *str, int ptype);
int			ft_isspace(int c);

/* *** "expand with spaces" struct *** */
typedef struct s_qchar
{
	char	*fc;
	char	*lc;
}	t_qchar;

/* *** "expand with spaces" funcs *** */
int			ft_split_token(t_list **list, t_list **head, char *str, int *ptype);
t_qchar		*ft_qchar(char *str, int flag);
void		ft_qchar_add(char *str, int flag);
t_list		*ft_tokenlst(char *str);
char		*ft_tokencmd(t_list *lst, t_list *head);

/* *** token *** */
t_token		*ft_new_token(char *token);
void		ft_free_token(void *ptr);

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
t_tree		*ft_parser(char *line, int status);
char		**ft_argv(t_list *lst);
t_tree		*ft_cmd_node(char **argv);
t_tree		*ft_red_node(int type, t_file file, t_tree *ntree);
t_tree		*ft_pipe_node(t_tree *rtree, t_tree *ltree);

/* *** heredoc *** */
int			ft_heredoc(char **delimiter, int status);
void		ft_store_fds(int fd);

/* *** free the tree *** */
void		ft_free_tree(t_tree *tree);
void		ft_free_argv(char **argv);

/* ************************************** */

/* *************** signals ************** */

typedef struct sigaction	t_sigaction;

void		ft_signals(int flag);
int			ft_heredoc_i(int f, int *fds);

/* ************************************** */

/* **************** main **************** */

/* *** utils *** */
int			ft_count_lines(int flag);
int			ft_status(int s);
int			ft_strcmp(const char *s1, const char *s2);
char		*ndup(const char *s1, size_t n);
char		*ft_strsjoin(char **strs);

/* ************************************** */

/* **************** exec **************** */

# define PATH_ "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

typedef struct s_environ
{
	char				*var;
	char				*operator;
	char				*value;
	struct s_environ	*next;
}	t_environ;

typedef struct s_env_var
{
	char	*pwd;
	int		*export_;
	char	*last_command;
	int		*pid;
	char	*oldpwd;
	char	*home;
}	t_env_var;

typedef struct s_local_trash
{
	void					*point;
	struct s_local_trash	*next;
}					t_local_trash;

typedef struct s_global_trash
{
	void					*point;
	struct s_global_trash	*next;
}					t_global_trash;

void		cd_execution(char **command, t_env **environ, t_env_var **env_vars);
void		echo_execution(char **command);

t_environ	*ft_lstnew_environ(char *str);
void		ft_lstadd_back_environ(t_environ **lst, t_environ *new);
void		pwd_execution(char **command, t_env_var **env_vars);
void		recursion(t_tree *tree, t_env **environ, t_env_var **env_vars);
void		unset_executing(char **command, t_env **environ);
int			is_the_var_in_environ(char *variable, t_env *environ);
char		**split_environ(char *str);
void		fill_in_var(char **var, char *str);
int			valid_position_export(char *str);
int			var_name_end(char *str);
int			valid_var_name(char *str, int count);
int			ft_is_a_numb(char c);
int			is_while_space(char c);
void		make_export_struct(char **command, t_env_var **env_vars);
void		cd_oldpwd(t_env **environ, t_env_var **env_vars, char **command);
char		*telda_full_path(char *telda_path, t_env_var **env_vars);
int			is_it_set(t_env **environ, char *path);
int			check_existans_and_permisisons(char *command);
void		external_commands_execution(char **command, t_env **environ,
				t_env_var **env_vars);
char		**potential_path(char *command);
int			ft_unset_flag(int flag);
void		error_handling(int return_value, char *failed_function, char *PATH);
void		infile_handling(t_tree *tree, t_env **environ,
				t_env_var **env_vars);
void		outfile_handling(t_tree *tree, t_env **environ,
				t_env_var **env_vars);

void		heredoc_handling(t_tree *tree, t_env **environ,
				t_env_var **env_vars);

void		append_handling(t_tree *tree, t_env **environ,
				t_env_var **env_vars);

void		execute_the_builtin(t_tree *tree, t_env **s_environ,
				t_env_var **env_vars, int pid);
int			is_built_in(char **command);
void		executing_env(char **command, t_env **environ);
void		export_execution(char **command, t_env **environ,
				t_env_var **env_vars);
void		cd_errno_handling(int ernum, char *path);
char		**splited_export_command(char *str);
void		export_flags_apdate(t_environ *new,t_env_var **env_vars);
char		**split_environ(char *str);
int			count_lengh_var_str_export(char *str);
void		handling_new_changes(t_environ **new, t_env_var **env_vars);
void		export_printing_conditions(t_env *current, t_env_var **env_vars);
void		printing_export(t_env *current);
void		*gc_malloc(size_t size, int pid);
char		*custom_strjoin(const char *s1, const char *s2, int pid);
char		**custom_split(const char *s, char c, int pid);
char		*custom_strdup(const char	*s1, int pid);
void		free_global_garbage(t_global_trash **global_trash);
void		free_local_garbage(t_local_trash **local_trash);
void		exit_execution(t_tree *tree, t_env_var **env_vars, int pid);
void		exit_execution(t_tree *tree, t_env_var **env_vars, int pid);
void		fd_input_directing(int fd_to, int fd_from);
char		*get_value(char *var, t_env *environ);
char		*custom_strndup(const char *s1, size_t n, int pid);
char		*ft_strndup(const char *s1, size_t n);
void		last_command_arg(t_tree *tree, t_env **environ);
int			count_words(const char *s, char c);
void		replace_node(t_environ **new, t_env_var **env_vars);
int			invalid_commands_checking(char *command, t_env **environ,
				t_env_var **env_vars);
int			there_is_slash(char *command, t_env **environ,
				t_env_var **env_vars);
int			stat_the_command(char *command);
char		*custom_strtrim(char const *s1, char const *set);
char		*custom_substr(char const *s, unsigned int start, size_t len);
void		print_msg(char *text1, char *text2, char *text3);
char		*get_deleted_path_gain(char *PWD, char *new);
char		*go_backwards(char *pwd);
int			count_two_points(char *new);
void		cd_points_handling(char **right_pwd, char *new, char *pwd);
char		*right_pwd(char *new, t_env_var **env_vars);
int			cd_flag(int flag_);
void		pwdinf_update(t_env_var **env_vars, char *path);
char		*trim_back_slach(char *new, char *pwd);
char		*escaped_path(char *pwd, int flag);
void		cd_deleted_path(char **right_pwd_, char *new,
				t_env_var **env_vars, int *flag);
long long	ft_lg__atoi(const char *str);
void		exiting(t_tree *tree, t_env_var **env_vars, int exit_printing);
void		real_exit_status(t_tree *tree, t_env_var **env_vars, int pid);
void		print_chr_str(char *text1, char c1, char c2, char *text2);
int			var_name_error(char *arg, int flag);
int			ft_unset_flag(int flag);
int			stat_plus(char *command, struct stat file_stat);
void		status_handling_chid(int *pid, int *fd, int status_2, int status_1);
void		status_handling(int status_1);	
void		change_lst_arg_(char *last_arg, t_env **environ);
int			outfiles_checking(t_tree *tree);
int			recursive_check(t_tree *tree);
void		last_command_arg(t_tree *tree, t_env **environ);
int			failed_redirection(int flag_);
void		fd_input_directing(int fd_to, int fd_from);
int			cd_old_flag(int flag_, char *path);
/* ************************************** */

#endif