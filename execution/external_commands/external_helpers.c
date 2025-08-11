/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:39:32 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/08/11 12:55:18 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_lengh_of_str(char *str, char c, int *i)
{
	int	lengh;

	lengh = 0;
	while (str[*i] && str[*i] != c)
	{
		(*i)++;
		lengh++;
	}
	return (lengh);
}

static char	**allocate_double_char(char *str, char c, char *command)
{
	int		i;
	int		j;
	char	**ptr;

	if (!str)
		return (NULL);
	ptr = (char **)gc_malloc(sizeof(char *)
			*(count_words(str, c) + 1), 0);
	if (!ptr || command == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count_words(str, c))
	{
		ptr[j] = (char *)gc_malloc(count_lengh_of_str(str, c, &i)
				+ ft_strlen(command) + 2, 0);
		j++;
	}
	ptr[j] = NULL;
	return (ptr);
}

char	**potential_path(char *command)
{
	char	*path;
	char	**splited_path;
	char	**potential_paths;
	char	*join;
	int		i;

	path = ft_getenv("PATH");
	if (!path && ft_unset_flag(0) == 0)
		path = custom_strdup(PATH_, 0);
	splited_path = custom_split(path, ':', 0);
	if (splited_path == NULL)
	{
		return (NULL);
	}
		// return ((print_msg("minishell: ",
		// 			command, ": No such file or directory\n")), NULL);
	potential_paths = allocate_double_char(path, ':', command);
	i = 0;
	while (splited_path[i] != NULL)
	{
		join = custom_strjoin(splited_path[i], "/", 0);
		if (!join)
			return (NULL);
		potential_paths[i] = custom_strjoin(join, command, 0);
		i++;
	}
	return (potential_paths);
}

int check_current_dir(char **command, char *pwd, char **envp_)
{
	char	*path;
	
	(void)envp_;
	path  = current_dir(command, pwd);
	if (!path)
	{
		return (-1);
	}
	if (access(path, F_OK) == 0)
	{
		if (access(path, X_OK) == 0)
		{
			
		}
		else
			return (-2);
	}
	return (-1);
}

int	check_existans_and_permisisons(char *command)
{
	int		i;
	char	**potential_paths;

	potential_paths = potential_path(command);
	if (!potential_paths)
		return (-1);
	i = 0;
	while (potential_paths[i])
	{
		if (access(potential_paths[i], F_OK) == 0)
		{
			if (access(potential_paths[i], X_OK) == 0)
				return (i);
			else
			{
				ft_putstr_fd("permission denied\n", 2);
				return (ft_status(126), -1);
			}
		}
		i++;
	}
	ft_status(127);
	print_msg("minishell: ", command, ": command not found\n");
	return (-1);
}
