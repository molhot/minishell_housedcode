/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:48:40 by satushi           #+#    #+#             */
/*   Updated: 2023/02/18 05:48:43 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	char		src;
	char		*s_2;
	size_t		num;

	s_2 = (char *)s;
	num = ft_strlen(s_2);
	src = (char)c;
	if (*s == '\0' && c == '\0')
		return ((char *)s);
	if (c == '\0')
		return (s_2 + num);
	while (num != 0)
	{
		if ((unsigned char)*s_2 == (unsigned char)src)
			return (s_2);
		num = num - 1;
		s_2 = s_2 + 1;
	}
	return (NULL);
}
