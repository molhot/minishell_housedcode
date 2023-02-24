/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 23:22:25 by user              #+#    #+#             */
/*   Updated: 2023/02/22 22:23:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_redirect	*tok_to_redirect_f(bool *flag, t_node *node, t_token **tok)
{
	parse_redirect(&(*node->command->redirect), &(*tok));
	(*node->command->redirect)->ambigous = false;
	*flag = false;
	(*node->command->redirect)->before = NULL;
	return (*node->command->redirect);
}

t_redirect	*tok_to_redirect(t_redirect *redirect, t_token **tok)
{
	parse_redirect(&(redirect->next), &(*tok));
	redirect->next->ambigous = false;
	redirect->next->before = redirect;
	return (redirect->next);
}

bool	parse_redirect(t_redirect **redirect, t_token **tok)
{
	*redirect = malloc(sizeof(t_redirect));
	if (ft_strcmp((*tok)->word, ">") == 0 && \
	ft_strcmp((*tok)->next->word, ">") == 0)
	{
		(*redirect)->type = APPEND;
		*tok = (*tok)->next;
	}
	else if (ft_strcmp((*tok)->word, "<") == 0 \
	&& ft_strcmp((*tok)->next->word, "<") == 0)
	{
		(*redirect)->type = HEREDOC;
		*tok = (*tok)->next;
	}
	else if (ft_strcmp((*tok)->word, "<") == 0)
		(*redirect)->type = IN;
	else
		(*redirect)->type = OUT;
	if ((*tok)->next->kind == TK_WORD)
		(*redirect)->file_path = ft_strdup((*tok)->next->word);
	else
		fatal_error("redirection end or not?\n");
	return (true);
}

void	ready_redirectinout(t_node *node, bool *flag, bool f_content)
{
	if (f_content == true)
		node->command->redirect = \
		(t_redirect **)malloc(sizeof(t_redirect *) * 1);
	node->command->in_fd[0] = STDIN_FILENO;
	node->command->in_fd[1] = -1;
	node->command->out_fd[0] = -1;
	node->command->out_fd[1] = STDOUT_FILENO;
	*flag = true;
}
