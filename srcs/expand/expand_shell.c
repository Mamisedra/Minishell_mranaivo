/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 10:04:13 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/12 17:32:25 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expand.h"

void	print_expand(t_exp *exp)
{
	printf("\t====|CHAINE A EXPANDER|====\n");
	while (exp)
	{
		printf("str : %s\t",exp->token);
		printf("quote :%d\t",exp->quote);
		if (exp->state == NO_EXPAND)
			printf("state :%s\n", "NO_EXPAND");
		else
			printf("state :%s\n", "TO_EXPAND");
		exp = exp->next;
	}
}

static bool	cmp_delim(char *str)
{
	if (!ft_strcmp(str, "<"))
		return (true);
	if (!ft_strcmp(str, "<<"))
		return (true);
	if (!ft_strcmp(str, ">"))
		return (true);
	if (!ft_strcmp(str, ">>"))
		return (true);
	return (false);
}

void	_get_state_exp(t_exp **exp)
{
	t_exp	*current;
	t_exp	*top;

	current = *exp;
	top = *exp;
	while (current)
	{
		if (cmp_delim(current->token))
			current->state = NO_EXPAND;
		else if (current->quote == 1)
			current->state = NO_EXPAND;
		else if (ft_strchr(current->token, '$') == 0)
			current->state = NO_EXPAND;
		else
			current->state = TO_EXPAND;
		if (!ft_strcmp(current->token, "<<"))
		{
			if (current->next)
			{
				current = current->next;
				current->state = NO_EXPAND;
			}
			else
				break ;
		}
		current = current->next;
	}
	*exp = top;
}

void	_expand_shell(t_shell **shell, t_env *env)
{
	t_shell	*current;
	t_shell	*top;
	t_exp	*expand;

	current = *shell;
	top = *shell;
	expand = NULL;
	while (current)
	{
		_expand_(current->lexer, &expand);
		_get_state_exp(&expand);
		expansion(&expand, env);
		free(current->lexer);
		current->lexer = _restore_prompt(expand);
		ft_exp_clear(&expand);
		expand = NULL;
		current = current->next;
	}
	*shell = top;
}
