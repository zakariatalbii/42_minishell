/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:39:35 by zatalbi           #+#    #+#             */
/*   Updated: 2025/06/22 02:11:54 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*env_var_initialization(void)
{
	t_env_var *env_vars;

	env_vars = malloc(sizeof(t_env_var));
	if(!env_vars)
		return(NULL);
	else
	{
		env_vars->env_flag = (int *)malloc(sizeof(int));
		if(env_vars->env_flag)
			*(env_vars->env_flag) = 0;
		env_vars->status = (int *)malloc(sizeof(int));
		if(env_vars->status)
			*(env_vars->status) = 0;
		env_vars->pwd = getcwd(NULL,0);
		env_vars->oldpwd = getenv("OLDPWD");
		return(env_vars);
	}
}
int	main(void)
{
	t_tree	*tree;
	char *line;
	// t_env_var *env_vars;
	
	static char *PWD;
	static char *OLDPWD;
	
	// env_vars = env_var_initialization();
	// printf("%d\n", env_vars->env_flag);
	// printf("%d\n", env_vars->status);
	// printf("%s\n", env_vars->pwd);
	// printf("%s\n", env_vars->oldpwd);
	
	char	*prompt;
	static int *status;

    if(!status)
    {
        status = malloc(sizeof(int));
        *status = 0;
    }
	PWD = getcwd(NULL,0);
	OLDPWD = getenv("OLDPWD");
	
	while (1)
	{	
		prompt = ft_strjoin(PWD, "> ");
		line = readline(prompt);
		if (!line)
			break ;
		add_history(line);
		tree = ft_parser(line, 1337);
		recursion(tree,&PWD,&OLDPWD, status);
		ft_free_tree(tree);
		free(line);
	}
	rl_clear_history();
	exit(0);
}
