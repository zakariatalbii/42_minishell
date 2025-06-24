/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 07:06:48 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/24 17:23:00 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void free_global_garbage(t_global_trash **global_trash)
{
    t_global_trash	*tmp;

	while (*global_trash)
	{
		tmp = *global_trash;
		*global_trash = (*global_trash)->next;
		free(tmp->point);
		free(tmp);
	}
}
void free_local_garbage(t_local_trash **local_trash)
{
    t_local_trash	*tmp;

	while (*local_trash)
	{
		tmp = *local_trash;
		*local_trash = (*local_trash)->next;
		free(tmp->point);
		free(tmp);
	}
}
static void *global_collection(t_global_trash **global_trash, size_t size)
{
   
    t_global_trash			        *new;
    void			            *ptr;
    
    new = malloc(sizeof(t_global_trash));
    if (!new)
    {
		free_global_garbage(global_trash);
        return(NULL);
    }
    ptr = malloc(size);
	if (!ptr)
    {
        free(new); 
		free_global_garbage(global_trash);
        return(NULL);
    }
	new->point = ptr;
	new->next = *global_trash;
	*global_trash = new;
	return (ptr);  
}

static void *local_collection(t_local_trash **local_trash ,size_t size)
{
   
    t_local_trash			        *new;
    void			            *ptr;
    
    new = malloc(sizeof(t_local_trash));
    if (!new)
    {
		free_local_garbage(local_trash);
        return(NULL);
    }
    ptr = malloc(size);
	if (!ptr)
    {
        free(new); 
		free_local_garbage(local_trash);
        return(NULL);
    }
	new->point = ptr;
	new->next = *local_trash;
	*local_trash = new;
	return (ptr);  
}
void *gc_malloc(size_t size, int pid)
{
    static t_global_trash	*global_trash;
    static t_local_trash	*local_trash;
    
	void			*ptr;
        
    if(pid == 0)
    {
        if(size)
            ptr = local_collection(&local_trash,size);
        else
            free_local_garbage(&local_trash);
    }
            
    else
    {
        if(size)
            ptr = global_collection(&global_trash, size);
        else
            free_global_garbage(&global_trash); 
    }
	return (ptr);
}
