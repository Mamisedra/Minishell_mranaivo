/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   code_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:02:43 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/25 12:53:08 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_input	ft_flags_in(t_shell *current)
{
	int		i;
	t_input	flag;

	i = 0;
	flag = STD_IN;
	if (current->id != 1)
		flag = PIPE_IN;
	while (current->lexer[i] != '\0')
	{
		ft_esquive_quote(&current->lexer[i], &i);
		if (current->lexer[i] == '<')
			flag = FILE_IN;
		i++;
	}
	return (flag);
}

t_output	ft_flags_out(t_shell *current)
{
	int			i;
	t_output	flag;

	i = 0;
	flag = STD_OUT;
	if (current->next != NULL)
		flag = PIPE_OUT;
	while (current->lexer[i] != '\0')
	{
		ft_esquive_quote(&current->lexer[i], &i);
		if (current->lexer[i] == '>')
			flag = FILE_OUT;
		i++;
	}
	return (flag);
}

static int	_compare_token(char *token, bool state)
{
	if (!ft_strcmp(token, "<") && !state)
		return (1);
	if (!ft_strcmp(token, ">") && !state)
		return (2);
	if (!ft_strcmp(token, ">>") && !state)
		return (3);
	if (!ft_strcmp(token, "<<") && !state)
		return (4);
	return (0);
}

static void	_set_parms(t_token **curr, int stat)
{
	if (stat == 1)
	{
		(*curr)->state = IN_FILE;
		if ((*curr)->next != NULL)
			(*curr)->next->state = FILE_NAME_I;
	}
	else if (stat == 2)
	{
		(*curr)->state = OUT_FILE;
		if ((*curr)->next != NULL)
			(*curr)->next->state = FILE_NAME_O;
	}
	else if (stat == 3)
	{
		(*curr)->state = APPEND;
		if ((*curr)->next != NULL)
			(*curr)->next->state = FILE_NAME_O;
	}
	else if (stat == 4)
	{
		(*curr)->state = HEREDOC;
		if ((*curr)->next != NULL)
			(*curr)->next->state = FILE_NAME;
	}
	*curr = (*curr)->next;
}

void	_token_state(t_token **token, t_list **hdoc)
{
	t_token	*curr;
	t_token	*top;
	bool	cmd;

	curr = *token;
	top = *token;
	cmd = false;
	while (curr)
	{
		if (curr->id == 1 && !_compare_token(curr->token, curr->quote))
		{
			curr->state = COMMANDE;
			cmd = true;
		}
		else if (_compare_token(curr->token, curr->quote))
			_set_parms(&curr, _compare_token(curr->token, curr->quote));
		else if (!cmd)
		{
			curr->state = COMMANDE;
			cmd = true;
		}
		else
			curr->state = ARGUMENT;
		if (curr->state == FILE_NAME)
		{
			free(curr->token);
			curr->token = ft_strdup((*hdoc)->content);
			if ((*hdoc)->next)
				(*hdoc) = (*hdoc)->next;
		}
		if (curr != NULL)
			curr = curr->next;
	}
	*token = top;
}
