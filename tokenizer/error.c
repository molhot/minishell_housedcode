/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:56:53 by user              #+#    #+#             */
/*   Updated: 2023/02/24 20:45:25 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fatal_error(const char *msg)
{
	write(STDERR_FILENO, "Fatal Error: ", ft_strlen("Fatal Error: "));
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", ft_strlen("\n"));
	exit(1);
}

void	tokenize_error(const char *location, char **rest, char *line)
{
	write(STDERR_FILENO, "Fatal Error: ", ft_strlen("Fatal Error: "));
	write(STDERR_FILENO, location, ft_strlen(location));
	write(STDERR_FILENO, "\n", ft_strlen("\n"));
	while (*line)
		line++;
	*rest = line;
}
