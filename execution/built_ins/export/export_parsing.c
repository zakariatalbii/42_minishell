/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:06:16 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/29 23:30:14 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int ft_is_a_numb(char c)
{
    if(c >= '0' && c <= '9')
        return(1);
    else
        return(0);
}

int is_while_space(char c)
{
    if((c > 8 && c <= 13) || c == ' ')
        return(1);
    return(0);
}

int valid_position_export(char *str)
{
    int i;

    i = 0;
    
    if(!str)
        return(-1);
    while(str[i])
    {
        if(((str[i] == '=') && ((i == 0) || is_while_space(str[i-1])) )
            || ((str[i] =='+') && ((i ==0) || is_while_space(str[i-1]))))
        {
            ft_status(1);
            return(0);
        }
        i++; 
    }
    return(1);
}

int var_name_end(char *str)
{
    int i;

    i = 0;
    if(!str)
        return(-1);
    while(str[i])
    {
        if(str[i]=='+' && str[i+1] == '=' && i!=0)
            return(i);
        else if(str[i] == '=' && i!= 0)
            return(i);
        i++;
    }
    return(i);
}

int valid_var_name(char *str, int count)
{
    int i;
    if(!str)
    {
        return(-1);
    }
    if(ft_is_a_numb(str[0]))
        return(0);
    i = 0;
    while(i < count)
    {
        if((!ft_is_a_numb(str[i]) && !ft_isalpha(str[i])) && str[i] != '_')
        {
            return(0);
        }
        i++;
    }
    return(1);
}
