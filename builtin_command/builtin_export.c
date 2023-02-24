/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:22:25 by user              #+#    #+#             */
/*   Updated: 2023/02/24 20:01:35 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	ch_word_alphabet(char ch)
{
	if ((('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z')) || ch == '_')
		return (true);
	return (false);
}

bool	exportwd_check(char *arg)
{
	if (ch_word_alphabet(*arg) == false)
		return (false);
	arg++;
	while (*arg != '\0')
	{
		if (!(0 <= *arg && *arg <= 127))
			return (false);
	}
	return (true);
}

void	ms_export(char *line, t_command *command)
{
	char	**commands;
	char	**name_and_value;

	(void)line;
	commands = command_to_array(command);
	if (commands != 0 && commands[0] != NULL)
	{
		if (exportwd_check(commands[1]) == false)
		{
			printf("minishell: export: `%s': not a valid identifier\n", command->args->next->word);
			return ;
		}
		name_and_value = ft_split(commands[1], '=');
		if (name_and_value[0] && name_and_value[1])
		{
			map_set(&g_env, name_and_value[0], name_and_value[1]);
			return ;
		}
		else
			return ;
	}
	puts("TODO: print usage");
}
