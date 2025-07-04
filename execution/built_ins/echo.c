/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:06:44 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/24 20:08:28 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

// static int identify_the_arg(char **str, int *i)
// {
//     int j ;

//     j = 0;

//    while(str[*i])
//     {
//         if (str[*i][0] == '-')
//         {

//             j = 1;
//             while(str[*i][j])
//             {
//                 if(str[*i][j] != 'n')
//                 {
//                     return(0);
//                 }
//                 j++;
//             }
//         }
//         else 
//             return(0);
//         (*i)++;
//     }
//     return(1); 
// }

// void echo_execution(char **command, t_env_var **env_vars)
// {
//     int i;
//     int new_line;

//     new_line = 0;
//     i = 1;
//     if(!identify_the_arg((command), &i))
//     {
//         if(i != 1)//cause if i != 1 of course we did pass one valid argument   
//             new_line = 1; 
//         i = 1;
//     }
//     // else 
//     // {
//     //     if(!command[i])
//     //         new_line = 1;
//     // }
//     while((command)[i])
//     {
//         printf("%s",(command)[i]);
//         if((command)[i+1] != NULL)
//             printf(" ");
//         i++;
//     }
//     if(new_line == 0)
//         printf("\n");
//     *((*env_vars)->status) = 0;
// }


static int identify_the_arg(char **str, int *i)
{
    int j ;
    int index;

    j = 0;
    index = 0;


   while(str[*i])
    {
        if (str[*i][0] == '-')
        {
            if(!ft_strcmp(str[*i], "-"))
            {
                return(0);
            }
            j = 1;
            while(str[*i][j])
            {
                if(str[*i][j] != 'n')
                    return(0);
                j++;
            }
        }
        else 
            return(0);
        (*i)++;
    }
    return(1);
    
}

void echo_execution(char **command, t_env_var **env_vars)
{
    int i;
    int new_line;

    new_line = 0;
    i = 1;
    if(!identify_the_arg((command), &i))
    {
        if(i != 1 )//cause if i != 1 of course we did pass one valid argument   
            new_line = 1; 
    }
    else 
    {
        new_line = 1;
    }
    while((command)[i])
    {
        printf("%s",(command)[i]);
        if((command)[i+1] != NULL)
            printf(" ");
        i++;
    }
    if(new_line == 0)
        printf("\n");
    *((*env_vars)->status) = 0;
}
