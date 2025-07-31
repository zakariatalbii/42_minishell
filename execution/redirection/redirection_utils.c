/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 02:38:00 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/30 06:54:42 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	failed_redirection(int flag_)
{
	static int	flag;

	if (flag_ == 0)
		return (flag);
	else
	{
		flag = flag_;
		return (flag);
	}
}

void	fd_input_directing(int fd_to, int fd_from)
{
	char	buffer[1024];
	ssize_t	bytes_read;

	bytes_read = read(fd_from, buffer, sizeof(buffer));
	while (bytes_read > 0)
	{
		write(fd_to, buffer, bytes_read);
		bytes_read = read(fd_from, buffer, bytes_read);
	}
}
