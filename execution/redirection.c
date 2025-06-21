/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 16:45:55 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/21 01:23:01 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void infile_handling(t_tree *tree, char **PWD, char **OLDPWD, int *status)
{
    int original_in;
    int original_out;
    int fd;
    
    if(access((tree->data.red.file.name), F_OK) == 0)
    {
        original_in=dup(STDIN_FILENO);
        error_handling(original_in, "dup");
        fd = open(tree->data.red.file.name, O_RDONLY);
        error_handling(fd,"open");
        error_handling(dup2(fd,STDIN_FILENO),"dup2");
        recursion(tree->data.red.ntree, PWD, OLDPWD, status);
        error_handling(close(fd),"close");
        error_handling(dup2(original_in,STDIN_FILENO),"dup2");
        error_handling(close(original_in),"close");
    }
    else
        printf("error file not found\n");
}
void outfile_handling(t_tree *tree, char **PWD, char **OLDPWD, int *status)
{
    int fd;
    int original_in;
    int original_out;

    if(access((tree->data.red.file.name), F_OK) == 0)
    {
        fd = open(tree->data.red.file.name,O_WRONLY);
        error_handling(fd,"open");
    }
    else
    {
        fd = open(tree->data.red.file.name, O_CREAT | O_RDWR);
        error_handling(fd,"open");
    }
        original_out=dup(STDOUT_FILENO);
        error_handling(original_out, "dup");
        error_handling(dup2(fd,STDOUT_FILENO),"dup2");
        error_handling(close(fd),"close");
        recursion(tree->data.red.ntree, PWD, OLDPWD, status);
        error_handling(dup2(original_out,STDOUT_FILENO),"dup2");
        error_handling(close(original_out),"close");
}

void heredoc_handling(t_tree *tree, char **PWD, char **OLDPWD, int *status)
{
    int original_in;
    int original_out;

    original_in=dup(STDIN_FILENO);
    error_handling(original_in,"dup");
    error_handling(dup2(tree->data.red.file.fd, STDIN_FILENO),"dup2");
    recursion(tree->data.red.ntree, PWD, OLDPWD, status);
    error_handling(close(tree->data.red.file.fd),"close");
    error_handling(dup2(original_in, STDIN_FILENO),"dup2");
    error_handling(close(original_in),"close");
}

void append_handling(t_tree *tree, char **PWD, char **OLDPWD, int *status)
{
    int fd;
    int original_in;
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
    recursion(tree->data.red.ntree, PWD, OLDPWD, status);
    error_handling(close(fd),"close");
    error_handling(dup2(original_out,STDOUT_FILENO),"dup2");
    error_handling(close(original_out),"close");
}
