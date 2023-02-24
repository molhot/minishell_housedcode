/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 20:20:06 by user              #+#    #+#             */
/*   Updated: 2023/02/18 02:22:22 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_env(void)
{
	t_item	*itr;
	size_t	size;
	char	*name_and_value;

	itr = g_env->item_head;
	while (itr != NULL)
	{
		size = ft_strlen(itr->name) + ft_strlen(itr->value) + 2;
		name_and_value = malloc(size);
		ft_strlcat(name_and_value, itr->name, size);
		ft_strlcat(name_and_value, "=", size);
		ft_strlcat(name_and_value, itr->value, size);
		printf("%s\n", name_and_value);
		free(name_and_value);
		itr = itr->next;
	}
}
