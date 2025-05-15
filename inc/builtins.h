/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:05:00 by esellier         #+#    #+#             */
/*   Updated: 2024/09/12 16:20:15 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "minishell.h"

//builtins
int		make_builtins(char **str, t_data *data, int flag);
int		exit_number(char **str, t_data *data);
int		make_exit(char **str, t_data *data);
int		check_echo(char **str, int i);
void	make_echo(char **str);

//builtins_env
t_env	*adjust_env(t_data *data, t_env *to_del);
void	make_unset(char **str, t_data *data);
int		make_env(t_data *data, char **str);
void	change_cd_data(t_data *data, char *new);

//builtins_export_utils
char	*check_value(t_data *data, int j, char *name);
int		first_check(char *str);
void	change_value(t_env *current, char *value, char *name);
int		check_name(char *str, int i, t_env *current, t_data *data);
int		check_args(char *str);

//builtins_export
void	p_exp_loop(t_env *to_print, t_env *old, t_env *cur, t_env *env_lst);
void	print_export(t_env *env_lst);
void	export_malloc(char **str, int i, t_env *current, t_data *data);
int		make_export(char **str, t_data *data);
int		make_pwd(t_data *data);

//builtins_cd
void	ft_free_cd(t_data *data, char *old, char *new, int i);
int		change_pwd(t_data *data, char *old, char *new, char **str);
int		cd_home(char **str, t_data *data, char *old_buf, char *new_buf);
int		make_cd(char **str, t_data *data);

//builtins_cd_utils
void	write_errors_cd(char **str, char *arg);
int		check_dir_cd(char **str);

//maths
int		modulo_negativ(int a);
int		check_num(char *str);
int		check_minmax(char *str);
int		strncmp_long(const char *s1, const char *s2);
int		count_lst(t_env *lst);

//env
t_env	*create_flag(t_env *new_node);
t_env	*env_new(char *str, t_env *new_node);
t_env	*create_env(char **env, t_data *data);
int		exp_new(char *str, t_env *new_node);
int		create_value(t_env *new_node, int i, int j, char *str);

//env_array
char	**copy_env(t_data *data, char **array, t_env *env);
char	**env_array(t_data *data, char **array);
t_env	*search_str(char *str, t_data *data);

//utils
int		ft_strcmp(char *s1, char *s2);
int		print_errors(char **str, t_data *data, int i);
void	ft_malloc(t_data *data, char **array, t_env *lst);
void	free_array(char **arr);
void	erase_lst(t_env *lst);

#endif
