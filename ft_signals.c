/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zatalbi <zatalbi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 14:51:16 by zatalbi           #+#    #+#             */
/*   Updated: 2025/07/22 17:00:07 by zatalbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_prompt_i(int flag)
{
	static int	pflag;

	if (flag > -1)
		pflag = flag;
	return (pflag);
}

static void	ft_handler_i(int sig)
{
	(void)sig;
	if (!ft_prompt_i(-1))
	{
		ft_status(1);
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		ft_count_lines(1);
	}
	else
	{
		ft_status(130);
		ft_putchar_fd('\n', 1);
	}
}

int	ft_heredoc_i(int f, int *fds)
{
	static int	flag;

	if (f == 1)
		flag = 1;
	else if (f == 0 && flag)
		return (dup2(fds[2], 0), close(fds[0]), close(fds[1]), close(fds[2]),
			flag = 0, ft_signals(1), 1);
	return (flag);
}

static void	ft_handler_h(int sig)
{
	(void)sig;
	ft_status(1);
	ft_heredoc_i(1, NULL);
	ft_putchar_fd('\n', 1);
	close(0);
}

void	ft_signals(int flag)
{
	t_sigaction	sa_i;
	t_sigaction	sa_q;

	ft_memset(&sa_i, 0, sizeof(t_sigaction));
	ft_memset(&sa_q, 0, sizeof(t_sigaction));
	if (flag == 0)
		sa_i.sa_handler = SIG_DFL;
	else if (flag == 1)
		sa_i.sa_handler = ft_handler_i;
	else if (flag == 2)
		sa_i.sa_handler = ft_handler_h;
	if (flag == 0)
		sa_q.sa_handler = SIG_DFL;
	else if (flag == 1 || flag == 2)
		sa_q.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_i, NULL);
	sigaction(SIGQUIT, &sa_q, NULL);
}
