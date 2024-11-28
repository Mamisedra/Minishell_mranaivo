/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:27:18 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/25 11:59:19 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_shell	*new_shell_list_p(char *str, int i)
{
	t_shell	*new_shell;

	new_shell = malloc(sizeof(t_shell));
	if (!new_shell)
		return (NULL);
	new_shell->id = i;
	new_shell->lexer = ft_strdup(str);
	new_shell->token = NULL;
	new_shell->f_in = NULL;
	new_shell->f_out = NULL;
	new_shell->next = NULL;
	return (new_shell);
}

t_shell	*shelllast_p(t_shell *shell)
{
	if (shell)
	{
		while (shell)
		{
			if (shell->next == NULL)
				return (shell);
			shell = shell->next;
		}
	}
	return (shell);
}

void	shell_add_back_p(t_shell **shell, t_shell *new_shell)
{
	t_shell	*current;

	if (!shell || !new_shell)
		return ;
	new_shell->next = NULL;
	if (*shell == NULL)
		*shell = new_shell;
	else
	{
		current = shelllast_p(*shell);
		current->next = new_shell;
	}
}

void	_complete_shell(t_shell **shell, t_list **hdoc)
{
	int		i;
	t_shell	*current;
	t_shell	*top;

	i = 1;
	current = *shell;
	top = *shell;
	while (current)
	{
		current->id = i;
		current->in = ft_flags_in(current);
		current->out = ft_flags_out(current);
		_token_state(&current->token, hdoc);
		_input_output_file(current);
		i++;
		current = current->next;
	}
	*shell = top;
}

void	_input_output_file(t_shell *shell)
{
	t_token	*token;

	token = shell->token;
	if (shell->in != FILE_IN && shell->out != FILE_OUT)
		return ;
	while (token)
	{
		if (token->state == FILE_NAME_O)
			ft_lstadd_back(&shell->f_out, ft_lstnew(ft_strdup(token->token)));
		else if (token->state == FILE_NAME || token->state == FILE_NAME_I)
			ft_lstadd_back(&shell->f_in, ft_lstnew(ft_strdup(token->token)));
		token = token->next;
	}
}
