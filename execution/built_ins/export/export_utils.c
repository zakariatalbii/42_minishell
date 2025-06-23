/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 03:00:22 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/23 09:56:52 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void export_printing_conditions(t_environ *current, t_env_var **env_vars)
{
    if(!strcmp(current->var, "PATH"))
    {
        if(*((*env_vars)->export_PATH) == 1)
            printing_export(current);
    }
    else if(!strcmp(current->var, "_"))
    {
        if(*((*env_vars)->export_) == 1)
            printing_export(current);
    }       
    else
        printing_export(current);
}
void export_flags_apdate(t_environ **environ ,t_environ *new, t_env_var **env_vars)
{
    if(!strcmp(new->var, "PATH") )
        *((*env_vars)->export_PATH) = 1;
    if(!strcmp(new->var, "_"))
        *((*env_vars)->export_) = 1;
    if(!strcmp(new->var, "OLDPWD"))
        *((*env_vars)->export_OLDPWD) = 1;
    if(is_the_var_in_environ(new->var, *environ))
        handling_new_changes(&new, environ, env_vars);
    else
        ft_lstadd_back_environ(environ, new);
}
char **splited_export_command(char *str)
{
    char **splited_char;
    int  lengh_var_str;

    
    lengh_var_str = count_lengh_var_str_export(str);
    if(!str)
        return(NULL);
    splited_char = (char **)gc_malloc(4*sizeof(char *),1);
    if(!splited_char)
        return(NULL);
    splited_char[0] =(char *)gc_malloc((size_t)(lengh_var_str + 1),1);
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
        splited_char[1] = custom_strdup("=",1);
    else if(str[lengh_var_str] == '+')
    {
        splited_char[1] = custom_strdup("+=",1);
        lengh_var_str = lengh_var_str + 1;
    }
    else
    {
        splited_char[1] = NULL;
        splited_char[2] = NULL;
        return(splited_char);
    }
    splited_char[2]= custom_strdup(str + lengh_var_str + 1,1);
    splited_char[3] = NULL ;
    if(!splited_char[0] || !splited_char[1] || !splited_char[2])
        return(NULL);
     return(splited_char);
}
