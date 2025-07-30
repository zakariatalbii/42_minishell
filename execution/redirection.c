/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:45:55 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/29 20:27:55 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int failed_redirection(int flag_)
{
    static int flag;
    if(flag_ == 0)
        return(flag);
    else
    {
        flag = flag_;
        return(flag);
    }
}
void infile_handling(t_tree *tree,t_env **environ ,t_env_var **env_vars)
{
    int original_in;
    int fd;
    
    if(access((tree->data.red.file.name), F_OK) == 0)
    {
        original_in=dup(STDIN_FILENO);
        error_handling(original_in, "dup", NULL);
        fd = open(tree->data.red.file.name, O_RDONLY);
        error_handling(dup2(fd,STDIN_FILENO),"dup2", NULL);
        recursion(tree->data.red.ntree, environ,env_vars);
        error_handling(close(fd),"close", NULL);
        error_handling(dup2(original_in,STDIN_FILENO),"dup2", NULL);
        error_handling(close(original_in),"close", NULL);
    }
    else
    {
        ft_putstr_fd("minishell: ",2);
        ft_putstr_fd(tree->data.red.file.name,2);
        ft_putstr_fd(": No such file or directory\n", 2);
        ft_status(1);
    }
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
void outfile_handling(t_tree *tree,t_env **environ,t_env_var **env_vars)
{
    int fd_;
    int original_out;
    int fd[2];

    pipe(fd);
    if (access(tree->data.red.file.name, F_OK) == 0)
        fd_ = open(tree->data.red.file.name, O_WRONLY | O_TRUNC);
    else
        fd_ = open(tree->data.red.file.name, O_CREAT | O_RDWR, 0644);
    original_out = dup(STDOUT_FILENO);
    error_handling(original_out, "dup", NULL);
    error_handling(dup2(fd[1], STDOUT_FILENO), "dup2", NULL);
    close(fd[1]);
    recursion(tree->data.red.ntree, environ,env_vars);
    error_handling(dup2(original_out, STDOUT_FILENO), "dup2", NULL);
    if (ft_status(-1) != 127)
        fd_input_directing(fd_,fd[0]);
    (1 && (close(original_out)),(close(fd[0])), (close(fd_)));
}

void heredoc_handling(t_tree *tree,t_env **environ,t_env_var **env_vars)
{
    int original_in;

    ft_signals(2);
    original_in=dup(STDIN_FILENO);
    error_handling(original_in,"dup",NULL);
    error_handling(dup2(tree->data.red.file.fd, STDIN_FILENO),"dup2", NULL);
    recursion(tree->data.red.ntree,environ ,env_vars);
    error_handling(close(tree->data.red.file.fd),"close", NULL);
    error_handling(dup2(original_in, STDIN_FILENO),"dup2", NULL);
    error_handling(close(original_in),"close", NULL);
}
void append_handling(t_tree *tree,t_env **environ,t_env_var **env_vars) 
{
    int fd_;
    int original_out;
    int fd[2];

    pipe(fd);
    original_out = dup(STDOUT_FILENO);
    error_handling(original_out, "dup", NULL);
    if(access(tree->data.red.file.name, F_OK)==0)
        fd_ = open(tree->data.red.file.name, O_WRONLY|O_APPEND);
    else
        fd_ = open(tree->data.red.file.name, O_CREAT|O_WRONLY|O_APPEND, 0644);
    error_handling(dup2(fd[1], STDOUT_FILENO), "dup2", NULL);
    close(fd[1]);
    recursion(tree->data.red.ntree,environ,env_vars);
    error_handling(dup2(original_out, STDOUT_FILENO), "dup2", NULL);
    if (ft_status(-1) != 127) 
        fd_input_directing(fd_,fd[0]);
    close(original_out);
    close(fd[0]);
    close(fd_); 
}
