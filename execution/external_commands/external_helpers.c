/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 01:39:32 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/06/21 07:30:48 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



static int	count_words(const char *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i] != c)
			&& (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

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

static char	**allocate_double_char(char *str, char c, char *command)
{
	int		i;
	int		j;
	char	**ptr;

	if (!str)
		return (NULL);
	ptr = (char **)malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (!ptr || command == NULL)
		return (NULL);
	(1 && (i = 0), (j = 0));
	while (j < count_words(str, c))
	{
		ptr[j] = (char *)malloc(count_lengh_of_str(str, c, &i) + ft_strlen(command) + 2);
		if (!ptr[j])
		{
			while (--j >= 0)
				free(ptr[j]);
			return (free(ptr), NULL);
		}
		j++;
	}
	ptr[j] = NULL;
	return (ptr);
}

char	**potential_path(char *command)
{
	char	*PATH;
	char	**splited_path;
	char 	**potential_paths;
	char 	*join;
	int		i;

	PATH = getenv("PATH");
	if(PATH == NULL)
		return(NULL);
	splited_path = ft_split(PATH,':');
	if(splited_path == NULL)
		return (NULL);
	potential_paths = allocate_double_char(PATH,':',command);
	i = 0;
	while(splited_path[i] != NULL)
	{
		join = ft_strjoin(splited_path[i],"/");
		if(!join)
			return(NULL);
		potential_paths[i] = ft_strjoin(join, command);
		i++;
	}
	return(potential_paths);
}

int  check_existans_and_permisisons(char *command, int *status)
{
	int	i;
	char 	**potential_paths;

	potential_paths=potential_path(command);
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
				printf("permission denied");
				*status = 126;
				return(-1);
			}
		}
		i++;
	}
	*status = 127;
	printf("bash: %s: command not found\n", command);
	return(-1);
}
