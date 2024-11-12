/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 16:22:42 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/10 14:18:54 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static char	*heredoc(char *str)
{
	char	*content;
	char	*prompt;
	char	*ret;

	content = NULL;
	ret = NULL;
	while (1)
	{
		prompt = readline("heredoc > ");
		if (!prompt)
			return (NULL);
		if (!ft_strcmp(str, prompt))
		{
			free(prompt);
			break ;
		}
		prompt = ft_strjoin(prompt, "\n");
		content = ft_strjoin(ret, prompt);
		if (!content)
		{
			free(prompt);
			return (NULL);
		}
		free(prompt);
		free(ret);
		ret = ft_strdup(content);
		free(content);
	}
	return (ret);
}

void	capture_heredoc(char *str)
{
	char	*eof;
	char	*here;

	eof = ft_strcatquote(str);
	if (!eof)
		return ;
	here = heredoc(eof);
	free(eof);
	if (!here)
		return ;
	copy_char_to_file(here);
	free(here);
}

void	copy_char_to_file(char *content)
{
	ssize_t		err;
	int			fd;

	err = 0;
	fd = open("./heredoc/.Heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Erreur lors de l'ouverture du fichier");
		return ;
	}
	err = write(fd, content, ft_strlen(content));
	if (err == -1)
	{
		perror("Erreur lors de l'écriture dans le fichier");
		close(fd);
		return ;
	}
	close(fd);
}

int	get_err_value(t_list *curr, int state)
{
	int	err;

	err = 0;
	if (curr->next)
	{
		if (state == 5 && is_pipe(curr->next->content))
		{
			print_error(2, curr->next->content);
			err = 1;
		}
		if (state != 5 && (is_token(curr->next->content, 1) || is_heredoc(curr->next->content)))
		{
			print_error(2, curr->next->content);
			err = 1;
		}
		else if (state == 1)
			capture_heredoc(curr->next->content);
	}
	else if ((ft_strcmp("|", curr->content) == 0) && !curr->next)
		err = 2;
	else
	{
		print_error(3, "");
		err = 1;
	}
	return (err);
}

int	check_syntax(t_list *lst)
{
	t_list	*curr;
	int		err;

	curr = lst;
	err = 0;
	if (!lst)
		return (ft_lstclear(&lst, free), 0);
	if (ft_strcmp(curr->content, "|") == 0)
	{
		print_error(2, curr->content);
		err = 1;
	}
	while (curr && !err)
	{
		if (is_heredoc(curr->content))
			err = get_err_value(curr, 1);
		else if (is_token(curr->content, 0))
			err = get_err_value(curr, 0);
		else if (is_pipe(curr->content))
			err = get_err_value(curr, 5);
		if (err)
			break ;
		curr = curr->next;
	}
	ft_lstclear(&lst, free);
	return (err);
}
