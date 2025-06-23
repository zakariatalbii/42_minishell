/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:39:35 by zatalbi           #+#    #+#             */
/*   Updated: 2025/06/23 10:50:20 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void path_initialiation(t_env_var **env_vars)
{
	t_environ *new;
    char      *user;
    char      *path;
	
	if(restore_user((*env_vars)->pwd))
    {
        if(restore_path((*env_vars)->pwd))
        {
            user=restore_user((*env_vars)->pwd);
            path =restore_path(user);
            new = ft_lstnew_environ(path);
            (*env_vars)->PATH=new->value;
		}
	}
}
void export_flags_initialization(t_env_var **env_vars)
{
	(*env_vars)->export_PATH = (int *)malloc(sizeof(int));
	if((*env_vars)->export_PATH)
		*((*env_vars)->export_PATH) = 0;
	(*env_vars)->export_ = (int *)malloc(sizeof(int));
	if((*env_vars)->export_ )
		*((*env_vars)->export_) = 0;
	(*env_vars)->export_OLDPWD=(int *)malloc(sizeof(int));
	if((*env_vars)->export_OLDPWD)
		*((*env_vars)->export_OLDPWD)=0;
	path_initialiation(env_vars);
	
}
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
		if(getcwd(NULL,0))
			env_vars->pwd = ft_strdup(getcwd(NULL,0));
		if(getenv("OLDPWD"))
			env_vars->oldpwd = ft_strdup(getenv("OLDPWD"));
		export_flags_initialization(&env_vars);
		return(env_vars);
	}
}
int	main(void)
{
	t_tree	*tree;
	char *line;
	t_env_var *env_vars;
	
	// static char *PWD;
	// static char *OLDPWD;
	
	env_vars = env_var_initialization();
	// printf("%d\n", env_vars->env_flag);
	// printf("%d\n", env_vars->status);
	// printf("%s\n", env_vars->pwd);
	// printf("%s\n", env_vars->oldpwd);
	
	char	*prompt;
	// static int *status;

    // if(!status)
    // {
    //     status = malloc(sizeof(int));
    //     *status = 0;
    // }
	// PWD = getcwd(NULL,0);
	// OLDPWD = getenv("OLDPWD");
	
	while (1)
	{	
		prompt = ft_strjoin(env_vars->pwd, "> ");
		line = readline(prompt);
		if (!line)
			break ;
		add_history(line);
		tree = ft_parser(line, 1337);
		recursion(tree, &env_vars);
		ft_free_tree(tree);
		free(line);
	}
	rl_clear_history();
	exit(0);
}
