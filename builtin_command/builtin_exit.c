/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:21:24 by user              #+#    #+#             */
/*   Updated: 2023/02/18 02:23:22 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_exit(char *line, t_command *command)
{
	char	**commands;

	(void)line;
	commands = command_to_array(command);
	if (commands[1] == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	if (!atoi(commands[1]) || (atoi(commands[1]) == -1 \
	&& ft_strlen(commands[1]) > 2))
	{
		printf("minishell: exit: numeric argument required\n");
		exit(255);
	}
	printf("exit\n");
	exit(atoi(commands[1]));
}
