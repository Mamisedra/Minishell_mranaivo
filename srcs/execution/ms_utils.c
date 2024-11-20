/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:28:25 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/20 17:02:15 by mranaivo         ###   ########.fr       */
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
		ft_putstr_fd("Minishell", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("No such file or directory\n", 2);
	}
	else if (state == 2)
	{
		ft_putstr_fd("Minishell", 2);
		ft_putstr_fd(name, 2);
		ft_putstr_fd("Permission denied\n", 2);
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
			if (access(red->str, W_OK) != 0)
				return (print_exec(2, red->str), 0);
			if (access(red->str, F_OK) != 0)
			{
				fd = open(red->str, O_CREAT | O_WRONLY | O_APPEND |  O_TRUNC, 0644);
				if (fd < 2)
				{
					perror("Open");
					return (0);
				}
				close(0);
			}
		}
		red = red->next;
	}
	return (1);
}

int	ms_redirect_in(t_shell *shell)
{
	(void)shell;
	return (0);
}

int	ms_redirect_out(t_shell *shell)
{
	(void)shell;
	return (0);
}

int	one_cmd(t_data *data)
{
	(void)data;
	return (0);
	// return (data->exit);
}

void	ft_close(int fd[])
{
	close(fd[0]);
	close(fd[1]);
}