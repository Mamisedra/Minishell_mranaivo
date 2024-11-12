/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 11:51:09 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/11 15:02:06 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expand.h"

static t_env	*ft_env_last(t_env *env)
{
	if (env)
	{
		while (env)
		{
			if (env->next == NULL)
				return (env);
			env = env->next;
		}
	}
	return (env);
}

t_env	*ft_new_env(char *key, char *env_s)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	env->env_s = env_s;
	env->next = NULL;
	return (env);
}

void	ft_env_clear(t_env **env)
{
	t_env	*tmp;

	if (env)
	{
		while (*env)
		{
			tmp = (*env)->next;
			free((*env)->key);
			free((*env)->env_s);
			free(*env);
			*env = tmp;
		}
	}
}

void	ft_back_env(t_env **envp, t_env *env)
{
	t_env	*curr;

	if (envp)
	{
		if (*envp == NULL)
			*envp = env;
		else
		{
			curr = ft_env_last(*envp);
			curr->next = env;
		}
	}
}

void	duplicate_env(char **env, t_env **envp)
{
	int		i;
	char	*key;
	int		len;

	i = 0;
	len = 0;
	while (env[i] != NULL)
	{
		len = ft_strlen_chr(env[i], '=');
		key = ft_strndup(env[i], len);
		ft_back_env(envp, ft_new_env(key, ft_strdup(env[i] + len + 1)));
		free(key);
		i++;
	}
}
