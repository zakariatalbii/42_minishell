/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 07:06:48 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/23 09:38:59 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"


void *global_collection(size_t size)
{
    static t_global_trash	*global_trash;
    t_global_trash			        *new;
    void			            *ptr;
    
    new = malloc(sizeof(t_global_trash));
    if (!new)
    {
		// free_global_garbage(&global_trash, 1);
        return(NULL);
    }
    ptr = malloc(size);
	if (!ptr)
    {
		// free_garbage(&global_trash, 1);
        return(NULL);
    }
	new->point = ptr;
	new->next = global_trash;
	global_trash = new;
	return (ptr);  
}

void *local_collection(size_t size)
{
    static t_local_trash	*local_trash;
    t_local_trash			        *new;
    void			            *ptr;
    
    new = malloc(sizeof(t_local_trash));
    if (!new)
    {
		// free_local_garbage(&local_trash, 1);
        return(NULL);
    }
    ptr = malloc(size);
	if (!ptr)
    {
		// free_local_garbage(&local_trash, 1);
        return(NULL);
    }
	new->point = ptr;
	new->next = local_trash;
	local_trash = new;
	return (ptr);  
}
void *gc_malloc(size_t size, int pid)
{
    
	void			*ptr;

    if(pid == 0)
    {
        ptr = local_collection(size);
    }
    else
       ptr =  global_collection(size);  
	return (ptr);
}

