/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:39:32 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/07/15 05:48:28 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



// static int	count_words(const char *s, char c)
// {
// 	int		i;
// 	int		count;

// 	i = 0;
// 	count = 0;
// 	while (s[i])
// 	{
// 		if ((s[i] != c)
// 			&& (s[i + 1] == c || s[i + 1] == '\0'))
// 			count++;
// 		i++;
// 	}
// 	return (count);
// }

int	count_lengh_of_str(char *str, char c, int *i)
{
	int lengh;

	lengh = 0;
	while(str[*i] && str[*i] != c)
	{
		(*i)++;
		lengh++;
	}
	return(lengh);
}
// static char *path_extraction(t_env *environ ,t_env_var **env_vars)
// {
// 	while(environ)
// 	{
// 		if(!strcmp(environ->var,"PATH"))
// 		{
// 			if(!strcmp(environ->val, (*env_vars)->PATH))
// 			{
// 				return(environ->val);
// 			}
// 			else
// 				return(NULL);
// 		}
// 		environ =environ->next;
// 	}
// 	return(NULL);
// }

static char	**allocate_double_char(char *str, char c, char *command)
{
	int		i;
	int		j;
	char	**ptr;

	if (!str)
		return (NULL);
	ptr = (char **)gc_malloc(sizeof(char *) * (count_words(str, c) + 1), 0);
	if (!ptr || command == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (j < count_words(str, c))
	{
		ptr[j] = (char *)gc_malloc(count_lengh_of_str(str, c, &i) + ft_strlen(command) + 2, 0);
		j++;
	}
	ptr[j] = NULL;
	return (ptr);
}

char	**potential_path(t_env **environ, char *command)
{
	char	*PATH;
	char	**splited_path;
	char 	**potential_paths;
	char 	*join;
	int		i;
	
	
	PATH = get_value("PATH", *environ);
	// ft_unset_flag(0);
	if(!PATH && ft_unset_flag(0) == 0)
	{
		PATH=custom_strdup(PATH_, 0);
	}
	splited_path = custom_split(PATH,':', 0);
	if(splited_path == NULL)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(command , 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (NULL);
	}
	potential_paths = allocate_double_char(PATH,':',command);
	i = 0;
	while(splited_path[i] != NULL)
	{
		join = custom_strjoin(splited_path[i],"/", 0);
		if(!join)
			return(NULL);
		potential_paths[i] = custom_strjoin(join, command, 0);
		i++;
	}
	return(potential_paths);
}

int  check_existans_and_permisisons(t_env **environ,char *command, t_env_var **env_vars)
{
	int	i;
	char 	**potential_paths;
	

	potential_paths=potential_path(environ, command);
	if(!potential_paths)
		return(-1);
	i = 0;
	while(potential_paths[i])
	{
		if(access(potential_paths[i], F_OK) == 0)
		{
			if(access(potential_paths[i], X_OK ) == 0)
				return(i);
			else
			{
				ft_putstr_fd("permission denied\n",2);
				*((*env_vars)->status) = 126;
				return(-1);
			}
		}
		i++;
	}
	// ft_status(127);
	*((*env_vars)->status) = 127;
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(command , 2);
	ft_putstr_fd(": command not found\n", 2);
	// ft_putstr_fd("bash: command not found\n",2);
	return(-1);
}
