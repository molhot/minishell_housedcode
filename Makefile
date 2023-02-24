NAME	=	minishell
SRCS	=	tokenizer/tokenizer.c tokenizer/error.c tokenizer/create_token.c\
			tokenizer/make_op_token.c tokenizer/make_redirect_token.c tokenizer/make_wd_token.c\
			syntax_check/syntax_check.c\
			parser/parser.c parser/parse_word.c parser/parse_redirect.c parser/parser_utils.c\
			expand/expand.c expand/expand_doller.c expand/expand_appendchar.c expand/expand_specialchar.c\
			expand/expand_simplecommand.c expand/expand_redirection.c\
			exec_func/exec_func.c exec_func/exec_builtin.c exec_func/pipe_func.c exec_func/redirect_file.c\
			exec_func/exec_absolutepath.c exec_func/exec_utils.c\
			word_rolechecker/is_blank.c word_rolechecker/is_metacharacter.c\
			word_rolechecker/is_operator.c word_rolechecker/is_redirect.c word_rolechecker/is_word.c\
			utils/split.c utils/putstr_fd.c utils/strlcat.c utils/strlcpy.c utils/strlen.c\
			utils/strtrim.c utils/putchar_fd.c utils/strchr.c utils/strdup.c\
			utils/strjoin.c utils/strcmp.c utils/strncmp.c utils/memcmp.c utils/calloc.c utils/bzero.c\
			builtin_command/builtin_cd.c builtin_command/builtin_echo.c builtin_command/builtin_env.c\
			builtin_command/builtin_exit.c builtin_command/builtin_export.c builtin_command/builtin_pwd.c\
			builtin_command/builtin_unset.c builtin_command/command_to_array.c builtin_command/builtin_ch.c\
			signalhandler/sigint_handler.c\
			map/map.c\
			env_ready.c main.c
OBJS	=	$(SRCS:%.c=%.o)
CC  	=	gcc
CFLAGS	=	-Wall -Werror -Wextra
RLDIR	=	$(shell brew --prefix readline)

all:$(NAME)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -Llibft -L$(RLDIR)/lib -I$(RLDIR)/include -o $(NAME) -lreadline -lft

$(OBJS): %.o : %.c
	$(CC) $(CFLAGS) -I$(RLDIR)/include -c  $< -o $@ 

debug:$(OBJS)
	$(CC) $(CFLAGS)  $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
