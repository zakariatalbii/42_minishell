/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:51:16 by zatalbi           #+#    #+#             */
/*   Updated: 2025/07/07 18:02:47 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_the_tree(t_tree *tree);// for test

void export_flags_initialization(t_env_var **env_vars)
{
	(*env_vars)->export_PATH = (int *)gc_malloc(sizeof(int),1);
	if((*env_vars)->export_PATH)
		*((*env_vars)->export_PATH) = 0;
	(*env_vars)->export_ = (int *)gc_malloc(sizeof(int),1);
	if((*env_vars)->export_ )
		*((*env_vars)->export_) = 0;
	(*env_vars)->export_OLDPWD=(int *)gc_malloc(sizeof(int),1);
	if((*env_vars)->export_OLDPWD)
		*((*env_vars)->export_OLDPWD)=0;
	(*env_vars)->last_command =custom_strdup("a",1);
	// path_initialiation(env_vars);
	
}
t_env_var	*env_var_initialization(void)
{
	t_env_var *env_vars;
	char *var;

	env_vars = gc_malloc(sizeof(t_env_var),1);
	if(!env_vars)
		return(NULL);
	else
	{
		env_vars->env_flag = (int *)gc_malloc(sizeof(int),1);
		if(env_vars->env_flag)
			*(env_vars->env_flag) = 0;
		env_vars->status = (int *)gc_malloc(sizeof(int),1);
		if(env_vars->status)
			*(env_vars->status) = 0;
		// var = getcwd(NULL,0);
		// if(var)
		// {
		// 	env_vars->pwd = custom_strdup(var,1);
		// 	free(var);
		// }
		// var = getenv("OLDPWD");
		// if(var)
		// 	env_vars->oldpwd = custom_strdup(var,1);
		export_flags_initialization(&env_vars);
		return(env_vars);
	}
}

static char	*ft_readline(void)
{
	char	*line;
	char	*prompt;
	char	*cwd;

	cwd = ft_getenv("PWD");
	if (!cwd)
	{
		cwd = getcwd(NULL, 0);
		prompt = ft_strjoin(cwd, "$ ");
		free(cwd);
	}
	else
		prompt = ft_strjoin(cwd, "$ ");
	if (!prompt)
		return (NULL);
	line = readline(prompt);
	if (line && *line)
		add_history(line);
	return (free(prompt), ft_count_lines(1), line);
}

int	main(void)
{
	t_tree	*tree;
	char	*line;
	t_env_var *env_vars;


	env_vars = env_var_initialization();
	ft_signals(1);
	if (!ft_environ(ft_envinit(), 1))
		exit(1);
	while (1)
	{
		line = ft_readline();
		if (!line)
			break ;
		tree = ft_parser(line, ft_status(-1));
		recursion(tree, &env_vars);
		show_the_tree(tree);// for test
		ft_free_tree(tree);
		free(line);
	}
	rl_clear_history();
	ft_environ_clear();
	exit(ft_status(-1));
}
