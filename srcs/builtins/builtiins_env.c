/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtiins_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:12:20 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/13 16:00:00 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(t_data *data)
{
	return (0);
}

int	ft_unset(t_data *data)
{
	t_env	*env;

	env = data->env;
	while (env)
	{
		if (!ft_strcmp(env->key, data->argv[0]))
		{
			delete_one(&env, env->key);
			break ;
		}
		env = env->next;
	}
	return (0);
}

int	ft_env(t_data *data)
{
	print_env(data->env);
	return (0);
}