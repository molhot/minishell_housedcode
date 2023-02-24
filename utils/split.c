/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:48:29 by satushi           #+#    #+#             */
/*   Updated: 2023/02/18 05:48:36 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	structure_in(const char *s, char c)
{
	int	individual_arrangementlength;

	individual_arrangementlength = 0;
	if (*s != '\0')
	{
		while ((*s) == c)
			s = s + 1;
		if (*s == '\0' && c != '\0')
			return (0);
		if (*s != '\0')
		{
			while ((*s) != c)
			{
				individual_arrangementlength = individual_arrangementlength + 1;
				s = s + 1;
				if (*s == '\0')
					break ;
			}
		}
	}
	return (individual_arrangementlength);
}

static size_t	secure_arrangement(const char (*s), char c)
{
	int		arrangement_row;
	int		counter_add;

	if (s == NULL || (*s == '\0' && c == '\0'))
		return (1);
	if (c == '\0')
		return (2);
	arrangement_row = 1;
	counter_add = 0;
	while (*s == c)
	{
		s = s + 1;
		counter_add = counter_add + 1;
	}
	while ((*s) != '\0')
	{
		if (*s != c && *(s + 1) == c)
			arrangement_row = arrangement_row + 1;
		s = s + 1;
		counter_add = counter_add + 1;
	}
	if (*(s - 1) != c && counter_add != 0)
		arrangement_row = arrangement_row + 1;
	return (arrangement_row);
}

static size_t	ft_insert_arrangement(char (*row), const char (*s), char c)
{
	int	counter_insert;

	counter_insert = 0;
	if (*s == '\0' && c == '\0')
	{
		*row = '\0';
		return (0);
	}
	while (((*(s + counter_insert)) == c) && (*(s + counter_insert)) != '\0')
		counter_insert = counter_insert + 1;
	if (*(s + counter_insert) == '\0')
	{
		row = NULL;
		return (counter_insert);
	}
	while (((*(s + counter_insert)) != c) && (*(s + counter_insert) != '\0'))
	{
		*row = *(s + counter_insert);
		row = row + 1;
		counter_insert = counter_insert + 1;
	}
	*(row) = '\0';
	return (counter_insert);
}

static char	**ft_free(int i, char (**arrangement))
{
	int	first;

	first = 0;
	while (first != i)
	{
		free(arrangement[first]);
		first = first + 1;
	}
	free(arrangement);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char		**arbox;
	size_t		i;
	size_t		mallocsize_arrange;
	size_t		structure;

	mallocsize_arrange = secure_arrangement(s, c);
	arbox = (char **)malloc(sizeof(char *) * mallocsize_arrange);
	if (!(arbox))
		return (NULL);
	i = 0;
	if (mallocsize_arrange != 1)
	{
		while (i != (mallocsize_arrange - 1))
		{
			structure = structure_in(s, c);
			arbox[i] = (char *)malloc(sizeof(char) * (structure + 1));
			if (!(arbox[i]))
				return (ft_free(i - 1, arbox));
			s = s + ft_insert_arrangement(arbox[i], s, c);
			i = i + 1;
		}
	}
	arbox[mallocsize_arrange - 1] = NULL;
	return (arbox);
}
