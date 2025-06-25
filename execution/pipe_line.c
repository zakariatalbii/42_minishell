/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:14:26 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/25 23:34:07 by wnid-hsa         ###   ########.fr       */
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
static void pipe_line(t_tree *tree, t_env_var **env_vars)
{
    int fd[2];
    int pid[2];
    int status_1;
    int status_2;
    
    (1 && pipe(fd), (pid[0] = fork()), error_handling(pid[0], "fork"));
    if (pid[0] == 0)
    {
        error_handling(close(fd[0]), "close");
        error_handling(dup2(fd[1], STDOUT_FILENO), "dup2");
        error_handling(close(fd[1]), "close");
        recursion(tree->data.pipe.rtree, env_vars);
        //gc_malloc(0,0);
        exit(*(*(env_vars))->status);
    }
    (1 && (pid[1] = fork()), error_handling(pid[1], "fork"));
    if (pid[1] == 0) 
    {
        printf("im here\n");
        error_handling(close(fd[1]), "close");
        error_handling(dup2(fd[0], STDIN_FILENO), "dup2");
        error_handling(close(fd[0]), "close");
        recursion(tree->data.pipe.ltree, env_vars);
        //gc_malloc(0,0);
        exit(*(*(env_vars))->status);
    }
    error_handling(close(fd[0]), "close");
    error_handling(close(fd[1]), "close");
    waitpid(pid[0], &status_1, 0);
    waitpid(pid[1], &status_2, 0);
    
    printf("DEBUG: status_1=%d, status_2=%d\n", status_1, status_2);
    printf("DEBUG: WEXITSTATUS(status_2)=%d\n", WEXITSTATUS(status_2));
    if (status_2 != 0) 
        *(*(env_vars))->status = status_2 >> 8;  // CHANGED: Extract exit code from status_2
    else 
        *(*(env_vars))->status = 0;
    
}

static void command_execution(t_tree *tree, int flag, t_env_var **env_vars)
{
    
    int pid;
    static t_environ *environ;
    int status_1;
    int flag_;

    flag_ = 0;

    if(!environ)
        environ = making_the_environ_struct(&flag_, env_vars);
    if(flag == 0)
    {
        if(is_built_in(tree->data.argv) == 1)
        {
            execute_the_builtin(tree, &environ, env_vars, 1);
        }
        else
        {
            pid = fork();
            error_handling(pid, "close");
            if(pid == 0)
            {
                printf("im here\n");
                external_commands_execution(tree->data.argv,&environ, env_vars);
            }
            waitpid(pid,&status_1,0);
            if (status_1 != 0) 
                *(*(env_vars))->status = status_1 >> 8;  // CHANGED: Extract exit code from status_2
            else 
                *(*(env_vars))->status = 0;
        }
    }    
    // else
    //     no_pipe_execution(tree, environ, env_vars, 0);
    
}


void recursion(t_tree *tree,t_env_var **env_vars)
{   
    static int flag;

   
    if (!tree) 
        return;
    if (tree->type == 0)
    { 
        command_execution(tree, flag, env_vars);
        (*env_vars)->last_command = custom_strdup(tree->data.argv[0],1);
    }
    else if (tree->type == 1)
    {   
        // flag =1;
        pipe_line(tree, env_vars);
    }
    else if (tree->type == 2)
        infile_handling(tree, env_vars);
    else if (tree->type == 3)
    {
        outfile_handling(tree, env_vars);
    }
    else if (tree->type == 4)
        heredoc_handling(tree, env_vars);
    else if(tree->type == 5)
        append_handling(tree, env_vars);
}
