/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:43:56 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/01 15:44:22 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	ft_esquive_space(char *str, int *i)
{
	int	j;

	j = 0;
	while (ft_isspace(str[j]) && str[j] != '\0')
		j++;
	*i += j;
}

void	ft_esquive_quote(char *str, int *i)
{
	char	c;
	int		j;

	c = str[0];
	j = 1;
	if (c != '\'' && c != '"')
		return ;
	while (str[j] != c)
		j++;
	(*i) += j;
}

int	ft_strlen_chr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		ft_esquive_quote(&str[i], &i);
		if (str[i] != '\0')
			i++;
	}
	return (i);
}

bool	ft_strdelim_p(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (true);
		i++;
	}
	return (false);
}

char	*ft_strcatquote(char *str)
{
	char	*cmd;
	char	quote;
	int		len;
	int		i;

	len = ft_strlen_quote(str);
	if (len < 0)
		return (NULL);
	cmd = malloc(sizeof(char) * (len + 1));
	if (!cmd)
		return (NULL);
	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] != quote && str[i] != '\0')
				cmd[len++] = str[i++];
			i++;
		}
		else
			cmd[len++] = str[i++];
	}
	cmd[len] = '\0';
	return (cmd);
}
