/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 10:48:41 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/24 17:20:11 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void real_exit_status(t_tree *tree, t_env_var  **env_vars)
{
    int status;
    char *argument = tree->data.argv[0];

    int real_status;
    status  = ft_atoi(argument);
    real_status = status % 256;
    *((*env_vars)->status) = real_status;
    printf("%d", *((*env_vars)->status));
    exiting(tree, env_vars, 1);
}

void exiting(t_tree *tree, t_env_var **env_vars, int exit_printing)
{   
    if(exit_printing)
        printf("exit\n"); 
    ft_free_tree(tree);
    gc_malloc(0, 0);
    gc_malloc(0, 1);
    exit(*(*env_vars)->status);
}
static void exit_argument_parssing(t_tree *tree, t_env_var  **env_vars)
{ 
    int i;
    char **command = tree->data.argv;
    
    i = 0;
    if(command[0] && command[1] && command[2])
    {
        printf("exit\nexit: too many arguments\n");
        *(*env_vars)->status = 1;
        printf("%d", *((*env_vars)->status));
        exiting(tree, env_vars,0);
    }
    else if(command[0] && command[1])
    {
        while(command[1][i])
        {
            if(!ft_is_a_numb(command[1][i]))
            {
                printf("exit\n");
                printf("bash: exit: %s: numeric argument required\n",command[1]);
                *(*env_vars)->status = 2;
                printf("%d", *((*env_vars)->status));
                exiting(tree, env_vars,0);
            }
            i++;    
        }
        real_exit_status(tree, env_vars);          
    }   
}
void exit_execution(t_tree *tree,t_env_var **env_vars)
{
    char **command = tree->data.argv;
    
    exit_argument_parssing(tree, env_vars);
    if(command[0] && command[1] == NULL)
    {
        printf("%d", *((*env_vars)->status));
        exiting(tree, env_vars,1);
    }
}