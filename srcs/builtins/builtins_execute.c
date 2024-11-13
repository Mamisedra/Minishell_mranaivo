/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:17:42 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/13 15:38:03 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

void	ft_builtins_execute(t_data *data)
{
	if (!ft_strcmp(data->cmd, "cd"))
		data->exit = ft_cd(data);
	else if (!ft_strcmp(data->cmd, "pwd"))
		data->exit = ft_pwd(data);
	else if (!ft_strcmp(data->cmd, "echo"))
		ft_echo_n(data);
	else if (!ft_strcmp(data->cmd, "export"))
		data->exit = ft_export(data);
	else if (!ft_strcmp(data->cmd, "unset"))
		data->exit = ft_unset(data);
	else if (!ft_strcmp(data->cmd, "env"))
		data->exit = ft_env(data);
	else if (!ft_strcmp(data->cmd, "exit"))
		data->exit = ft_exit(data);
}
