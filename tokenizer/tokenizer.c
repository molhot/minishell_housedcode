/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satushi <satushi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:42:10 by satushi           #+#    #+#             */
/*   Updated: 2023/02/19 20:15:13 by satushi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	consume_blank(char **rest, char *line)
{
	if (is_blank(*line))
	{
		while (*line && is_blank(*line))
			line++;
		*rest = line;
		return (true);
	}
	*rest = line;
	return (false);
}

bool	startswith(const char *s, const char *keyword)
{
	return (ft_memcmp(s, keyword, strlen(keyword)) == 0);
}

t_token	*tokenizer(char *line)
{
	t_token	head;
	t_token	*tok;

	head.next = NULL;
	tok = &head;
	while (*line)
	{
		if (consume_blank(&line, line))
			continue ;
		else if (is_operator(line) || is_word(line) || is_redirect(line))
		{
			if (is_operator(line))
				tok->next = operator(&line, line);
			else if (is_word(line))
				tok->next = word(&line, line);
			else if (is_redirect(line))
				tok->next = redirect(&line, line);
			tok = tok->next;
		}
		else
			tokenize_error("Unexpected Token", &line, line);
	}
	tok->next = new_token(NULL, TK_EOF);
	return (head.next);
}

void	free_token(t_token *head)
{
	t_token	*itr;
	t_token	*next;

	itr = head;
	next = itr->next;
	while (next != NULL)
	{
		free(itr->word);
		free(itr);
		itr = next;
		next = itr->next;
	}
	free(itr->word);
	free(itr);
}
