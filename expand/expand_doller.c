/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_doller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 01:04:15 by satushi           #+#    #+#             */
/*   Updated: 2023/02/24 10:06:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand_args_doller(char *args, char *args_free)
{
	char	*new_word;
	char	type;

	new_word = NULL;
	while (*args != '\0')
	{
		if (*args == '\'' || *args == '\"')
		{
			type = *args;
			append_char(&new_word, *args++);
			while (*args != type)
				append_char(&new_word, *args++);
			append_char(&new_word, *args++);
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

void	expand_doller(char **dst, char **rest, char *p)
{
	char	*name;
	char	*value;

	name = calloc(1, sizeof(char));
	if (name == NULL)
		fatal_error("calloc");
	p++;
	if (!isalpha(*p) && *p != '_')
	{
		append_char(dst, *(p - 1));
		append_char(dst, *(p));
		*rest = p + 1;
		return ;
	}
	append_char(&name,*p++);
	while (isalpha(*p) != 0 || *p == '_' || isdigit(*p) != 0)
		append_char(&name,*p++);
	value = map_get(g_env, name);
	free(name);
	if (value)
		while (*value)
			append_char(dst, *value++);
	*rest = p;
}

void	expand_doller_dq(char **dst, char **rest, char *p)
{
	char	*name;
	char	*value;

	name = calloc(1, sizeof(char));
	if (name == NULL)
		fatal_error("calloc");
	p++;
	if (!isalpha(*p) && *p != '_')
	{
		append_char(dst, *(p - 1));
		append_char(dst, *(p));
		*rest = p + 1;
		return ;
	}
	append_char(&name,*p++);
	while ((isalpha(*p) != 0 || *p == '_' || isdigit(*p) != 0) && *p != '\"')
		append_char(&name,*p++);
	value = getenv(name);
	free(name);
	if (value)
		while (*value)
			append_char(dst, *value++);
	*rest = p;
}
