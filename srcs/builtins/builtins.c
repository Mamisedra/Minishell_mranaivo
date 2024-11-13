/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:59:37 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/13 15:49:52 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(t_data *data)
{
	return (0);
}

void	ft_echo_n(t_data *data)
{
	int	i;

	i = 0;
	while (data->argv[i])
	{
		printf("%s", data->argv[i]);
		i++;
	}
}

int	ft_pwd(t_data *data)
{
	return (0);
}

int	ft_exit(t_data *data)
{
	return (0);
}
