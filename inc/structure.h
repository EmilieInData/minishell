/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:05:00 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/22 18:37:00 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

//Libraries
# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <dirent.h>
# include <sys/stat.h>

//Global
extern int	g_signal_num;

//Errors msn
# define NO_ARGS "Error. Execution don't allow arguments\n"
# define NO_GETCWD "getcwd() error, can't read current path directory\n"
# define EXIT "exit\n"
# define ERR_SQUOTE ">\nError while looking for matching `''\n"
# define ERR_DQUOTE ">\nError while looking for matching `\"\'\n"
# define ERR_PIPE "bash: syntax error near unexpected token `|'\n"
# define ERR_SEMICOL "bash: syntax error near unexpected token `;'\n"
# define ERR_BACKSLASH "bash: syntax error near unexpected token `\\'\n"
# define ERR_DELIM "bash: syntax error near unexpected token `newline'\n"
# define ERR_INPUT "bash: syntax error near unexpected token `<'\n"
# define ERR_TRUNC "bash: syntax error near unexpected token `>'\n"
# define ERR_HEREDOC "bash: syntax error near unexpected token `<<'\n"
# define ERR_APPEND "bash: syntax error near unexpected token `>>'\n"
# define MAX_HEREDOC "bash: maximum here-document count exceeded\n"

# define MAX_TOKENS 580000

//delimiters
# define BACKSLASH -2 // '\'
# define SEMICOL -1 // ;
# define CMD 0 // command for expansion variables
# define SPACES 1 //Spaces and tabs
# define PIPE 2 // |
# define INPUT 3 // <
# define TRUNC 4 // >
# define SQUOTE 5 // '
# define DQUOTE 6 // "
# define HEREDOC 7 // <<
# define APPEND 8 // >>
# define END 9
# define ARG 10 // string or argument
# define VAR 11 //Variable $
# define NOEXP 12 //Delim no expand on heredoc

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
	char				flag;
	int					print;
}						t_env;

typedef struct s_tokens
{
	char				*value;
	int					type;
}						t_tokens;

typedef struct s_red
{
	char				*file;
	int					redi;
	struct s_red		*next;
}						t_red;

typedef struct s_section
{
	char				**cmd;
	t_red				*files;
	char				**path_array;
	char				*path;
	int					flag;
	int					pid;
	int					fd_in;
	int					fd_out;
	int					tokens_qt;
	struct s_section	*next;
}						t_section;

typedef struct s_data
{
	char				*prompt;
	t_tokens			**tokens;
	t_section			*sections;
	int					tokens_qt;
	int					sections_qt;
	int					rt_value;
	t_env				*env_lst;
	char				*current_dir;
}						t_data;

#endif