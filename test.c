/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:39:35 by zatalbi           #+#    #+#             */
/*   Updated: 2025/07/01 21:05:52 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int g_ack;

// void path_initialiation(t_env_var **env_vars)
// {
// 	t_environ *new;
//     char      *user;
//     char      *path;
	
// 	if(restore_user((*env_vars)->pwd))
//     {
//         if(restore_path((*env_vars)->pwd))
//         {
//             user=restore_user((*env_vars)->pwd);
//             path =restore_path(user);
//             new = ft_lstnew_environ(path);
//             (*env_vars)->PATH=new->value;
// 		}
// 	}
// }
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
void handler(int signal)
{
	if(signal == 2)
	{
		g_ack = 1;
		write(1,"\n",1);
        rl_on_new_line();
		rl_replace_line("", 0);
        rl_redisplay(); 
	}
}

int	main(void)
{
	t_tree	*tree;
	char *line;
	t_env_var *env_vars;
	char	*prompt;
	struct sigaction sa;

	
	env_vars = env_var_initialization();
	signal(SIGQUIT,SIG_IGN);	
	while (1)
	{
		sigemptyset(&sa.sa_mask); 
    	sa.sa_handler = handler; 
		sigaction(SIGINT, &sa, NULL);
		prompt = custom_strjoin(env_vars->pwd, "> ", 1);
		line = readline(prompt);
		if (!line)
		{
			printf("exit\n");
			gc_malloc(0, 0);
			gc_malloc(0, 1);
			break ;
		}
		if(g_ack == 1)
		{
			free(line);
			g_ack = 0;
			continue;
		}
		signal(SIGINT, SIG_IGN);
		add_history(line);
		tree = ft_parser(line, 1337);
		recursion(tree, &env_vars);
		ft_free_tree(tree);
		free(line);
		gc_malloc(0, 0);
	}
	rl_clear_history();
	exit(0);
}
