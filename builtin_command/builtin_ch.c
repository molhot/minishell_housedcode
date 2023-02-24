/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 17:45:47 by user              #+#    #+#             */
/*   Updated: 2023/02/23 17:29:06 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_builtin(char *line)
{
	if (strncmp("export", line, ft_strlen("export")) == 0)
		return (true);
	else if (strncmp("env", line, ft_strlen("env")) == 0)
		return (true);
	else if (strncmp("pwd", line, ft_strlen("pwd")) == 0)
		return (true);
	else if (strncmp("cd", line, ft_strlen("cd")) == 0)
		return (true);
	else if (strncmp("exit", line, ft_strlen("exit")) == 0)
		return (true);
	else if (strncmp("unset", line, ft_strlen("unset")) == 0)
		return (true);
	else if (strncmp("echo", line, ft_strlen("echo")) == 0)
		return (true);
	else
		return (false);
}
