/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:31:38 by zatalbi           #+#    #+#             */
/*   Updated: 2025/07/22 16:00:23 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	return (ft_lstclear(list, ft_free_token), ft_status(258));
}

static void	ft_check_tokens(t_list **list)
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

static int	ft_expand_tokens(t_list **list, int status)
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
			if (!ft_qchar(((t_token *)head->content)->token, 1) || !str)
				return (ft_lstclear(list, ft_free_token), free(str),
					ft_qchar(NULL, -1), perror("malloc"), ft_status(1));
			ft_expand_token(str, ((t_token *)head->content)->token, status, 0);
			if ((ft_empty_token(list, &head, str, ptype)
					|| ft_split_token(list, &head, str, &ptype))
				&& !ft_qchar(NULL, -1))
				continue ;
		}
		ptype = ((t_token *)head->content)->type;
		head = head->next;
	}
	return (*list == NULL);
}

t_list	*ft_lexer(char *line, int status)
{
	t_list	*head;

	head = ft_split_line(line);
	ft_check_tokens(&head);
	ft_expand_tokens(&head, status);
	return (head);
}
