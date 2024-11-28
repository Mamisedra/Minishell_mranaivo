/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_code.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 10:15:17 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/25 15:47:00 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	free_token(t_token **tkn)
{
	t_token	*current;
	t_token	*next;

	if (!tkn || !*tkn)
		return ;
	current = *tkn;
	while (current)
	{
		next = current->next;
		free(current->token);
		free(current);
		current = next;
	}
	current = NULL;
}

void	free_shell(t_shell **shell)
{
	t_shell	*current;
	t_shell	*next;

	if (!shell || !*shell)
		return ;
	current = *shell;
	while (current)
	{
		next = current->next;
		free(current->lexer);
		free_token(&current->token);
		ft_lstclear(&current->f_in, free);
		ft_lstclear(&current->f_out, free);
		free(current);
		current = next;
	}
	unlink("./heredoc/.Heredoc");
	*shell = NULL;
}
