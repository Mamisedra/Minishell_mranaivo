/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redir_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:59:22 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/21 11:20:19 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execute.h"

static t_redir	*__last_redir(t_redir *redir)
{
	if (redir)
	{
		while (redir)
		{
			if (redir->next == NULL)
				return (redir);
			redir =redir->next;
		}
	}
	return (redir);
}

static void	__back_redir(t_redir **redir, t_redir *red)
{
	t_redir *tmp;

	if (redir)
	{
		if (*redir == NULL)
			*redir = red;
		else
		{
			tmp = __last_redir(*redir);
			tmp->next = red;
		}
	}
}

static t_redir *__new_redir(char *str, t_s_redir state)
{
	t_redir	*new_red;

	new_red = malloc(sizeof(t_redir));
	if (!new_red)
		return (NULL);
	new_red->str = ft_strdup(str);
	new_red->state = state;
	new_red->next = NULL;
	return (new_red);
}

void	get_redir(t_redir **redir, t_token *token)
{
	while (token)
	{
		if (token->state == FILE_NAME || token->state == FILE_NAME_I)
			__back_redir(redir, __new_redir(token->token, INPUT));
		else if (token->state == FILE_NAME_O)
			__back_redir(redir, __new_redir(token->token, OUTPUT));
		token = token->next;
	}
}

void	__redir_clear(t_redir **redir)
{
	t_redir *curr;
	t_redir *next_node;

	if (!redir)
		return ;
	curr = *redir;
	while (curr)
	{
		next_node = curr->next;
		free(curr->str);
		free(curr);
		curr = next_node;
	}
	curr = NULL;
}