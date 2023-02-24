/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 05:32:46 by satushi           #+#    #+#             */
/*   Updated: 2023/02/24 14:20:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_node	*ready_nextnode(bool *flag, t_node *node, t_token **token)
{
	if (*flag == true)
		(*(node->command->redirect)) = NULL;
	*flag = true;
	node->next = new_node(ND_SIMPLE_CMD);
	ready_redirectinout(node->next, &(*flag), false);
	node->next->command->redirect = \
	(t_redirect **)malloc(sizeof(t_redirect *) * 1);
	node->next->command->args = NULL;
	*token = (*token)->next;
	return (node->next);
}

void	tok_parsing(t_token *tok, t_node *node, bool first_action)
{
	t_redirect	*redirection_node;

	while (tok && !at_eof(tok))
	{
		if (tok->kind == TK_WORD)
			parse_word(&node->command->args, tokdup(tok), &tok);
		else if (tok->kind == TK_REDIRECT)
		{
			if (first_action == true)
				redirection_node = tok_to_redirect_f(&first_action, node, &tok);
			else
				redirection_node = tok_to_redirect(redirection_node, &tok);
			tok = tok->next->next;
		}
		else if (tok->kind == TK_OP)
		{
			if (first_action == false)
				redirection_node->next = NULL;
			node = ready_nextnode(&first_action, node, &tok);
		}
		else
			fatal_error("Implement parser");
	}
	if (first_action == true)
		(*(node->command->redirect)) = NULL;
	else
		redirection_node->next = NULL;
	node->next = NULL;
}

t_node	*parse(t_token *tok)
{
	t_node		*node;
	t_node		*fnode;
	bool		first_action;

	node = new_node(ND_SIMPLE_CMD);
	fnode = node;
	ready_redirectinout(node, &first_action, true);
	tok_parsing(tok, node, first_action);
	return (fnode);
}
