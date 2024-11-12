/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:37:06 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/10 14:35:48 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	ft_strchr_quote(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_esquive_quote(&str[i], &i);
		if (str[i] == c)
			return (1);
		else if (str[i] != '\'' && str[i] != '"')
			i++;
	}
	return (0);
}

void	print_error(int err, char *str)
{
	if (err == 1)
		ft_putstr_fd("Quote unclose \n", 2);
	if (err == 2)
	{
		ft_putstr_fd("Minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("'\n", 2);
	}
	if (err == 3)
		ft_putstr_fd("Minishell: syntax error near unexpected token `newline'\n", 2);
}

bool	is_pipe(char *str)
{
	if (ft_strcmp(str, "|") == 0)
		return (true);
	return (false);
}

bool	is_heredoc(char *str)
{
	if (ft_strcmp(str, "<<") == 0)
		return (true);
	return (false);
}

bool	is_token(char *str, int pipe)
{
	if (ft_strcmp(str, ">") == 0)
		return (true);
	if (ft_strcmp(str, ">>") == 0)
		return (true);
	if (ft_strcmp(str, "<") == 0)
		return (true);
	if (pipe)
	{
		if (ft_strcmp(str, "|") == 0)
			return (true);
	}
	return (false);
}
