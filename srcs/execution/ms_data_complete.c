/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_data_complete.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 09:00:37 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/21 17:15:34 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <time.h>

void	ft_data_clear(t_data **data)
{
	t_data	*curr;
	t_data	*next;

	curr = *data;
	while (curr)
	{
		next = curr->next;
		close(curr->fd_in);
		close(curr->fd_out);
		free(curr->cmd);
		free_str(curr->argv);
		free(curr);
		curr = next;
	}
	*data = NULL;
}

t_data	*ft_new_data(t_shell *shell, t_env *env, int id)
{
	t_data	*dnew;
	int		fd_in;
	int		fd_out;
	dnew = malloc(sizeof(t_data));
	if (!dnew)
		return (NULL);
	fd_in = ms_redirect_in(shell);
	if (fd_in > 2)
		dnew->fd_in = dup(fd_in);
	else
		dnew->fd_in = -1;
	fd_out = ms_redirect_out(shell);
	if (fd_out > 2)
		dnew->fd_out = dup(fd_out);
	else
		dnew->fd_out = -1;
	dnew->id = id;
	dnew->env = env;
	dnew->exit = 0;                                         
	dnew->cmd = ft_get_cmd(shell->token);
	dnew->argv = ft_get_arg(shell->token);
	dnew->next = NULL;
	return (dnew);
}

static t_data	*ft_data_last(t_data *data)
{
	if (data)
	{
		while (data)
		{
			if (data->next == NULL)
				return (data);
			data = data->next;
		}
	}
	return (data);
}

void	ft_data_add(t_data **data, t_data *new_data)
{
	t_data	*tmp;

	if (data)
	{
		if (*data == NULL)
			*data = new_data;
		else
		{
			tmp = ft_data_last(*data);
			tmp->next = new_data;
		}
	}
}

int	complete_data(t_data **data, t_shell *shell, t_env *env)
{
	int		i;
	t_redir	*redir;

	i = 0;
	redir = NULL;
	while (shell)
	{
		get_redir(&redir, shell->token);
		if (check_file(redir) == 0)
			return (-20);
		__redir_clear(&redir);
		ft_data_add(data, ft_new_data(shell, env, i));
		shell = shell->next;
		i++;
	}
	return (i);
}