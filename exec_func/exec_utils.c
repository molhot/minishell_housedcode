/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 19:59:30 by satushi           #+#    #+#             */
/*   Updated: 2023/02/24 19:43:55 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**args_to_argv(t_token *args)
{
	size_t	len;
	char	**argv;
	size_t	i;
	t_token	*itr;

	len = 0;
	i = 0;
	itr = args;
	while (itr != NULL)
	{
		len++;
		itr = itr->next;
	}
	argv = malloc(sizeof(char *) * (len + 1));
	itr = args;
	while (i != len)
	{
		argv[i] = ft_strdup(itr->word);
		itr = itr->next;
		i++;
	}
	argv[len] = NULL;
	return (argv);
}

int	stashfd(int fd)
{
	int	stashfd;

	stashfd = fcntl(fd, F_DUPFD, 10);
	close(fd);
	return (stashfd);
}

char	*searchpath(const char *filename)
{
	char	*path;
	char	*value;
	char	*end;

	value = getenv("PATH");
	path = (char *)malloc(sizeof(char) * PATH_MAX);
	if (ft_strlen(filename) > PATH_MAX)
		return (NULL);
	while (*value != '\0')
	{
		bzero(path, PATH_MAX);
		end = ft_strchr(value, ':');
		if (end)
			strncpy(path, value, end - value);
		else
			ft_strlcpy(path, value, PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, filename, PATH_MAX);
		if (access(path, X_OK) == 0)
			return (accessok_file(path));
		if (end == NULL)
		{
			free(path);
			return (NULL);
		}
		value = end + 1;
	}
	free(path);
	assert(false);
	return (NULL);
}

char	*accessok_file(char *path)
{
	char	*dup;

	dup = ft_strdup(path);
	if (dup == NULL)
		return (NULL);
	return (dup);
}
