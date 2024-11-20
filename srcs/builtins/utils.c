/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:57:45 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/18 10:01:50 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strlen_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**copy_env(t_env *env)
{
	char	**strenv;
	int		len;
	int		i;

	len = ft_strlen_env(env);
	strenv = malloc(sizeof(char *) * (len + 1));
	if (!strenv)
		return (NULL);
	i = 0;
	while (env)
	{
		strenv[i] = ft_strdup(env->key);
		i++;
		env = env->next;
	}
	strenv[i] = NULL;
	return (strenv);
}

void	compare_string(char **str1, char **str2, int *i)
{
	char	*tmp;

	if (ft_strcmp(*str1, *str2) <= 0)
		return ;
	else
	{
		tmp = *str1;
		*str1 = *str2;
		*str2 = tmp;
		*i = 0;
	}
}

char	**sort_env(t_env *env)
{
	char	**str;
	int		i;

	str = copy_env(env);
	i = 0;
	if (!str)
		return (NULL);
	while (str[i + 1] != NULL)
	{
		if (ft_isalpha(str[i][0]))
			compare_string(&str[i], &str[i+1], &i);
		i++;
	}
	return (str);
}

void	print_sort_env(char *str, t_env *env)
{
	t_env	*top;
	char	**strev;
	int		i;

	i = 0;
	top = env;
	strev = sort_env(env);
	while (strev[i])
	{
		while (env)
		{
			if (!ft_strcmp(env->key, strev[i]))
			{
				printf("%s %s=\"%s\"\n", str, env->key, env->value);
				break ;
			}
			env = env->next;
		}
		env = top;
		i++;
	}
	i = 0;
	while (strev[i++] != NULL)
		free(strev[i]);
	free(strev);
}

t_env	*find_key(t_env *env, char *argv)
{
	char	*key;
	int		len;
	t_env	*curr;

	if (!argv)
		return (NULL);
	len = ft_strlen_chr(argv, '=');
	if (len == 0)
		return(NULL);
	key = ft_strndup(argv, len);
	curr = env;
	while (curr)
	{
		if (!ft_strcmp(curr->key, key))
		{
			free(key);
			return (curr);
		}
		curr = curr->next;
	}
	free(key);
	return (NULL);
}

void	replace_value(t_env **env, char *argv)
{
	int		len;
	char	*key;
	char	*value;

	if (!argv)
		return ;
	len = ft_strlen_chr(argv, '=');
	key = ft_strndup(argv, len);
	if (!key)
		return ;
	value = ft_strdup(argv + len + 1);
	if (!value)
		return ;
	free((*env)->key);
	free((*env)->value);
	(*env)->key = key;
	(*env)->value = value;
}

void	export_new_key(t_env **env, char *argv)
{
	int		len;
	char	*key;
	char	*value;

	if (!argv || !ft_strchr(argv, '='))
		return ;
	len = ft_strlen_chr(argv, '=');
	key = ft_strndup(argv, len);
	if (!key)
		return ;
	value = ft_strdup(argv + len + 1);
	if (!value)
		return ;
	ft_back_env(env, ft_new_env(key,value));
	free(key);
}

void delete_node(t_env *temp)
{
	if (!temp)
		return ;
	free(temp->key);
	free(temp->value);
	free(temp);
}


void ft_list_remove_if(t_env **env, char *key_delone)
{
	t_env *cur;

	cur = *env;
	if (env == NULL || *env == NULL)
		return;
	if (ft_strcmp(cur->key, key_delone) == 0)
	{
		*env = cur->next;
		free(cur->key);
		free(cur->value);
		free(cur);
		return ;
	}
	else
	{
		cur = *env;
		ft_list_remove_if(&cur->next, key_delone);
	}
}