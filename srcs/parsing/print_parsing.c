/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:49:43 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/10 14:14:07 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

void	print_state_token(t_token *token)
{
	printf("state : ");
	if (token->state == COMMANDE)
		printf("COMMANDE");
	else if (token->state == ARGUMENT)
		printf("ARGUMENT");
	else if (token->state == HEREDOC)
		printf("HEREDOC");
	else if (token->state == FILE_NAME)
		printf("FILE_NAME");
	else if (token->state == IN_FILE)
		printf("IN_FILE");
	else if (token->state == OUT_FILE)
		printf("OUT_FILE");
	else if (token->state == APPEND)
		printf("APPEND");
	else if (token->state == FILE_NAME_I)
		printf("FILE_NAME_I");
	else if (token->state)
		printf("FILE_NAME_O");
	printf("\n");
}

void	print_token(t_token *token)
{
	t_token	*curr;

	curr = token;
	printf("\t=======TOKEN=======\n");
	while (curr)
	{
		printf("\tId : %d\t", curr->id);
		printf("Token : %s\t", curr->token);
		print_state_token(curr);
		curr = curr->next;
	}
}

void	print_state(t_shell *shell)
{
	printf("IN : ");
	if (shell->in == STD_IN)
		printf("STD_IN");
	else if (shell->in == PIPE_IN)
		printf("PIPE_IN");
	else if (shell->in == FILE_IN)
		printf("FILE_IN");
	printf("\tOUT : ");
	if (shell->out == STD_OUT)
		printf("STD_OUT");
	else if (shell->out == PIPE_OUT)
		printf("PIPE_OUT");
	else if (shell->out == FILE_OUT)
		printf("FILE_OUT");
	printf("\n");
}

void	print_shell(t_shell *shell)
{
	t_shell	*curr;

	curr = shell;
	while (curr)
	{
		printf("Id : %d\t\t", curr->id);
		printf("Lexer : %s\t", curr->lexer);
		print_state(curr);
		print_token(curr->token);
		curr = curr->next;
	}
}

void	print_list(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		printf("Token[%d] = '%s'\n", i, lst->content);
		i++;
		lst = lst->next;
	}
}
