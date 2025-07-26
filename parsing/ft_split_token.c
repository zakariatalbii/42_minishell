/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 21:31:38 by zatalbi           #+#    #+#             */
/*   Updated: 2025/07/26 20:24:45 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_withequal(char *str)
{
	while (*str && *str != '\'' && *str != '"')
	{
		if (*str == '=')
			return (1);
		str++;
	}
	return (0);
}

static int	ft_nultoken(t_list **lst, char *token, int ptype)
{
	t_qchar	*qc;

	qc = ft_qchar(NULL, 0);
	if (qc && qc->fc && qc->lc)
		return (0);
	if (ptype < INRED)
		ft_lstclear(lst, ft_free_token);
	else if (ptype >= INRED)
		return (ft_putstr_fd("minishell: ", 2),
			ft_putstr_fd(token, 2),
			ft_putendl_fd(": ambiguous redirect", 2),
			ft_lstclear(lst, ft_free_token), ft_status(1));
	return (0);
}

static int	ft_addlst(t_list **list, t_list **head, t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		lst = (*head)->next;
	else
		ft_lstadd_back(&lst, (*head)->next);
	tmp = *list;
	while (tmp != *head && tmp->next != *head)
		tmp = tmp->next;
	if (tmp == *head)
		*list = lst;
	else if (tmp->next == *head)
		tmp->next = lst;
	tmp = *head;
	*head = (*head)->next;
	return (ft_lstdelone(tmp, ft_free_token), 1);
}

int	ft_split_token(t_list **list, t_list **head, char *str, int *ptype)
{
	t_list	*lst;
	t_list	*tmp;
	char	*cmd;

	cmd = ft_tokencmd(*list, *head);
	if (cmd && !ft_strcmp(cmd, "export")
		&& ft_withequal(((t_token *)(*head)->content)->token))
		return (*ptype = STR, free(((t_token *)(*head)->content)->token),
		((t_token *)(*head)->content)->token = str, *head = (*head)->next, 1);
	lst = ft_tokenlst(str);
	free(str);
	if (!lst || (!*((t_token *)lst->content)->token
			&& ft_nultoken(&lst, ((t_token *)(*head)->content)->token, *ptype)))
		return (*head = NULL, ft_lstclear(list, ft_free_token), 1);
	tmp = lst;
	while (tmp)
	{
		((t_token *)tmp->content)->type = STR;
		tmp = tmp->next;
	}
	return (*ptype = STR, ft_addlst(list, head, lst));
}
