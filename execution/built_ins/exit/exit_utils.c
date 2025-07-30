/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 01:55:40 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/30 01:58:10 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

long long ft_lg__atoi(const char *str)
{
    long long num ;
    int sign ;
    int digit;

    (1 && (num = 0),(sign = 1));
    while (*str == ' ' || *str == '\t' || *str == '\n'
        || *str == '\v' || *str == '\r' || *str == '\f')
        str++;
    if (*str == '+' || *str == '-')
        if (*str++ == '-')
            sign = -1;
    while (*str >= '0' && *str <= '9')
    {
        digit = *str - '0';
        if (sign == 1 && num > (LLONG_MAX - digit) / 10)
            return (-111);
        if (sign == -1 && 
                num > ((unsigned long long)LLONG_MAX + 1ULL - digit) / 10)
            return (-111);
        num = num * 10 + digit;
        str++;
    }
    if (sign == -1 && num == (unsigned long long)LLONG_MAX + 1ULL)
        return LLONG_MIN;
    return (num * sign);
}


void exiting(t_tree *tree, t_env_var **env_vars, int exit_printing, int pid)
{   
    int status;
    
    status = ft_status(-1);
    if(exit_printing && pid == 1)
    ft_free_tree(tree);
    gc_malloc(0, 0);
    gc_malloc(0, 1);
    exit(status);
}

void real_exit_status(t_tree *tree, t_env_var  **env_vars, int pid)
{
    unsigned char  status;
    char *argument = tree->data.argv[1];
    
    status  =(unsigned char)(ft_atoi(argument));
    ft_status(status);
    exiting(tree, env_vars, 1, pid);
}