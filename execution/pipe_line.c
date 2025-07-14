/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:14:26 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/13 23:52:04 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void error_handling(int return_value,char *failed_function)
{
    if(return_value==-1)
    {
        if(!strcmp(failed_function, "close"))
            perror("close failed\n");
        if(!strcmp(failed_function, "dup2"))
            perror("dup2 failed\n");
        if(!strcmp(failed_function, "fork"))
            perror("fork failed\n");
        if(!strcmp(failed_function, "dup"))
            perror("dup failed\n");
        if(!strcmp(failed_function, "open"))
            perror("open failed\n");
        // gc_malloc(0,0);
        // exit(1);
    }
} 
static void pipe_line(t_tree *tree,t_env **environ, t_env_var **env_vars)
{
    int fd[2];
    int pid[2];
    int status_1;
    int status_2;
    
    (1 && (pipe(fd)), (pid[0] = fork()), (error_handling(pid[0], "fork")));
    if (pid[0] == 0)
    {
        signal(SIGINT,SIG_DFL);
        signal(SIGQUIT,SIG_DFL);
        error_handling(close(fd[0]), "close");
        error_handling(dup2(fd[1], STDOUT_FILENO), "dup2");
        error_handling(close(fd[1]), "close");
        recursion(tree->data.pipe.rtree,environ ,env_vars);
        //gc_malloc(0,0);
        exit(*(*(env_vars))->status);
    }
    (1 && (pid[1] = fork()), (error_handling(pid[1], "fork")));
    if (pid[1] == 0) 
    {
        signal(SIGINT,SIG_DFL);
        signal(SIGQUIT,SIG_DFL);
        error_handling(close(fd[1]), "close");
        error_handling(dup2(fd[0], STDIN_FILENO), "dup2");
        error_handling(close(fd[0]), "close");
        recursion(tree->data.pipe.ltree,environ, env_vars);
        //gc_malloc(0,0);
        exit(*(*(env_vars))->status);
    }
    error_handling(close(fd[0]), "close");
    error_handling(close(fd[1]), "close");
    waitpid(pid[0], &status_1, 0);
    waitpid(pid[1], &status_2, 0);
    if(WCOREDUMP(status_2))
            printf("Quit (core dumped)\n");
    if (status_2 != 0) 
        *(*(env_vars))->status = status_2 >> 8; 
    else 
        *(*(env_vars))->status = 0;

}

static void command_execution(t_tree *tree,t_env **environ ,int flag, t_env_var **env_vars)
{
    int pid;
    int status_1;

    if(is_built_in(tree->data.argv) == 1)
    {
        
        execute_the_builtin(tree, environ, env_vars, flag);
    }
    else
    {
        pid = fork();
        error_handling(pid, "close");
        if(pid == 0)
        {
            signal(SIGINT,SIG_DFL);
            signal(SIGQUIT,SIG_DFL);
            external_commands_execution(tree->data.argv,environ, env_vars);
        }
        waitpid(pid,&status_1,0);
        if(WCOREDUMP(status_1))
            printf("Quit (core dumped)\n");
        if (status_1 != 0) 
        {
            *(*(env_vars))->status = status_1 >> 8; 
        }
        else 
            *(*(env_vars))->status = 0;
    }    
}
static void change_lst_arg_(char *last_arg ,t_env **environ)
{

    char *lst_arg;
    
    // while(current)
    // {
    //     if(!ft_strcmp(current->var, "_"))
    //     {
    //         if(!ft_strcmp(last_arg,"env"))
    //           last_arg = "/usr/bin/env";
    //         current->val = custom_strdup(last_arg,1);
    //     }
    //     current = current ->next; 
    // }
    if(!ft_strcmp(last_arg,"env"))
        lst_arg = "/usr/bin/env";
    else
        lst_arg = custom_strdup(last_arg,1);
    // save_node_changes(environ, "_", lst_arg);
}

void last_command_arg(t_tree *tree, t_env **environ)
{
    char **args;
    char *last_arg;
    int i;
    
    i = 0;
    if(tree)
        args = tree->data.argv;
    if(!args)
        return;
    while(args && args[i])
    {
        i++;
    }
    last_arg =args[i-1];
    change_lst_arg_(last_arg ,environ);
}

void recursion(t_tree *tree,t_env **environ,t_env_var **env_vars)
{   
    int flag;

   flag = 0;
    if (!tree) 
        return;
    if (tree->type == 0 && tree->data.argv && tree->data.argv[0])
    { 
        last_command_arg(tree, environ);
        command_execution(tree,environ,flag,env_vars);
        // (*env_vars)->last_command = custom_strdup(tree->data.argv[0],1);
    }
    else if (tree->type == 1)
    {   
        flag =1;
        pipe_line(tree,environ,env_vars);
    }
    else if (tree->type == 2)
        infile_handling(tree,environ,env_vars);
    else if (tree->type == 3)
    {
        outfile_handling(tree,environ,env_vars);
    }
    else if (tree->type == 4)
        heredoc_handling(tree,environ,env_vars);
    else if(tree->type == 5)
        append_handling(tree,environ,env_vars);
}

