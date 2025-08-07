/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 02:36:24 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/08/07 17:50:14 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	infile_handling(t_tree *tree, t_env **environ, t_env_var **env_vars)
{
	int	original_in;
	int	fd;

	if (access((tree->data.red.file.name), F_OK) == 0)
	{
		original_in = dup(STDIN_FILENO);
		error_handling(original_in, "dup", NULL);
		fd = open(tree->data.red.file.name, O_RDONLY);
		error_handling(dup2(fd, STDIN_FILENO), "dup2", NULL);
		error_handling(close(fd), "close", NULL);
		recursion(tree->data.red.ntree, environ, env_vars);
		error_handling(dup2(original_in, STDIN_FILENO), "dup2", NULL);
		error_handling(close(original_in), "close", NULL);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(tree->data.red.file.name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		ft_status(1);
	}
}

void	outfile_handling(t_tree *tree, t_env **environ, t_env_var **env_vars)
{
	int	fd_;
	int	original_out;

	if (access(tree->data.red.file.name, F_OK) == 0)
		fd_ = open(tree->data.red.file.name, O_WRONLY | O_TRUNC);
	else
		fd_ = open(tree->data.red.file.name, O_CREAT | O_RDWR, 0644);
	original_out = dup(STDOUT_FILENO);
	error_handling(original_out, "dup", NULL);
	error_handling(dup2(fd_, STDOUT_FILENO), "dup2", NULL);
	close(fd_);
	recursion(tree->data.red.ntree, environ, env_vars);
	error_handling(dup2(original_out, STDOUT_FILENO), "dup2", NULL);
	close(original_out);
}

void	heredoc_handling(t_tree *tree, t_env **environ, t_env_var **env_vars)
{
	int	original_in;

	ft_signals(2);
	original_in = dup(STDIN_FILENO);
	error_handling(original_in, "dup", NULL);
	error_handling(dup2(tree->data.red.file.fd, STDIN_FILENO), "dup2", NULL);
	recursion(tree->data.red.ntree, environ, env_vars);
	error_handling(dup2(original_in, STDIN_FILENO), "dup2", NULL);
	error_handling(close(original_in), "close", NULL);
}

void	append_handling(t_tree *tree, t_env **environ, t_env_var **env_vars)
{
	int	fd_;
	int	original_out;

	original_out = dup(STDOUT_FILENO);
	error_handling(original_out, "dup", NULL);
	if (access(tree->data.red.file.name, F_OK) == 0)
		fd_ = open(tree->data.red.file.name, O_WRONLY | O_APPEND);
	else
		fd_ = open(tree->data.red.file.name,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
	error_handling(dup2(fd_, STDOUT_FILENO), "dup2", NULL);
	close(fd_);
	recursion(tree->data.red.ntree, environ, env_vars);
	error_handling(dup2(original_out, STDOUT_FILENO), "dup2", NULL);
	close(original_out);
}
