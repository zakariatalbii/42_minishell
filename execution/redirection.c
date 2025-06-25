/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:45:55 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/24 21:29:45 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void infile_handling(t_tree *tree, t_env_var **env_vars)
{
    int original_in;
    // int original_out;
    int fd;
    
    if(access((tree->data.red.file.name), F_OK) == 0)
    {
        original_in=dup(STDIN_FILENO);
        error_handling(original_in, "dup");
        fd = open(tree->data.red.file.name, O_RDONLY);
        error_handling(fd,"open");
        error_handling(dup2(fd,STDIN_FILENO),"dup2");
        recursion(tree->data.red.ntree, env_vars);
        error_handling(close(fd),"close");
        error_handling(dup2(original_in,STDIN_FILENO),"dup2");
        error_handling(close(original_in),"close");
    }
    else
        printf("error file not found\n");
}

void outfile_handling(t_tree *tree, t_env_var **env_vars)
{
    int fd_;
    int original_out;
    char buffer[1024];
    ssize_t bytes_read;
    int fd[2];

    // printf("%s\n",(tree->data.red.file.name));
    pipe(fd);
    if (access(tree->data.red.file.name, F_OK) == 0)
        fd_ = open(tree->data.red.file.name, O_WRONLY);
    else
        fd_ = open(tree->data.red.file.name, O_CREAT | O_RDWR, 0644);
    error_handling(fd_, "open");
    original_out = dup(STDOUT_FILENO);
    error_handling(original_out, "dup");
    error_handling(dup2(fd[1], STDOUT_FILENO), "dup2");
    close(fd[1]);
    recursion(tree->data.red.ntree, env_vars);
    error_handling(dup2(original_out, STDOUT_FILENO), "dup2");
    if (*((*env_vars)->status) == 127)
    {
        while ((bytes_read = read(fd[0], buffer, sizeof(buffer))) > 0) 
        {
            write(STDERR_FILENO, buffer, bytes_read);
        }
    }
    else 
    {   
        while ((bytes_read = read(fd[0], buffer, sizeof(buffer))) > 0) 
        {
            write(fd_, buffer, bytes_read);
        }
    }
    close(original_out);
    close(fd[0]);
    close(fd_);
}

void heredoc_handling(t_tree *tree, t_env_var **env_vars)
{
    int original_in;
    // int original_out;

    original_in=dup(STDIN_FILENO);
    error_handling(original_in,"dup");
    error_handling(dup2(tree->data.red.file.fd, STDIN_FILENO),"dup2");
    recursion(tree->data.red.ntree, env_vars);
    error_handling(close(tree->data.red.file.fd),"close");
    error_handling(dup2(original_in, STDIN_FILENO),"dup2");
    error_handling(close(original_in),"close");
}

void append_handling(t_tree *tree, t_env_var **env_vars)
{
    int fd;
    // int original_in;
    int original_out;
    
    original_out=dup(STDOUT_FILENO);
    error_handling(original_out,"dup");
    if(access(tree->data.red.file.name, F_OK)==0)
    {
        fd = open(tree->data.red.file.name, O_WRONLY|O_APPEND);
        error_handling(fd,"open");
    }
    else
    {
        fd = open(tree->data.red.file.name, O_CREAT|O_WRONLY|O_APPEND);
        error_handling(fd,"open");
    }
    error_handling(dup2(fd,STDOUT_FILENO),"dup2");
    recursion(tree->data.red.ntree, env_vars);
    error_handling(close(fd),"close");
    error_handling(dup2(original_out,STDOUT_FILENO),"dup2");
    error_handling(close(original_out),"close");
}
