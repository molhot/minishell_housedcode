/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:16:50 by satushi           #+#    #+#             */
/*   Updated: 2023/02/18 05:18:58 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	cpy_pipe(int dst[2], int src[2])
{
	dst[0] = src[0];
	dst[1] = src[1];
}

void	prepare_pipe(t_node *node)
{
	if (node->next == NULL)
		return ;
	if (pipe(node->command->out_fd) < 0)
		fatal_error("pipe");
	cpy_pipe(node->next->command->in_fd, node->command->out_fd);
}

void	prepare_pipe_child(t_node *node)
{
	close(node->command->out_fd[0]);
	dup2(node->command->in_fd[0], STDIN_FILENO);
	if (node->command->in_fd[0] != STDIN_FILENO)
		close(node->command->in_fd[0]);
	dup2(node->command->out_fd[1], STDOUT_FILENO);
	if (node->command->out_fd[1] != STDOUT_FILENO)
		close(node->command->out_fd[1]);
}

void	prepare_pipe_parent(t_node *node)
{
	if (node->command->in_fd[0] != STDIN_FILENO)
		close(node->command->in_fd[0]);
	if (node->next != NULL)
		close(node->command->out_fd[1]);
}

int	wait_pipeline(pid_t last_pid)
{
	pid_t	wait_result;
	int		status;
	int		wstatus;

	while (1)
	{
		wait_result = wait(&wstatus);
		if (wait_result == last_pid)
			status = WEXITSTATUS(wstatus);
		else if (wait_result < 0)
		{
			if (errno == ECHILD)
				break ;
		}
	}
	return (status);
}
