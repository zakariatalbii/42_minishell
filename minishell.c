/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:51:16 by zatalbi           #+#    #+#             */
/*   Updated: 2025/07/27 16:02:25 by zatalbi          ###   ########.fr       */
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
	if(!(*env_vars)->export_PATH || !(*env_vars)->export_ || !(*env_vars)->export_OLDPWD || !(*env_vars)->last_command )
		return;

}
t_env_var	*env_var_initialization(void)
{
	t_env_var *env_vars;
	char	*cwd;
	
	cwd = getcwd(NULL, 0);
	env_vars = gc_malloc(sizeof(t_env_var),1);
	if(!env_vars || !cwd)
		return(NULL);
	else
	{
		env_vars->env_flag = (int *)gc_malloc(sizeof(int),1);
		if(env_vars->env_flag)
			*(env_vars->env_flag) = 0;
		env_vars->status = (int *)gc_malloc(sizeof(int),1);
		if(env_vars->status)
			*(env_vars->status) = 0;
		
		if(!env_vars->env_flag || !env_vars->status)
			return(free(cwd),NULL);
		env_vars->pwd = custom_strdup(cwd, 1);
		
		export_flags_initialization(&env_vars);
		return(free(cwd),env_vars);
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

int	main(void)
{
	t_tree		*tree;
	char		*line;
	t_env_var	*env_vars;
	t_env		**env;

	env_vars = env_var_initialization();
	ft_signals(1);
	if (!ft_environ(&env, ft_envinit(), 1))
		return (gc_malloc(0, 0), gc_malloc(0, 1), 1);
	while (1)
	{
		line = ft_readline(env_vars);
		if (!line)
			return (printf("exit\n"), gc_malloc(0, 0), gc_malloc(0, 1),
				clear_history(), ft_environ_clear(), ft_status(-1));
		tree = ft_parser(line, ft_status(-1));
		recursion(tree, env, &env_vars);
		ft_free_tree(tree);
		free(line);
	}
}
