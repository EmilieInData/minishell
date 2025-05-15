/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esellier <esellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 18:44:22 by mirifern          #+#    #+#             */
/*   Updated: 2024/10/09 17:50:31 by esellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*Function to find > >> < o << in prompt*/
int	find_others(char *input)
{
	int	len;

	len = ft_strlen(input) - 1;
	if (input[len] == '<' || input[len] == '>')
	{
		ft_msn(ERR_DELIM, 2);
		return (1);
	}
	return (0);
}

/*Function to find some spaces or tabs characters inside the string*/
int	only_spaces(char *s)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (s[i] != '\0')
	{
		if (ft_isspace(s[i]))
			check++;
		i++;
	}
	if (i == check)
		return (1);
	return (0);
}

/* Function is calling other functions like expander, to find not allowed types 
like \ and ;, organize tokens if END_token appears, join tokens if 2 or more
ARG tokens are together, and finaly verify all the tokens. If something is wrong
return 1 still main o not excecute*/
int	token_expand_clean(t_data *data)
{
	if (ft_tokenizer(data, ft_strlen(data->prompt), 0, 0) == 1)
		return (1);
	if (ft_expander(data) == 1)
		return (1);
	if (find_not_allowed_type(data) == 1)
		return (1);
	delete_token_type(data, END);
	join_tokens(data, 0, 0);
	delete_token_type(data, SPACES);
	if (verify_num_heredoc(data) == 1 || verify_next_type(data) == 1)
		return (1);
	return (0);
}

/*
1 - Read input prompt
2 - If an EOF (ctr+d) is detected, make exit and return -1 to break while(1)
in main function, free the structure and close minishell
3 - Trim prompt to delete spaces after and before input
4 - If prompt exist but it's empty return 1 to main to make a new prompt and
free the structure
5 - If everything it's ok, add input to history
6 - Check prompt by parser if something is wrong and parser returns 1, return
back 1 to main to not execute and prepare new prompt. Error msn should be write
7 - Start tokenizer, expander and prepare the token structure to separete into
sections if it's necessary. if something is wrong and parser returns 1, return
back 1 to main to not execute and prepare new prompt. Error msn should be write
*/
int	ft_read_prompt(t_data *data)
{
	data->prompt = readline("\033[1;34m👯 minishell> \033[0m");
	if (!data->prompt)
		return (ft_msn(EXIT, 2), -1);
	trim_prompt(data);
	if (data->prompt && !data->prompt[0])
		return (1);
	else if (data->prompt[0])
		add_history(data->prompt);
	if (ft_parser(data) == 1 || token_expand_clean(data) == 1)
		return (1);
	ft_sections(data);
	return (0);
}
