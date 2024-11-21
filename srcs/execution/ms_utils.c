/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:28:25 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/21 14:36:36 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

void	print_exec(int state, char *name)
{
	if (state == 1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (state == 2)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
}

int	check_file(t_redir *red)
{
	int	fd;

	while (red)
	{
		if (red->state == INPUT)
		{
			if (access(red->str, F_OK) != 0)
				return (print_exec(1, red->str), 0);
			if (access(red->str, R_OK) != 0)
				return (print_exec(2, red->str), 0);
		}
		else
		{
			if (access(red->str, F_OK) != 0)
			{
				fd = open(red->str, O_CREAT | O_WRONLY | O_APPEND, 0644);
				if (fd < 2)
					return (perror("Open"), 0);
				close(fd);
			}
			else if (access(red->str, W_OK) != 0)
				return (print_exec(2, red->str), 0);
		}
		red = red->next;
	}
	return (1);
}

int	ms_redirect_in(t_shell *shell)
{
	t_list	*file;
	int		fd;

	file = ft_lstlast(shell->f_in);
	if (!file)
		return (-1);
	fd = open(file->content, O_RDONLY);
	if (fd < 2)
	{
		close(fd);
		return (-1);
	}
	return (fd);
}

int	ms_redirect_out(t_shell *shell)
{
	t_list	*file;
	t_token	*curr;
	int		fd;

	file = ft_lstlast(shell->f_out);
	if (!file)
		return (-1);
	curr = shell->token;  
	while (curr->next)
	{
		if (ft_strcmp(curr->next->token, file->content) == 0)
			break ;
		curr = curr->next;
	}
	if (curr && curr->next && curr->state == APPEND)
		fd = open(file->content, O_CREAT | O_WRONLY | O_APPEND);
	else
		fd = open(file->content, O_CREAT | O_WRONLY | O_TRUNC);
	if (fd < 2)
	{
		close(fd);
		return (-1);
	}
	return (fd);
}

void	copy_standard(int *fd_in, int *fd_out, int state)
{
	if (state == 1)
	{
		dup2(STDIN_FILENO, *fd_in);
		dup2(STDOUT_FILENO, *fd_out);
	}
	else if (state == 0)
	{
		dup2(*fd_in, STDIN_FILENO);
		dup2(*fd_out, STDOUT_FILENO);
	}
}

int	one_cmd(t_data *data)
{
	(void)data;
	return (0);
}

void	ft_close(int fd[])
{
	close(fd[0]);
	close(fd[1]);
}