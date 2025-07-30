/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_line_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 02:23:52 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/30 02:24:51 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int outfiles_checking(t_tree * tree)
{
    int fd;
    
    if (tree->type == 3)
    {
        fd = open(tree->data.red.file.name,
             O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0)
        {
            error_handling(-1, "open", tree->data.red.file.name);
            return (1);
        }
        close(fd);
    }
    else if (tree->type == 5)
    {
        fd = open(tree->data.red.file.name, 
            O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd < 0)
        {
            error_handling(-1, "open", tree->data.red.file.name);
            return (1);
        }
        close(fd);
    }
    return(0);
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
                fd = open(tree->data.red.file.name, O_RDONLY);
                if (fd<0)
                {
                    error_handling(-1, "open", tree->data.red.file.name);
                    return (1);
                }
                close(fd);
            }
            else
                return(outfiles_checking(tree));       
            tree = tree->data.red.ntree;
        }
        else
            break;
    }
    return (0);
}