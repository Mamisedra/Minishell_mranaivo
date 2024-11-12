/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:57:35 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/09 09:33:40 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expand.h"

t_exp	*ft_exp_new(char *content)
{
	t_exp	*newv;

	newv = malloc(sizeof(t_exp));
	if (!newv)
		return (NULL);
	newv->token = content;
	newv->quote = check_quote(content);
	newv->next = NULL;
	return (newv);
}

t_exp	*ft_exp_last(t_exp *exp)
{
	if (exp)
	{
		while (exp)
		{
			if (exp->next == NULL)
				return (exp);
			exp = exp->next;
		}
	}
	return (exp);
}

void	ft_exp_clear(t_exp **exp)
{
	t_exp	*tmp;

	if (exp)
	{
		while (*exp)
		{
			tmp = (*exp)->next;
			free((*exp)->token);
			free(*exp);
			*exp = tmp;
		}
	}
}

void	ft_exp_back(t_exp **exp, t_exp *newv)
{
	t_exp	*tmp;

	if (exp)
	{
		if (*exp == NULL)
			*exp = newv;
		else
		{
			tmp = ft_exp_last(*exp);
			tmp->next = newv;
		}
	}
}

int	ft_exp_len(t_exp *exp)
{
	int	len;

	len = 0;
	while (exp)
	{
		len += ft_strlen(exp->token);
		len++;
		exp = exp->next;
	}
	return (len);
}