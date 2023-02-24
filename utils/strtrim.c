/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:49:12 by satushi           #+#    #+#             */
/*   Updated: 2023/02/18 05:49:14 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	*check_first(char const *s1, char const *set)
{
	size_t	len;

	len = ft_strlen(s1);
	while (len != 0)
	{
		if (ft_strchr(set, (*s1)) == 0)
			break ;
		len = len - 1;
		s1 = s1 + 1;
	}
	return ((char *)s1);
}

static	char	*check_last(char const *s1, char const *set)
{
	size_t	len;

	len = ft_strlen(s1);
	s1 = s1 + len - 1;
	while (len-- != 0)
	{
		if (ft_strchr(set, (*s1)) == 0)
			break ;
		s1 = s1 - 1;
	}
	return ((char *)(s1 + 1));
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*s1_copy;
	const char	*firstaddress;
	const char	*lastaddress;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	if (*s1 == '\0' && *set == '\0')
		return (ft_strdup(""));
	firstaddress = check_first(s1, set);
	lastaddress = check_last(s1, set);
	if (firstaddress >= lastaddress)
		return (ft_strdup(""));
	s1_copy = (char *)malloc(sizeof(char) * (lastaddress - firstaddress + 1));
	if (s1_copy == NULL)
		return (NULL);
	ft_strlcpy(s1_copy, firstaddress, (size_t)(lastaddress - firstaddress + 1));
	return (s1_copy);
}
