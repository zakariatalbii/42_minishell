/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:51:16 by zatalbi           #+#    #+#             */
/*   Updated: 2025/08/11 14:12:43 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	msh_error(int n)
{
	if (!n)
		ft_putendl_fd("minishell: too many arguments", 2);
	else if (n)
		ft_putendl_fd("minishell: invalid tty", 2);
	return (1);
}

static t_env_var	*env_var_initialization(void)
{
	t_env_var	*env_vars;
	char		*cwd;

	cwd = getcwd(NULL, 0);
	env_vars = gc_malloc(sizeof(t_env_var), 1);
	if (!env_vars || !cwd)
		return (NULL);
	else
	{
		env_vars->pwd = custom_strdup(cwd, 1);
		env_vars->export_ = (int *)gc_malloc(sizeof(int), 1);
		if (env_vars->export_)
			*(env_vars->export_) = 0;
		env_vars->pid = (int *)gc_malloc(sizeof(int), 1);
		if (env_vars->pid)
			*(env_vars->pid) = 1;
		env_vars->last_command = custom_strdup("PATH", 1);
		env_vars->oldpwd = NULL;
		if (!env_vars->pwd || !env_vars->export_
			|| !env_vars->last_command || !env_vars->pid)
			return (free(cwd), NULL);
		return (free(cwd), env_vars);
	}
}

static char	*ft_readline(t_env_var *env_vars)
{
	char	*line;
	char	*prompt;
	char	*cwd;

	cwd = (env_vars)->pwd;
	prompt = ft_strjoin(cwd, "$ ");
	if (!prompt)
		return (NULL);
	line = readline(prompt);
	if (line && *line)
		add_history(line);
	return (free(prompt), ft_count_lines(1), line);
}

int	main(int argc, char **argv)
{
	t_tree		*tree;
	char		*line;
	t_env_var	*env_vars;
	t_env		**env;

	(void)argv;
	if ((argc != 1 && msh_error(0))
		|| ((!isatty(0) || !isatty(1)) && msh_error(1)))
		exit(1);
	env_vars = env_var_initialization();
	ft_signals(1);
	if (!env_vars || !ft_environ(&env, ft_envinit(), 1))
		return (gc_malloc(0, 0), gc_malloc(0, 1), 1);
	while (1)
	{
		line = ft_readline(env_vars);
		if (!line)
			return (printf("exit\n"), gc_malloc(0, 0), gc_malloc(0, 1),
				clear_history(),
				ft_environ_clear(), ft_status(-1));
		tree = ft_parser(line, ft_status(-1));
		recursion(tree, env, &env_vars);
		(ft_store_fds(-1), ft_free_tree(tree), free(line));
	}
}
