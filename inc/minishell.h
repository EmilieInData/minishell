/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:05:00 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/22 22:10:31 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//Libraries
# include "structure.h"
# include "builtins.h"
# include "execution.h"

//Main minishell.c
void		print_sections(t_data *data);
void		do_prompt(t_data *data, int prompt);
void		print_tokens(t_data *data);
int			ft_initialize(t_data **data, char **env);
int			main(int ac, char **av, char **env);

//read_prompt.c
int			find_others(char *input);
int			only_spaces(char *s);
int			token_expand_clean(t_data *data);
void		free_for_new_prompt(t_data *data);
int			ft_read_prompt(t_data *data);

//read_prompt_utils.c
void		trim_prompt(t_data *data);
int			find_not_allowed_type(t_data *data);
int			verify_num_heredoc(t_data *data);

//parse.c
int			end_quote(char *input, char c, int i);
int			find_pipes(char *input);
int			find_pair_quote(char *input, int *i, char quote_type);
int			find_quotes(char *input, int squote, int dquote);
int			ft_parser(t_data *data);

//tokenize.c
int			end_variable(char *input, int i);
void		tok_delimiter(t_data *data, char *input, int *ind, int *start);
void		tok_nodelimiter(t_data *data, int *ind, int *start, int *end);
void		define_delimiter(t_data *data, int *start, int *end, int *index);
int			ft_tokenizer(t_data *d, int len, int start, int index);

//tokenize_utils.c
void		remove_quotes(char *str);
int			clean_quotes(t_data *d, char *res, int i, int check);
void		ft_move_tokens(t_data *data, int *i, int *j);
void		join_tokens(t_data *d, int i, int j);
void		delete_token_type(t_data *d, int type);

//utils2.c
void		ft_free(t_tokens **arr);
void		ft_free_flag(t_data *data, int flag);
void		ft_free_data(t_data *data, int flag);
int			ft_msn(char *s, int fd);
int			ft_isdelimiter(char c);

//expander.c
char		*find_var_name(char *value, int *i, t_data *data);
int			find_dollar(char *str);
char		*quit_dollar(char *value, int *i);
char		*expand_var(t_data *data, char *value);
int			ft_expander(t_data *d);

//expander_utils.c
char		*allocate_result_buffer(t_data *data);
void		handle_rt_value(t_data *data, char **temp, char **res);
void		handle_digit_variable(char **temp, char **res);
void		handle_normal_variable(t_data *data, char **temp, char **res);
char		*expand_env_variables(t_data *data, char *input, char *res);

//expander_checker.c
void		ft_add_tokens(t_data *d, char *input, int add_tokens, int pos);
int			check_var_spaces(t_data *data, char *input, int pos);
int			check_previous_null(t_data *d, int i, char *cpy);
int			check_previous_heredoc(t_data *data, int i);
int			expand_check_and_prev(t_data *d, char *cpy, char *expanded, int *i);

//add_expand_tokens.c
t_tokens	**init_new_tok(t_data *d, int add_tokens);
int			copy_tok_before(t_data *d, t_tokens **new_tokens, int pos);
int			insert_exp_tok(t_data *d, t_tokens **new, char **split_tok, int j);
int			copy_rest_tok(t_data *d, t_tokens **new_tokens, int pos, int j);
void		final_tok(t_data *d, t_tokens **new, int total, char **split_tok);

//verify_tokens.c
void		print_err(int check);
int			check_type(int type);
void		write_msn(t_data *data, char *value);
int			verify_previous_type(t_data *d, int i, char *value, int flag);
int			verify_next_type(t_data *d);

//sections.c
t_section	*create_node(t_data *data);
void		add_redir(t_section *temp_section, t_data *data, int *i);
int			ft_isredir(int type);
void		init_sections(t_data *data);
void		ft_sections(t_data *data);

//sections_utils.c
void		add_first_redir(t_section *section, t_tokens **tokens, int *i,
				t_data *data);
void		add_rest_redir(t_section *section, t_tokens **tokens, int *i,
				t_data *data);
char		**create_cmd(t_section *section, char *arg, t_data *data);
int			size_cmd(char **cmd);
char		**add_arg(t_section *section, char *arg, t_data *data);

//signals.c
void		readline_sigint_handler(int signum);
void		readline_sigquit_handler(int signum);
void		set_readline_signals(void);

//signals_exe.c
void		exe_sigquit_handler(int signum);
void		exe_sigint_handler(int signum);
void		set_execution_signals(void);

//signals_heredoc.c
void		heredoc_sigquit_handler(int signum);
void		heredoc_sigint_handler(int signum);
void		set_heredoc_signals(void);

#endif