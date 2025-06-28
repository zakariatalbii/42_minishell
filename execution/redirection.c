/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:45:55 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/28 15:03:54 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void infile_handling(t_tree *tree, t_env_var **env_vars)
{
    int original_in;
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
        perror("bash: No such file or directory\n");
}

void fd_input_directing(int fd_to,int fd_from)
{
    char buffer[1024];
    ssize_t bytes_read;

    bytes_read = read(fd_from, buffer, sizeof(buffer));
    while(bytes_read>0)
    {
        write(fd_to, buffer, bytes_read);
        bytes_read = read(fd_from, buffer,bytes_read);
    }
}
void outfile_handling(t_tree *tree, t_env_var **env_vars)
{
    int fd_;
    int original_out;
    int fd[2];

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
        fd_input_directing(STDERR_FILENO, fd[0]);
    else 
        fd_input_directing(fd_,fd[0]);
    close(original_out);
    close(fd[0]);
    close(fd_);
}

void heredoc_handling(t_tree *tree, t_env_var **env_vars)
{
    int original_in;

    original_in=dup(STDIN_FILENO);
    error_handling(original_in,"dup");
    error_handling(dup2(tree->data.red.file.fd, STDIN_FILENO),"dup2");
    recursion(tree->data.red.ntree, env_vars);
    error_handling(close(tree->data.red.file.fd),"close");
    error_handling(dup2(original_in, STDIN_FILENO),"dup2");
    error_handling(close(original_in),"close");
    // int original_in;

}
void append_handling(t_tree *tree, t_env_var **env_vars) 
{
    int fd_;
    int original_out;
    int fd[2];

    pipe(fd);
    original_out = dup(STDOUT_FILENO);
    error_handling(original_out, "dup");
    if(access(tree->data.red.file.name, F_OK)==0)
    {
            fd_ = open(tree->data.red.file.name, O_WRONLY|O_APPEND);
            error_handling(fd_,"open");
    }
    else
    {
            fd_ = open(tree->data.red.file.name, O_CREAT|O_WRONLY|O_APPEND);
            error_handling(fd_,"open");
    }
    error_handling(dup2(fd[1], STDOUT_FILENO), "dup2");
    close(fd[1]);
    recursion(tree->data.red.ntree, env_vars);
    error_handling(dup2(original_out, STDOUT_FILENO), "dup2");
    if (*((*env_vars)->status) == 127) 
        fd_input_directing(STDERR_FILENO,fd[0]);
    else
        fd_input_directing(fd_,fd[0]);
    close(original_out);
    close(fd[0]);
    close(fd_);
    
}
