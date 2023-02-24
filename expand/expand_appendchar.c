/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_appendchar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:03:13 by satushi           #+#    #+#             */
/*   Updated: 2023/02/22 13:22:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_char(char **s, char c)
{
	size_t	size;
	char	*new;

	size = 2;
	if (*s)
		size += ft_strlen(*s);
	new = malloc(size);
	if (new == NULL)
		fatal_error("malloc");
	if (*s)
		ft_strlcpy(new, *s, size);
	new[size - 2] = c;
	new[size - 1] = '\0';
	if (*s)
		free(*s);
	*s = new;
}

void	append_single(char **args, char **new)
{
	while (**args != '\'')
	{
		append_char(&(*new), **args);
		(*args)++;
	}
}

void	append_double(char **args, char **new, char *args_dummy)
{
	while (**args != '\"')
	{
		if (**args == '$')
		{
			expand_doller_dq(&(*new), &(*args), args_dummy);
			args_dummy = *args;
		}
		else
		{
			append_char(&(*new), **args);
			(*args)++;
		}
	}
}
