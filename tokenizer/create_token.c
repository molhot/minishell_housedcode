/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:32:06 by user              #+#    #+#             */
/*   Updated: 2023/02/19 19:36:44 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*new_token(char *word, t_token_kind kind)
{
	t_token	*tok;

	tok = ft_calloc(1, sizeof(*tok));
	if (tok == NULL)
		fatal_error("calloc");
	tok->word = word;
	tok->kind = kind;
	return (tok);
}

char	*token_append(int flag)
{
	char	*return_str;

	return_str = NULL;
	if (flag == SINGLE)
		return_str = readline("single > ");
	else if (flag == DOUBLE)
		return_str = readline("doublele > ");
	return_str = ft_strjoin("\n", return_str);
	return (return_str);
}
