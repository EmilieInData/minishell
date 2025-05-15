/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 21:57:37 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/01 12:39:45 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*allocate_result_buffer(t_data *data)
{
	char	*result;

	result = malloc(sizeof(char) * 10240);
	if (!result)
		ft_malloc(data, NULL, NULL);
	return (result);
}

/* Function that assigns the return value when it receives the variable $?
It is returned as a string by passing the int rt_value through
 the ft_itoa function */
void	handle_rt_value(t_data *data, char **temp, char **res)
{
	char	*var_value;
	char	*original_var_value;

	(*temp)++;
	if (g_signal_num != 0)
		var_value = ft_itoa(g_signal_num);
	else
		var_value = ft_itoa(data->rt_value);
	original_var_value = var_value;
	while (*var_value != '\0')
		*(*res)++ = *var_value++;
	g_signal_num = 0;
	free(original_var_value);
}

void	handle_digit_variable(char **temp, char **res)
{
	if (**temp == '0')
	{
		*(*res)++ = 'b';
		*(*res)++ = 'a';
		*(*res)++ = 's';
		*(*res)++ = 'h';
	}
	(*temp)++;
	while (ft_isdigit(**temp))
		*(*res)++ = *(*temp)++;
}

void	handle_normal_variable(t_data *data, char **temp, char **res)
{
	char	var_name[128];
	char	*var_value;
	int		i;

	i = 0;
	ft_memset(var_name, 0, sizeof(var_name));
	while (**temp != '\0' && (ft_isalnum(**temp) || **temp == '_'))
		var_name[i++] = *(*temp)++;
	var_name[i] = '\0';
	var_value = expand_var(data, var_name);
	if (var_value && var_value[0])
	{
		while (*var_value != '\0')
			*(*res)++ = *var_value++;
	}
	else
		return ;
}

char	*expand_env_variables(t_data *data, char *input, char *res)
{
	char	*result;

	result = allocate_result_buffer(data);
	res = result;
	while (*input != '\0')
	{
		if (*input == '$')
		{
			input++;
			if (*input == '\0' || *input == 32)
				*res++ = '$';
			else if (*input == '?')
				handle_rt_value(data, &input, &res);
			else if (ft_isdigit(*input))
				handle_digit_variable(&input, &res);
			else
				handle_normal_variable(data, &input, &res);
		}
		else
			*res++ = *input++;
	}
	*res = '\0';
	return (result);
}
