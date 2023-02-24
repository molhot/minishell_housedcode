/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:28:10 by user              #+#    #+#             */
/*   Updated: 2023/02/24 16:20:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <assert.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <ctype.h>
# include <stdbool.h>
# include "./libft/libft.h"
# include <fcntl.h>
# include <stdint.h>
# define IN 0
# define OUT 1
# define APPEND 2
# define HEREDOC 3
# define SINGLE 1
# define DOUBLE 2

typedef struct s_token	t_token;
typedef struct s_redirect	t_redirect;

typedef enum e_token_kind{
	TK_WORD,
	TK_RESERVED,
	TK_REDIRECT,
	TK_OP,
	TK_EOF,
}	t_token_kind;

struct	s_token {
	char			*word;
	t_token_kind	kind;
	t_token			*next;
};

typedef enum e_node_kind {
	ND_SIMPLE_CMD,
}	t_node_kind;

typedef struct s_redirect
{
	int					type;
	char				*file_path;
	int					stashed_fd;
	int					redirectfile;
	t_redirect			*next;
	t_redirect			*before;
	bool				ambigous;
}	t_redirect;

typedef struct s_command
{
	t_token		*args;
	t_redirect	**redirect;
	int			in_fd[2];
	int			out_fd[2];
	int			now_in;
	int			now_out;
}	t_command;

typedef struct s_node	t_node;

struct s_node {
	t_command	*command;
	t_node_kind	kind;
	t_node		*next;
};

/********* MAP ***********/

typedef struct s_item {
	char			*name;
	char			*value;
	struct s_item	*next;
}				t_item;

typedef struct s_map{
	t_item	*item_head;
	int		err_status;
}				t_map;

extern t_map	*g_env;

/****************** MAP *******************/

t_item		*item_new(char *name, char *value);
t_map		*map_new(void);
char		*map_get(t_map *map, const char *name);
void		map_set(t_map **map, char *name, char *value);
void		map_unset(t_map **map, char *name);

/************* builtin command ************/

bool		is_builtin(char *line);
void		ms_cd(char *line, t_command *command);
void		ms_env(void);
int			ms_echo(char *line, t_command *command);
void		ms_exit(char *line, t_command *command);
void		ms_export(char *line, t_command *command);
void		ms_pwd(void);
void		ms_unset(char *line, t_command *command);
char		**command_to_array(t_command *command);

/******************* env *****************/

void		env_init(t_map **env);
char		*get_name(char *name_and_value);

/**************** tokcheck ***************/

bool		tokcheck(t_token *tok);

/*************** torkenizer **************/

t_token		*tokenizer(char *line);
void		tokenize_error(const char *location, char **rest, char *line);
t_token		*new_token(char *word, t_token_kind kind);
char		*token_append(int flag);
t_token		*redirect(char **rest, char *line);
t_redirect	*tok_to_redirect_f(bool *flag, t_node *node, t_token **tok);
t_redirect	*tok_to_redirect(t_redirect *redirect, t_token **tok);
t_token		*word(char **rest, char *line);
t_token		*operator(char **rest, char *line);

/***************** parser ****************/

t_node		*parse(t_token *tok);
bool		parse_redirect(t_redirect **redirect, t_token **tok);
void		parse_word(t_token **args, t_token *tok, t_token **tok_o);
void		append_tok(t_token **tokens, t_token *tok);
void		ready_redirectinout(t_node *node, bool *flag, bool f_content);
bool		at_eof(t_token *tok);
t_node		*new_node(t_node_kind kind);
t_token		*tokdup(t_token *tok);
void		append_tok(t_token **tokens, t_token *tok);

/***************** expand ****************/

void		expand(t_node *node);
void		expand_doller(char **dst, char **rest, char *p);
void		expand_doller_dq(char **dst, char **rest, char *p);
void		append_char(char **s, char c);
void		expand_dolleeques(char **dst, char **rest, char *p);
void		append_num(char **dst, unsigned int num);
void		expand_specialparam(t_token *token);
void		remake_token(t_token *token, t_token *re_token);
void		expand_quote(t_token *token);
char		*expand_args_quote(char *args, char *args_free);
char		*expand_args_doller(char *args, char *args_free);
t_redirect	*expand_redirect_ten(t_redirect *redirect);
void		append_single(char **args, char **new);
void		append_double(char **args, char **new, char *args_dummy);

/************* signal handler ************/

void		sigint_handler();

/************* execfunction ************/

int			exec(t_node *node);
void		exec_check(t_node *node, char *path);
int			do_builtin(char *line, t_command *command);
int			abusolute_path(char *line);
void		ready_redirectionfile(t_node *node);
int			redirect_reconect(t_command *command);
void		prepare_pipe(t_node *node);
void		prepare_pipe_child(t_node *node);
void		prepare_pipe_parent(t_node *node);
int			wait_pipeline(pid_t last_pid);
char		**args_to_argv(t_token *args);
char		*searchpath(const char *filename);
char		*accessok_file(char *path);
int			stashfd(int fd);

/************* role checker ************/

bool		is_blank(char c);
bool		is_metacharactert(char c);
bool		is_operator(const char *s);
bool		is_redirect(const char *s);
bool		is_word(const char *s);

/**************** utils ****************/

void		ft_putstr_fd(char *s, int fd);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
size_t		ft_strlen(const char *string_row);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		ft_bzero(void *s, size_t n);

/************* errorhandle *************/

void		fatal_error(const char *msg) __attribute__((noreturn));
void		free_token(t_token *head);
pid_t		exec_pipeline(t_node *node);
void		env_init(t_map **env);
bool		startswith(const char *s, const char *keyword);

#endif
