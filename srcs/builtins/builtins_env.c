/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:12:20 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/14 14:34:55 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_export(t_data *data)
{
	t_env	*unset;

	if (!data->argv[0])
		print_sort_env("delare -x", data->env);
	else
	{
		unset = find_key(data->env, data->argv[0]);
		if (unset)
			replace_value(&unset, data->argv[0]);
		else
			export_new_key(&data->env, data->argv[0]);
	}
	return (0);
}

int	ft_unset(t_data *data)
{
	t_env	*env;
	int		len;

	env = data->env;
	while (env)
	{
		if (!data->argv[0])
			return (0);
		len = ft_strlen_chr(data->argv[0],'=');
		if (!ft_strncmp(env->key, data->argv[0], len))
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