/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:32:50 by satushi           #+#    #+#             */
/*   Updated: 2023/02/24 19:32:30 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	heredoc(const char *deli)
{
	char	*line;
	int		pfd[2];

	if (pipe(pfd) < 0)
		return (25555);
	while (1)
	{
		line = readline("input > ");
		if (line == NULL)
			break ;
		else if (ft_strcmp(line, deli) == 0)
		{
			free(line);
			break ;
		}
		dprintf(pfd[1], "%s\n", line);
		free(line);
	}
	close (pfd[1]);
	return (pfd[0]);
}

void	ready_redirectionfile(t_node *node)
{
	int			fd;
	t_redirect	*redirect;

	while (node != NULL)
	{
		redirect = *(node->command->redirect);
		while (redirect != NULL)
		{
			if (redirect->type == IN)
				fd = open(redirect->file_path, O_RDONLY);
			if (redirect->type == HEREDOC)
				fd = heredoc(redirect->file_path);
			if (redirect->type == OUT)
				fd = open(redirect->file_path, \
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (redirect->type == APPEND)
				fd = open(redirect->file_path, \
				O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (fd != -1)
				fd = stashfd(fd);
			redirect->redirectfile = fd;
			redirect = redirect->next;
		}
		node = node->next;
	}
}

void	inout_reconnect(int file_fd, int fd, t_command *command)
{
	dup2(file_fd, fd);
	close(file_fd);
	command->now_in = file_fd;
}

int	redirect_reconect(t_command *command)
{
	t_redirect	*redirect;
	int			flag;

	flag = 0;
	if (command->redirect == NULL)
		return (flag);
	redirect = *(command->redirect);
	while (redirect != NULL)
	{
		if (redirect->redirectfile == -1 || redirect->ambigous == true)
			return (1);
		if (redirect->type == IN || redirect->type == HEREDOC)
		{
			redirect->stashed_fd = stashfd(0);
			inout_reconnect(redirect->redirectfile, 0, command);
		}
		if (redirect->type == OUT || redirect->type == APPEND)
		{
			redirect->stashed_fd = stashfd(1);
			inout_reconnect(redirect->redirectfile, 1, command);
		}
		redirect = redirect->next;
	}
	return (flag);
}
