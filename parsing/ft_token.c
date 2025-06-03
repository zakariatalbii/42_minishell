/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 14:05:31 by zatalbi           #+#    #+#             */
/*   Updated: 2025/06/03 13:07:18 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_token_type(char *token)
{
	if (!ft_strncmp(token, "|", 2))
		return (PIPE);
	else if (!ft_strncmp(token, "<", 2))
		return (INRED);
	else if (!ft_strncmp(token, ">", 2))
		return (OUTRED);
	else if (!ft_strncmp(token, "<<", 3))
		return (HEREDOC);
	else if (!ft_strncmp(token, ">>", 3))
		return (OUTRED_A);
	return (STR);
}

t_token	*ft_new_token(char *token)
{
	t_token	*node;

	if (token)
		node = (t_token *)malloc(sizeof(t_token));
	if (!token || !node)
		return (NULL);
	node->token = token;
	node->type = ft_token_type(token);
	return (node);
}

void	ft_free_token(void *ptr)
{
	if (!ptr)
		return ;
	free(((t_token *)ptr)->token);
	free(ptr);
}
