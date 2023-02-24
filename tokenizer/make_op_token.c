/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_op_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:38:37 by user              #+#    #+#             */
/*   Updated: 2023/02/19 19:38:32 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*operator(char **rest, char *line)
{
	static char *const	operators[] = \
	{"||", "&", "&&", ";", ";;", "(", ")", "|", "\n"};
	size_t				i;
	char				*op;

	i = 0;
	while (i < sizeof(operators) / sizeof(*operators))
	{
		if (startswith(line, operators[i]))
		{
			op = ft_strdup(operators[i]);
			if (op == NULL)
				fatal_error("strdup");
			*rest = line + ft_strlen(op);
			return (new_token(op, TK_OP));
		}
		i++;
	}
	fatal_error("Unexpected operator");
}
