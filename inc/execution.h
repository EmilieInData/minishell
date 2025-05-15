/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:05:00 by esellier          #+#    #+#             */
/*   Updated: 2024/10/22 22:04:29 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include "minishell.h"

//split
int			count_path(char *str, char c);
int			strlen_path(char *str, char c);
char		**put_path(char **array, char *str, char c, int path);
char		**split_env(char *str, t_data *data);

//exe
int			builtins_exe(t_data *data, t_section *section);
int			classic_exe(t_data *data, t_section *section);
void		free_array_int(int **array);
int			ft_waitpid_status(t_section *section, t_data *data);
int			execution(t_data *data, t_section *section);

//exe_utils

char		*ft_strjoin_three(char const *s1, char const *s2, char const *s3);
int			check_builtins(char **str);
void		exe_builtins_redi(t_data *data, int fd_in, int fd_out);
int			fd_pipe(t_data *data);
int			fd_null(t_data *data, t_section *section, int fd);

//exe_files
void		do_heredoc(int *fd, char *del);
int			ft_heredoc(t_data *data, char *del);
int			create_file(char *file, int i, t_data *data, int fd);
int			check_files(t_data *data, t_section *current, t_red *red);

//path
int			search_path(t_data *data, char **array, t_section *section);
char		*check_path(t_section *section, t_data *data, char *path_lst);
char		*find_path_cmd(char **array, int j, t_data *data, char *tmp);
char		**lst_to_arr(t_env *lst, t_data *data, char **array);
void		create_pipe(t_data *data);

//exe_section-utils
void		do_red(t_red *red, t_red *prev);
void		ft_free_section(t_section *section, t_section *previous);
void		close_fd(t_section *section);
void		close_fd_child(t_section *section);

//exe_errors
void		write_arg(char *arg);
int			check_dir(char *arg);
int			error_exe(t_data *data, char *arg, int i);
int			access_errors(char *file, t_data *data, int fd, int i);

#endif