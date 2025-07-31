/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 22:07:23 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/30 05:40:38 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_lengh_var_str_export(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] && (str[i] != '=' && str[i] != '+'))
	{
		i++;
	}
	return (i);
}

void	fill_in_var(char **var, char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		(*var)[i] = str[i];
		i++;
	}
	(*var)[i] = '\0';
}

t_environ	*ft_lstnew_environ(char *str)
{
	t_environ	*newnode;
	char		**splited_export;

	newnode = (t_environ *)gc_malloc(sizeof(t_environ), 1);
	if (!newnode)
		return (NULL);
	splited_export = split_environ(str);
	if (!splited_export)
		return (NULL);
	else
	{
		newnode->var = splited_export[0];
		newnode->operator = splited_export[1];
		newnode->value = splited_export[2];
		newnode->next = NULL;
		return (newnode);
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
