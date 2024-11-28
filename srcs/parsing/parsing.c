/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 12:25:14 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/25 12:59:15 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	ft_strlen_delim(char *str, char *delim)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		ft_esquive_quote(&str[i], &i);
		if (ft_strdelim_p(delim, str[i]))
			break ;
		i++;
	}
	return (i);
}

char	*ft_delimiter(char *str, int *i, char c)
{
	char	*token;
	int		len;
	int		j;

	len = 0;
	while (str[len] == c && str[len] != '\0')
	{
		if (c == '|' && len == 1)
			break ;
		else if (len == 2)
			break ;
		len++;
	}
	token = malloc(sizeof(char) * len + 1);
	if (!token)
		return (NULL);
	j = 0;
	while (j < len)
	{
		token[j] = str[j];
		j++;
	}
	*i += len;
	token[j] = '\0';
	return (token);
}

void	tokenisation(char *str, t_list **lst)
{
	int		i;
	int		len;
	char	*lex;

	i = 0;
	while (str[i] != '\0')
	{
		ft_esquive_space(&str[i], &i);
		len = ft_strlen_delim(&str[i], "|<\t >");
		lex = ft_strndup(&str[i], len);
		if (!lex)
			return ;
		if (lex[0] != '\0')
			ft_lstadd_back(lst, ft_lstnew(ft_strdup(lex)));
		free(lex);
		i += len;
		ft_esquive_space(&str[i], &i);
		if (ft_strdelim_p("|><", str[i]))
		{
			lex = ft_delimiter(&str[i], &i, str[i]);
			if (!lex)
				return ;
			ft_lstadd_back(lst, ft_lstnew(ft_strdup(lex)));
			free(lex);
		}
		ft_esquive_space(&str[i], &i);
	}
}

int	parsing(char *str, t_shell **shell, t_env *env)
{
	t_list	*lst;
	t_list	*head;
	t_list	*heredoc;
	int		err;

	lst = NULL;
	heredoc = NULL;
	if (check_quote_unclose(str))
		return (1);
	tokenisation(str, &lst);
	err = check_syntax(lst, env,  &heredoc);
	if (err == 1)
		return (ft_lstclear(&heredoc, free), 1);
	prompt_lexer(str, shell);
	err = close_pipe(str, *shell, env, &heredoc);
	if (err == 1)
		return (ft_lstclear(&heredoc, free), 1);
	if (!shell || !*shell)
		return (ft_lstclear(&heredoc, free), 1);
	_expand_shell(shell, env);
	loop_token(shell);
	head = heredoc;
	_complete_shell(shell, &heredoc);
	ft_lstclear(&head, free);
	return (0);
}
