/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:46:37 by user              #+#    #+#             */
/*   Updated: 2023/02/21 07:49:09 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	do_builtin(char *line, t_command *command)
{
	if (ft_strcmp(command->args->word, "env") == 0)
		ms_env();
	else if (ft_strncmp(command->args->word, "export", 6) == 0)
		ms_export(line, command);
	else if (ft_strncmp(command->args->word, "pwd", 3) == 0)
		ms_pwd();
	else if (ft_strncmp(command->args->word, "cd", 2) == 0)
		ms_cd(line, command);
	else if (ft_strncmp(command->args->word, "exit", 4) == 0)
		ms_exit(line, command);
	else if (ft_strncmp(command->args->word, "unset", 5) == 0)
		ms_unset(line, command);
	else if (ft_strncmp(command->args->word, "echo", 4) == 0)
		ms_echo(line, command);
	return (0);
}
