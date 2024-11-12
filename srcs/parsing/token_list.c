/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:19:37 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/10 14:09:42 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"
#include <stdbool.h>

t_token	*new_token_list_p(char *str, int i)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->id = i;
	new_token->quote = check_quote(str);
	new_token->token = ft_strcatquote(str);
	new_token->next = NULL;
	return (new_token);
}

t_token	*tokenlast_p(t_token *token)
{
	if (token)
	{
		while (token)
		{
			if (token->next == NULL)
				return (token);
			token = token->next;
		}
	}
	return (token);
}

void	token_add_back_p(t_token **token, t_token *new_token)
{
	t_token	*current;

	if (!token || !new_token)
		return ;
	new_token->next = NULL;
	if (*token == NULL)
		*token = new_token;
	else
	{
		current = tokenlast_p(*token);
		current->next = new_token;
	}
}

void	add_token(t_token **token, char *str, int *i, int id)
{
	char	*cmd;
	int		iter;

	iter = 0;
	cmd = ft_strtok_p(str, &iter, "<>\t \n");
	if (!cmd)
		return ;
	token_add_back_p(token, new_token_list_p(cmd, id));
	(*i) += iter;
	free(cmd);
}

void	add_delimiter(t_token **token, char *str, int *i, int id)
{
	char	*cmd;
	int		iter;

	iter = 0;
	cmd = ft_delimtok_p(str, &iter, "<>");
	if (!cmd)
		return ;
	token_add_back_p(token, new_token_list_p(cmd, id));
	(*i) += iter;
	free(cmd);
}
