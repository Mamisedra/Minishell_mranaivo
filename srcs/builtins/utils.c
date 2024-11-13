/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:57:45 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/13 16:06:42 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	delete_one(t_env **env, char *key)
{
	t_env	*current;
	t_env	*last;
	t_env	*next;

	current = *env;
	if (!ft_strcmp(current->next->key, key))
	{
		last = current;
		return ;
	}
	while (current->next)
	{
		if (!ft_strcmp(current->next->key, key))
		{
			last = current;
			break ;
		}
		current = current->next;
	}
}