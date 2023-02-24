/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:04:31 by user              #+#    #+#             */
/*   Updated: 2023/02/16 22:07:09 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_redirect(const char *s)
{
	static char *const	redirect[] = {"<", ">"};
	size_t				i;

	i = 0;
	while (i < sizeof(redirect) / sizeof(*redirect))
	{
		if (startswith(s, redirect[i]))
			return (true);
		i++;
	}
	return (false);
}
