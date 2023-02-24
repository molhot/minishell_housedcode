/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:49:48 by user              #+#    #+#             */
/*   Updated: 2023/02/18 05:48:52 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	*input_char(const char *insert, char *inserted)
{
	while ((*insert) != '\0')
	{
		*inserted = *insert;
		insert = insert + 1;
		inserted = inserted + 1;
	}
	return (inserted);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len;
	char		*dust;
	char		*dust_first;

	if ((s1 == NULL) && (s2 == NULL))
		return (NULL);
	if (s1 == NULL)
		return (strdup(s2));
	if (s2 == NULL)
		return (strdup(s1));
	len = strlen(s1) + strlen(s2);
	dust = (char *)malloc(sizeof(char) * (len + 1));
	if (!(dust))
		return (NULL);
	dust_first = dust;
	dust = input_char(s1, dust);
	dust = input_char(s2, dust);
	*dust = '\0';
	return (dust_first);
}
