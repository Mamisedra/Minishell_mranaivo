/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:17:42 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/18 14:47:44 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int	is_builtins(char *str)
{
	if (!ft_strcmp(str, "cd\0"))
		return (1);
	else if (!ft_strcmp(str, "pwd\0"))
		return (2);
	else if (!ft_strcmp(str, "echo\0"))
		return (3);
	else if (!ft_strcmp(str, "export\0"))
		return (4);
	else if (!ft_strcmp(str, "unset\0"))
		return (5);
	else if (!ft_strcmp(str, "env\0"))
		return (6);
	else if (!ft_strcmp(str, "exit\0"))
		return (7);
	return (0);
}

void	ft_builtins_execute(t_data *data, int bultins)
{
	if (bultins == 1)
		data->exit = ft_cd(data);
	else if (bultins == 2)
		data->exit = ft_pwd();
	else if (bultins == 3)
		ft_echo_n(data);
	else if (bultins == 4)
		data->exit = ft_export(data); //OK WITH ARG
	else if (bultins == 5)
		data->exit = ft_unset(data);
	else if (bultins == 6)
		data->exit = ft_env(data);
	else if (bultins == 7)
		data->exit = ft_exit(data); // to_edit
}
