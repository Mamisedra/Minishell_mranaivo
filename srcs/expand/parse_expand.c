/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:20:12 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/09 09:33:55 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expand.h"

static void	add_exp(t_exp **exp, char *str, int *i)
{
	char	*cmd;
	int		iter;

	iter = 0;
	cmd = ft_strtok_p(str, &iter, "<>\t \n");
	if (!cmd)
		return ;
	ft_exp_back(exp, ft_exp_new(cmd));
	(*i) += iter;
}

static void	add_delim_exp(t_exp **exp, char *str, int *i)
{
	char	*cmd;
	int		iter;

	iter = 0;
	cmd = ft_delimtok_p(str, &iter, "<>");
	if (!cmd)
		return ;
	ft_exp_back(exp, ft_exp_new(cmd));
	(*i) += iter;
}

static void	_exp_strcpy(char **dest, char *src, int *i)
{
	int	j;

	j = 0;
	while (src[j] != '\0')
	{
		(*dest)[*i] = src[j];
		(*i)++;
		j++; 
	}
}

char	*_restore_prompt(t_exp	*exp)
{
	int		len;
	int		i;
	char	*prmpt;

	len = ft_exp_len(exp);
	prmpt = malloc(sizeof(char) * (len + 1));
	if (!prmpt)
		return (NULL);
	i = 0;
	while (exp)
	{
		_exp_strcpy(&prmpt, exp->token, &i);
		prmpt[i] = ' ';
		i++;
		exp = exp->next;
	}
	prmpt[i] = '\0';
	return (prmpt);
}

void	_expand_(char *str, t_exp **exp)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_esquive_space(&str[i], &i);
		if (str[i] == '\0')
			break ;
		if (!ft_strdelim_p("<>", str[i]))
			add_exp(exp, &str[i], &i);
		else if (ft_strdelim_p("><", str[i]))
			add_delim_exp(exp, &str[i], &i);
	}
}