/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:07:23 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/05/29 03:40:41 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int count_lengh_var_str_export(char *str)
{
    int i ;
    
    i = 0;
    if(!str)
        return(-1);
    while(str[i] &&(str[i] != '=' && str[i]!= '+'))
    {
        i++;
    }
    return (i);  
}
void fill_in_var(char **var, char *str)
{
    int i;
        
    i = 0;
    while(str[i] && str[i] != '=' && str[i] != '+')
    {
        (*var)[i] = str[i];
        i++;
    }
    (*var)[i] = '\0';
}

static char **splited_export_command(char *str)
{
    char **splited_char;
    int  lengh_var_str;

    
    lengh_var_str = count_lengh_var_str_export(str);
    if(!str)
        return(NULL);
    splited_char = (char **)malloc(4*sizeof(char *));
    if(!splited_char)
        return(NULL);
    splited_char[0] =(char *)malloc((size_t)(lengh_var_str + 1));
    if(splited_char[0])
        fill_in_var(&splited_char[0], str);
    return(splited_char);
    
}

char  **split_environ(char *str)
{
    char **splited_char;
    int  lengh_var_str;

    if(!str)
        return(NULL);
    lengh_var_str = count_lengh_var_str_export(str);
    splited_char = splited_export_command(str);
    if(str[lengh_var_str] == '=')
        splited_char[1] = ft_strdup("=");
    else if(str[lengh_var_str] == '+')
    {
        splited_char[1] = ft_strdup("+=");
        lengh_var_str = lengh_var_str + 1;
    }
    else
    {
        splited_char[1] = NULL;
        splited_char[2] = NULL;
        return(splited_char);
    }
    splited_char[2]= ft_strdup(str + lengh_var_str + 1);
    splited_char[3] = NULL ;
    if(!splited_char[0] || !splited_char[1] || !splited_char[2])
        return(NULL);
     return(splited_char);
}


t_environ  *ft_lstnew_environ(char *str)
{
	t_environ	*newnode;
    char       **splited_export;

	newnode = (t_environ *)malloc(sizeof(t_environ));
	if (!newnode)
		return (NULL);
    splited_export = split_environ(str);
    if(!splited_export)
        return(NULL);
    else
    {
	    newnode->var =splited_export[0];
        newnode->operator= splited_export[1];
        newnode->value= splited_export[2];
	    newnode->next = NULL;
        return(newnode);
    }
}
void	ft_lstadd_back_environ(t_environ **lst, t_environ *new)
{
	t_environ	*temp;

	if (new == NULL)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while ((temp)->next != NULL)
	{
		(temp) = (temp)->next;
	}
	(temp)->next = new;
}

