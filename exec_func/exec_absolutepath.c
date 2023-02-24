/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_absolutepath.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:56:43 by satushi           #+#    #+#             */
/*   Updated: 2023/02/19 22:45:47 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	**line_to_argv(char *line)
{
	char	**argv;
	size_t	position;

	position = 0;
	while (line[position] != '\0')
	{
		if (isspace(line[position]))
		{
			argv = ft_split(line, ' ');
			return (argv);
		}
		position++;
	}
	argv = malloc(sizeof(char *) * 2);
	argv[0] = line;
	argv[1] = NULL;
	return (argv);
}

int	abusolute_path(char *line)
{
	char		**argv;
	pid_t		pid;
	int			wstatus;
	extern char	**environ;

	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
	{
		argv = line_to_argv(line);
		execve(argv[0], argv, environ);
		fatal_error("execve\n");
		return (1);
	}
	else
	{
		wait(&wstatus);
		return (WEXITSTATUS(wstatus));
	}
}
