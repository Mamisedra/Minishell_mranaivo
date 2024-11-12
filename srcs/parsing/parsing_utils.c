/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:15:10 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/12 14:15:55 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	check_quote_unclose(char *str)
{
	int		i;
	char	quote;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				i++;
			if (str[i] != quote)
			{
				print_error(1, "");
				return (1);
			}
		}
		if (str[i] == '\0')
			break ;
		i++;
	}
	return (0);
}

int	ft_strlen_quote(char *str)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			while (str[++i] == '\'')
				len++;
		}
		if (str[i] == '\"')
		{
			while (str[++i] == '\"')
				len++;
		}
		if (str[i] != '\'' && str[i] != '"')
		{
			i++;
			len++;
		}
	}
	return (len);
}

char	*ft_strtok_p(char *str, int *i, char *delim)
{
	int		len;
	char	*tkn;

	len = 0;
	while (!ft_strdelim_p(delim, str[len]) && str[len] != '\0')
	{
		ft_esquive_quote(&str[len], &len);
		len++;
	}
	tkn = ft_strndup(str, len);
	if (!tkn)
		return (NULL);
	*i += len;
	return (tkn);
}

char	*ft_delimtok_p(char *str, int *i, char *delim)
{
	char	*tkn;
	int		len;
	char	c;

	len = 0;
	c = '\0';
	if (ft_strdelim_p(delim, str[len]))
	{
		c = str[len];
		len++;
	}
	while (str[len] == c)
		len++;
	tkn = ft_strndup(str, len);
	if (!tkn)
		return (NULL);
	*i += len;
	return (tkn);
}

int	check_quote(char *str)
{
	char	quote;
	int		len;

	len = 0;
	len = ft_strlen(str) - 1;
	quote = str[0];
	if (quote == '\'' || quote == '"')
	{
		if (str[0] == str[len])
		{
			if (str[0] == '\'')
				return (1);
			else if (str[0] == '"')
				return (2);
		}
	}
	return (0);
}
