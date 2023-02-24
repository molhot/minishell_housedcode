/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 13:36:34 by satushi           #+#    #+#             */
/*   Updated: 2023/02/19 14:16:39 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	position;

	position = 0;
	s1_len = ft_strlen(s1);
	if (s1_len != ft_strlen(s2))
		return (1);
	while (position != s1_len)
	{
		if (s1[position] != s2[position])
			return (s1[position] - s2[position]);
		position++;
	}
	return (0);
}
