/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 11:18:26 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/10 14:37:15 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int	lexer_is_all_space(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i] != '\0')
	{
		if (!ft_isspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	prompt_lexer(char *str, t_shell **shell)
{
	int		i;
	int		len;
	char	*lexer;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		len = ft_strlen_chr(&str[i], '|');
		lexer = ft_strndup(&str[i], len);
		if (!lexer)
			return ;
		if (!lexer_is_all_space(lexer))
			shell_add_back_p(shell, new_shell_list_p(lexer, 1));
		i += len;
		if (str[i] == '|')
			i++;
		free(lexer);
	}
}

void	token_complete(t_shell *shell)
{
	int	i;
	int	id;

	i = 0;
	id = 1;
	while (shell->lexer[i] != '\0')
	{
		ft_esquive_space(&shell->lexer[i], &i);
		if (shell->lexer[i] == '\0')
			break ;
		if (!ft_strdelim_p("<>", shell->lexer[i]))
			add_token(&shell->token, &shell->lexer[i], &i, id++);
		else if (ft_strdelim_p("><", shell->lexer[i]))
			add_delimiter(&shell->token, &shell->lexer[i], &i, id++);
	}
}

void	loop_token(t_shell **shell)
{
	t_shell	*curr;
	t_shell	*top;

	curr = *shell;
	top = *shell;
	while (curr)
	{
		token_complete(curr);
		curr = curr->next;
	}
	*shell = top;
}
