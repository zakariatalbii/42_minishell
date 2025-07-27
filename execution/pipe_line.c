/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 13:14:26 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/26 05:33:28 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void error_handling(int return_value,char *failed_function, char *path)
{
    if(return_value==-1)
    {
        if(!ft_strcmp(failed_function, "close"))
            perror("close failed");
        if(!ft_strcmp(failed_function, "dup2"))
            perror("dup2 failed");
        if(!ft_strcmp(failed_function, "fork"))
            perror("fork failed");
        if(!ft_strcmp(failed_function, "dup"))
            perror("dup failed");
        if(!ft_strcmp(failed_function, "open"))
        {
            if (errno == ENOENT)
            {
                ft_putstr_fd("minishell: ",2);
                ft_putstr_fd(path, 2);
                ft_putstr_fd(": No such file or directory\n", 2);
                ft_status(1);
            }
            else if (errno == EACCES)
            {
                ft_putstr_fd("minishell: ",2);
                ft_putstr_fd(path, 2);
                ft_putstr_fd(": Permission denied\n",2);
                ft_status(1);
            }
        }
    }
} 
static void pipe_line(t_tree *tree,t_env **environ, t_env_var **env_vars)
{
    int fd[2];
    int pid[2];
    int status_1;
    int status_2;
    
    (1 && (pipe(fd)), (pid[0] = fork()), (error_handling(pid[0], "fork", NULL)));
    if (pid[0] == 0)
    {
        ft_signals(0);
        error_handling(close(fd[0]), "close", NULL);
        error_handling(dup2(fd[1], STDOUT_FILENO), "dup2", NULL);
        error_handling(close(fd[1]), "close", NULL);
        recursion(tree->data.pipe.rtree,environ ,env_vars);
        exit(ft_status(-1));
    }
    (1 && (pid[1] = fork()), (error_handling(pid[1], "fork", NULL)));
    if (pid[1] == 0) 
    {
        ft_signals(0);
        error_handling(close(fd[1]), "close", NULL);
        error_handling(dup2(fd[0], STDIN_FILENO), "dup2", NULL);
        error_handling(close(fd[0]), "close", NULL);
        recursion(tree->data.pipe.ltree,environ, env_vars);
        exit(ft_status(-1));
    }
    error_handling(close(fd[0]), "close", NULL);
    error_handling(close(fd[1]), "close", NULL);
    waitpid(pid[0], &status_1, 0);
    waitpid(pid[1], &status_2, 0);
    if (WIFSIGNALED(status_2))
    {
        int sig = WTERMSIG(status_2);
        if (sig == SIGINT)
            ft_status(130);
        else if (sig == SIGQUIT)
        {
            ft_status(131);
            printf("Quit (core dumped)\n");
        }
    }
    else if (WIFEXITED(status_2))
        ft_status(WEXITSTATUS(status_2));
    else
        ft_status(1);
}    
    

static void command_execution(t_tree *tree,t_env **environ ,int flag, t_env_var **env_vars)
{
    int pid;
    int status_1;

    if(is_built_in(tree->data.argv) == 1)
    {
        if(flag == 1)
            flag = 0;
        else if (flag == 0)
            flag = 1;
        execute_the_builtin(tree, environ, env_vars, flag);
    }
    else
    {
        if(!invalid_commands_checking(tree->data.argv[0],environ, env_vars))
            return;
        pid = fork();
        error_handling(pid, "close",NULL);
        if(pid == 0)
        {
            ft_signals(0);
            external_commands_execution(tree->data.argv,environ, env_vars);
        }
        waitpid(pid,&status_1,0);
        if (WIFSIGNALED(status_1))
        {
            int sig = WTERMSIG(status_1);
            if (sig == SIGINT)
                ft_status(130);
            else if (sig == SIGQUIT)
            {
                ft_status(131);
                printf("Quit (core dumped)\n");
            }
        }
        else if (WIFEXITED(status_1))
            ft_status(WEXITSTATUS(status_1));
        else
            ft_status(1);

    }    
}
static void change_lst_arg_(char *last_arg ,t_env **environ)
{

    char *lst_arg;
    
    if(!ft_strcmp(last_arg,"env"))
        lst_arg = "/usr/bin/env";
    else
        lst_arg = custom_strdup(last_arg,1);
    ft_setenv("_", lst_arg,0);
}

void last_command_arg(t_tree *tree, t_env **environ)
{
    char **args;
    char *last_arg;
    int i;
    
    i = 0;
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
int recursive_check(t_tree *tree)
{
    int fd;

    while (tree)
    {
        if(tree->type >= 2 && tree->type <=5)
        {
            if (tree->type == 2 )
            {
                
                if (access(tree->data.red.file.name, R_OK) != 0)
                {
                    error_handling(-1, "open", tree->data.red.file.name);
                    return (1);
                }
            }
            else if (tree->type == 3)
            {
                fd = open(tree->data.red.file.name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0)
                {
                    error_handling(-1, "open", tree->data.red.file.name);
                    return (1);
                }
                close(fd);
            }
            else if (tree->type == 5)
            {
                fd = open(tree->data.red.file.name, O_WRONLY | O_CREAT | O_APPEND, 0644);
                if (fd < 0)
                {
                    error_handling(-1, "open", tree->data.red.file.name);
                    return (1);
                }
                close(fd);
            }
        
            tree = tree->data.red.ntree;
        }
        else
            break;
    }
    return (0);
}
      
 void recursion(t_tree *tree, t_env **environ, t_env_var **env_vars)
{
    static int flag;

    if (!tree)
        return;

    if (tree->type == 0 && tree->data.argv && tree->data.argv[0])
    {
        last_command_arg(tree, environ);
        command_execution(tree, environ, flag, env_vars);
    }
    else if (tree->type == 1)
    {
        flag = 1;
        pipe_line(tree, environ, env_vars);
    }
    if (tree->type >= 2 && tree->type <= 5)
    {
        if (recursive_check(tree))
            return;
        else if (tree->type == 2)
            infile_handling(tree, environ, env_vars);
        else if (tree->type == 3)
            outfile_handling(tree, environ, env_vars);
        else if (tree->type == 4)
            heredoc_handling(tree, environ, env_vars);
        else if (tree->type == 5)
            append_handling(tree, environ, env_vars);
    }
}
  
   

