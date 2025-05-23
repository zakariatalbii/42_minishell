/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:31:38 by zatalbi           #+#    #+#             */
/*   Updated: 2025/05/23 22:39:45 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_max_heredoc(t_list **list)
{
	ft_putendl_fd("minishell: maximum here-document count exceeded", 2);
	ft_lstclear(list, ft_free_token);
	exit(2);
}

static int	ft_syntax_error(t_list **list, char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putendl_fd("'", 2);
	ft_lstclear(list, ft_free_token);
	return (1);
}

static int	ft_ambiguous(char *s1, char *s2)
{
	int	v;

	v = -1;
	while (s2[++v])
	{
		if (s2[v] == '\'' || s2[v] == '"')
			return (0);
	}
	if (!*s1)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(s2, 2),
			ft_putendl_fd(": ambiguous redirect", 2), 1);
	return (0);
}

void	ft_check_tokens(t_list **list)
{
	t_list	*head;
	int		hdc;

	head = *list;
	if (head && ((t_token *)head->content)->type == PIPE
		&& ft_syntax_error(list, ((t_token *)head->content)->token))
		return ;
	hdc = 0;
	while (head)
	{
		if ((((t_token *)head->content)->type >= PIPE && (!head->next
					|| ((t_token *)head->next->content)->type == PIPE))
			|| (((t_token *)head->content)->type >= INRED
				&& ((t_token *)head->next->content)->type > PIPE))
		{
			if (!head->next)
				ft_syntax_error(list, "newline");
			else
				ft_syntax_error(list, ((t_token *)head->next->content)->token);
			return ;
		}
		if (((t_token *)head->content)->type == HEREDOC && ++hdc > MAX_HEREDOC)
			ft_max_heredoc(list);
		head = head->next;
	}
}

int	ft_expand_tokens(t_list **list, int status)
{
	t_list	*head;
	char	*str;
	int		ptype;

	head = *list;
	ptype = 0;
	while (head)
	{
		if (((t_token *)head->content)->type == STR && ptype != HEREDOC)
		{
			str = (char *)malloc(ft_tokenlen(((t_token *)head->content)->token,
						status, 0) + 1);
			if (!str)
				return (ft_lstclear(list, ft_free_token), perror("malloc"), 1);
			ft_expand_token(str, ((t_token *)head->content)->token, status, 0);
			if (ft_ambiguous(str, ((t_token *)head->content)->token))
				return (ft_lstclear(list, ft_free_token), free(str), 1);
			free(((t_token *)head->content)->token);
			((t_token *)head->content)->token = str;
		}
		ptype = ((t_token *)head->content)->type;
		head = head->next;
	}
	return (0);
}
