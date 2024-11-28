/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 13:22:53 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/25 11:48:19 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

bool	pipe_end(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[len] == '\0')
		len--;
	while (len >= 0)
	{
		while (ft_isspace(str[len]) && len != 0)
			len--;
		if (str[len] == '|')
			return (true);
		else
			break ;
	}
	return (false);
}

int	complete_pipe(t_shell *shell, t_env *env, t_list **hdoc)
{
	char	*rl;
	t_list	*lst;
	int		err;

	lst = NULL;
	rl = NULL;
	err = 0;
	while (1)
	{
		rl = readline("pipe > ");
		if (!rl)
			return (1);
		if (ft_strcmp(rl, "\0"))
		{
			if (check_quote_unclose(rl))
				return (1);
			tokenisation(rl, &lst);
			err = check_syntax(lst, env, hdoc);
			if (err == 1)
				return (free(rl), 1);
			prompt_lexer(rl, &shell);
			if (err != 2)
				break ;
			err = 0;
			lst = NULL;
		}
		free(rl);
	}
	return (free(rl), err);
}

int	close_pipe(char *str, t_shell *shell, t_env *env, t_list **hdoc)
{
	if (!pipe_end(str))
		return (0);
	else
		return (complete_pipe(shell, env, hdoc));
}
