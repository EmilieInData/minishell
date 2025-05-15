CC = gcc

NAME = minishell

HEADER_NAME = inc/minishell.h inc/structure.h inc/builtins.h inc/execution.h

LIB_DIR = libft

LIBFT = libft.a

CFLAGS = -Wall -Wextra -Werror

HEADER_DIR = inc/

INCLUDES = -I $(HEADER_DIR)

LIB_READ = -lreadline

SRC = 	minishell.c \
		src/read_prompt.c\
		src/read_prompt_utils.c\
		src/utils2.c\
		src/parser.c\
		src/tokenize.c\
		src/tokenize_utils.c\
		src/expander.c\
		src/expander_utils.c\
		src/expander_checker.c\
		src/add_expand_tokens.c\
		src/verify_tokens.c\
		src/sections.c\
		src/sections_utils.c\
		src/signals.c\
		src/signals_exe.c\
		src/signals_heredoc.c\
		builtins/maths.c \
		builtins/utils.c \
		builtins/builtins.c \
		builtins/env_manage.c \
		builtins/env_array.c \
		builtins/builtins_cd.c \
		builtins/builtins_cd_utils.c \
		builtins/builtins_env.c \
		builtins/builtins_export.c \
		builtins/builtins_export_utils.c \
		execution/exe_errors.c \
		execution/exe_files.c \
		execution/exe_path.c \
		execution/exe_section_utils.c \
		execution/exe_split.c \
		execution/exe_utils.c \
		execution/execution.c

OBJS = src/$(SRC:.c=.o)

DEPS = src/$(SRC:.c=.d)

all:
	$(MAKE) -C $(LIB_DIR)
	$(MAKE) $(NAME)
	
$(NAME): $(OBJS) libft/$(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LIB_READ) libft/$(LIBFT) -o $@

%.o: %.c Makefile libft/$(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

-include $(DEPS) 

clean:
	rm -f $(OBJS) $(DEPS)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean r
