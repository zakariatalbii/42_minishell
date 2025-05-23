/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:31:38 by zatalbi           #+#    #+#             */
/*   Updated: 2025/05/23 22:41:03 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isspace(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static size_t	ft_ignore_spaces(char *str)
{
	size_t	v;

	v = 0;
	while ((str[v] >= 9 && str[v] <= 13) || str[v] == 32)
		v++;
	return (v);
}

static size_t	ft_qcount(char *str)
{
	size_t	v;

	v = 0;
	if (str[v] == '\'')
	{
		v++;
		while (str[v] && str[v] != '\'')
			v++;
	}
	else if (str[v] == '"')
	{
		v++;
		while (str[v] && str[v] != '"')
			v++;
	}
	return (v);
}

static size_t	ft_count(char *str)
{
	size_t	v;

	v = 0;
	while (str[v] && !ft_isspace(str[v]) && str[v] != '|'
		&& str[v] != '<' && str[v] != '>')
	{
		v += ft_qcount(&str[v]);
		if (!str[v++])
			return (0);
	}
	if (!v && str[v] == '<')
		v += (str[v + 1] == '<') + 1;
	else if (!v && str[v] == '>')
		v += (str[v + 1] == '>') + 1;
	else if (!v && str[v] == '|')
		v++;
	return (v);
}

t_list	*ft_split_line(char *line)
{
	t_list	*head;
	t_list	*node;
	size_t	count;
	size_t	v;

	if (!line)
		return (NULL);
	head = NULL;
	v = ft_ignore_spaces(line);
	while (line[v])
	{
		count = ft_count(line + v);
		node = ft_lstnew(ft_new_token(ft_strndup(line + v, count)));
		ft_lstadd_back(&head, node);
		if (!node || !node->content)
		{
			if (!count)
				ft_putendl_fd("minishell: unclosed quotes", 2);
			else
				perror("malloc");
			return (ft_lstclear(&head, ft_free_token), NULL);
		}
		v += ft_ignore_spaces(line + v + count) + count;
	}
	return (head);
}
