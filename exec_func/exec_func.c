/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:39:08 by satushi           #+#    #+#             */
/*   Updated: 2023/02/24 19:42:57 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*   Updated: 2023/02/23 15:57:58 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process(t_node *node, char *path, char **argv, char **environ)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	prepare_pipe_child(node);
	if (redirect_reconect(node->command) == 1)
		exit(1);
	if (is_builtin(node->command->args->word))
		exit(do_builtin(node->command->args->word, node->command));
	else
	{
		if (path[0] == '/' || path[0] == '.')
			execve(path, argv, environ);
		else
		{
			if (searchpath(path) == NULL)
				exit(127);
			else
				execve(searchpath(path), argv, environ);
		}
		exit(127);
	}
}

void	exec_check(t_node *node, char *path)
{
	t_redirect	*redirect;

	redirect = *(node->command->redirect);
	while (redirect != NULL)
	{
		if (redirect->redirectfile == -1 || redirect->ambigous == true)
		{
			if (redirect->file_path == NULL || redirect->ambigous == true)
				printf("minishell: %s: ambiguous redirect\n", \
				redirect->file_path);
			else
				printf("minishell: %s: No such file or directory\n", \
				redirect->file_path);
			g_env->err_status = 1;
			return ;
		}
		redirect = redirect->next;
	}
	if (is_builtin(path) == false && path[0] != '/' && path[0] != '.' \
	&& searchpath(path) == NULL && ft_strcmp("exit", path) != 0)
	{
		printf("bash: %s: command not found :x\n", path);
		g_env->err_status = 127;
	}
}

pid_t	exec_pipeline(t_node *node)
{
	extern char	**environ;
	pid_t		pid;
	char		**argv;

	if (node == NULL)
		return (-1);
	argv = args_to_argv(node->command->args);
	exec_check(node, argv[0]);
	prepare_pipe(node);
	pid = fork();
	if (pid < 0)
		fatal_error("fork");
	else if (pid == 0)
		child_process(node, argv[0], argv, environ);
	prepare_pipe_parent(node);
	if (node->next)
		return (exec_pipeline(node->next));
	return (pid);
}

int	exec(t_node *node)
{
	pid_t	last_pid;
	int		status;

	ready_redirectionfile(node);
	last_pid = exec_pipeline(node);
	status = wait_pipeline(last_pid);
	return (status);
}
