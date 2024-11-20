/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:12:20 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/18 10:55:21 by mranaivo         ###   ########.fr       */
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
		unset = find_key(data->env, data->argv[1]);
		if (unset)
			replace_value(&unset, data->argv[1]);
		else
			export_new_key(&data->env, data->argv[1]);
	}
	return (0);
}

static int	u_index_to_delone(t_env *env, char	*key)
{
	int	i;

	i = 0;
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
			return (i);
		env = env->next;
		i++;
	}
	return (i);
}

static void	unset_apply(t_env **env, int index)
{
	t_env	*temp;
	t_env	*delone;
	int		i;

	temp = *env;
	if (index == 0)
	{
		delone = temp;
		(*env) = (*env)->next;
		delete_node(delone);
		return ;
	}
	i = 0;
	while (temp)
	{
		if (i + 1 == index && temp->next)
		{
			delone = temp->next;
			temp->next = delone->next;
			delete_node(delone);
			return ;
		}
		i++;
		temp = temp->next;
	}
}

int	ft_unset(t_data *data)
{
	int		index;

	if (!data->argv || !data->argv[0])
		return (0);
	index = u_index_to_delone(data->env, data->argv[1]);
	unset_apply(&data->env, index);
	return (0);
}

int	ft_env(t_data *data)
{
	print_env(data->env);
	return (0);
}