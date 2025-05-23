/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:20:54 by zatalbi           #+#    #+#             */
/*   Updated: 2025/05/23 22:39:11 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_heredoc_warning(char *delimiter, int n)
{
	ft_putstr_fd("minishell: warning: here-document at line ", 2);
	ft_putnbr_fd(n, 2);
	ft_putstr_fd(" delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putendl_fd("')", 2);
	return (1);
}

static int	ft_heredoc_fds(int *fds)
{
	unlink("/tmp/minishell-heredoc");
	fds[0] = open("/tmp/minishell-heredoc", O_CREAT | O_EXCL | O_RDONLY, 0600);
	if (fds[0] != -1)
	{
		fds[1] = open("/tmp/minishell-heredoc", O_WRONLY);
		if (fds[1] == -1)
			close(fds[0]);
		unlink("/tmp/minishell-heredoc");
	}
	if (fds[0] == -1 || fds[1] == -1)
		return (ft_putendl_fd("minishell: cannot open here-document", 2), -1);
	return (0);
}

static int	ft_expand_heredoc(char **s, int status, int flag)
{
	char	*str;
	size_t	len;

	len = ft_tokenlen(*s, status, flag);
	if (flag == 1 && len == ft_strlen(*s))
		return (0);
	str = (char *)malloc(len + 1);
	if (!str)
		return (free(*s), *s = NULL, perror("malloc"), -1);
	ft_expand_token(str, *s, status, flag);
	free(*s);
	*s = str;
	return (1);
}

void	ft_store_fd(int fd)
{
	static int	fds[MAX_HEREDOC + 1] = {-1};
	int			v;

	v = -1;
	if (fd == -1)
	{
		while (++v < MAX_HEREDOC)
		{
			if (fds[v] == -1)
				return ;
			close(fds[v]);
			fds[v] = -1;
		}
	}
	while (++v < MAX_HEREDOC)
	{
		if (fds[v] == -1)
		{
			fds[v] = fd;
			fds[v + 1] = -1;
			break ;
		}
	}
}

int	ft_heredoc(char **delimiter, int status, int flag)
{
	static size_t	count;
	size_t			n;
	char			*line;
	int				fds[2];

	if (ft_heredoc_fds(fds) == -1)
		return (-1);
	if ((flag && ++count) || !flag)
		n = count;
	flag = ft_expand_heredoc(delimiter, status, 1);
	if (flag == -1)
		return (-1);
	while (count++)
	{
		line = readline("> ");
		if ((!line && ft_heredoc_warning(*delimiter, n) && count--)
			|| !ft_strncmp(*delimiter, line, strlen(line) + 1))
			break ;
		if (!flag && ft_expand_heredoc(&line, status, 2) == -1)
			return (close(fds[0]), close(fds[1]), -1);
		ft_putendl_fd(line, fds[1]);
		free(line);
	}
	return (free(*delimiter), free(line), close(fds[1]), ft_store_fd(fds[0]),
		fds[0]);
}
