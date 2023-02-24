/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 00:37:31 by satushi           #+#    #+#             */
/*   Updated: 2023/02/24 14:01:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_args(char *args, char *args_free)
{
	char	*new_word;

	new_word = NULL;
	while (*args != '\0')
	{
		if (*args == '\'' || *args == '\"')
		{
			args++;
			if (*(args - 1) == '\'')
				append_single(&args, &new_word);
			else if (*(args - 1) == '\"')
				append_double(&args, &new_word, args);
			args++;
		}
		else if (*args == '$' && *(args + 1) == '?')
			expand_dolleeques(&new_word, &args, args);
		else if (*args == '$')
			expand_doller(&new_word, &args, args);
		else
			append_char(&new_word, *args++);
	}
	free(args_free);
	return (new_word);
}

void	expand_redirect(t_redirect *redirect)
{
	while (redirect != NULL)
	{
		if (redirect->type != HEREDOC)
			redirect->file_path = expand_args(redirect->file_path, \
			redirect->file_path);
		redirect = redirect->next;
	}
}

t_token	*expand_simplecommand(t_token *token)
{
	t_token	*re_token;
	t_token	*f_re_tok;

	re_token = (t_token *)malloc(sizeof(t_token) * 1);
	f_re_tok = re_token;
	expand_specialparam(token);
	remake_token(token, re_token);
	expand_quote(re_token);
	return (f_re_tok);
}

void	expand(t_node *node)
{
	t_redirect	*redirect;
	t_token		*token;

	while (node != NULL)
	{
		token = node->command->args;
		if (node->command->args != NULL)
			node->command->args = expand_simplecommand(token);
		if (node->command->redirect != NULL)
		{
			redirect = *(node->command->redirect);
			*(node->command->redirect) = expand_redirect_ten(redirect);
		}
		node = node->next;
	}
}
