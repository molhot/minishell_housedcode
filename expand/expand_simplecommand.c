/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_simplecommand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 22:31:02 by marvin            #+#    #+#             */
/*   Updated: 2023/02/21 22:31:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	word_blankcheck(char *string)
{
	while (*string != '\0')
	{
		if (is_blank(*string))
			return (true);
		string++;
	}
	return (false);
}

void	split_tokenword(t_token **token, t_token **re_token)
{
	char	**tokenwd_split;
	size_t	position;

	tokenwd_split = ft_split((*token)->word, ' ');
	position = 0;
	while (tokenwd_split[position] != NULL)
	{
		(*re_token)->word = ft_strdup(tokenwd_split[position]);
		(*re_token)->kind = TK_WORD;
		if (tokenwd_split[position + 1] != NULL)
		{
			(*re_token)->next = (t_token *)malloc(sizeof(t_token) * 1);
			*re_token = (*re_token)->next;
		}
		free(tokenwd_split[position]);
		position++;
	}
	free(tokenwd_split);
	(*token) = (*token)->next;
}

void	expand_specialparam(t_token *token)
{
	while (token != NULL)
	{
		token->word = expand_args_doller(token->word, token->word);
		token = token->next;
	}
}

void	re_token_in_null(t_token **token, t_token **re_token)
{
	(*re_token)->word = NULL;
	(*re_token)->kind = TK_WORD;
	if ((*token)->next != NULL)
	{
		(*re_token)->next = (t_token *)malloc(sizeof(t_token) * 1);
		(*re_token) = (*re_token)->next;
	}
	(*token) = (*token)->next;
}

void	remake_token(t_token *token, t_token *re_token)
{
	t_token	*tmp_token;

	while (token != NULL)
	{
		tmp_token = token;
		if (token->word == NULL && (token->next == NULL || token->next->kind == TK_OP))
			re_token_in_null(&token, &re_token);
		else if (token->word == NULL)
			token = token->next;
		else if (word_blankcheck(token->word) && (token->word[0] != '\'' && token->word[0] != '\"'))
			split_tokenword(&token, &re_token);
		else
		{
			re_token->word = ft_strdup(token->word);
			re_token->kind = token->kind;
			if (token->next != NULL)
			{
				re_token->next = (t_token *)malloc(sizeof(t_token) * 1);
				re_token = re_token->next;
			}
			token = token->next;
		}
		free(tmp_token);
	}
	re_token->next = NULL;
}

void	expand_quote(t_token *token)
{
	while (token != NULL)
	{
		if (token->word != NULL)
			token->word = expand_args_quote(token->word, token->word);
		token = token->next;
	}
}

char	*expand_args_quote(char *args, char *args_free)
{
	char	*new_word;

	new_word = NULL;
	while (*args != '\0')
	{
		if (*args == '\'' || *args == '\"')
		{
			if (*args == '\'')
				append_single(&args, &new_word);
			else if (*args == '\"')
				append_double(&args, &new_word, args);
			args++;
		}
		else if (*args == '$' && (*(args + 1) == '\0' || *(args + 1) == '\'' || *(args + 1) == '\"'))
			append_char(&new_word, *args++);
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