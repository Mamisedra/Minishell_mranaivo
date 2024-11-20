/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:59:37 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/18 17:59:56 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	replace_value_env(t_env **env, char *path, char *key)
{
	t_env	*curr;

	curr = find_key(*env, key);
	if (!curr)
		return ;
	free((curr)->value);
	(curr)->value = ft_strdup(path);
}

static void	maj_env(t_env **env)
{
	char	*old;
	char	pwd[1024];

	old = get_env("PWD", *env);
	if (!old)
		return ;
	replace_value_env(env, old, "OLDPWD");
	free(old);
	if (getcwd(pwd, sizeof(pwd)) == NULL)
	{
		perror("getcwd() a échoué");
		return ;
	}
	else
		replace_value_env(env, pwd, "PWD");
}

int	ft_cd(t_data *data)
{
	char	*home_dir;

	home_dir = get_env("HOME", data->env);
	if (!home_dir || !data->argv)
		return (0);
	if (data->argv[1] == NULL || data->argv[1][0] == '~')
	{
		if (chdir(home_dir) != 0)
		{
			perror("Minishell : cd");
			free(home_dir);
			return (0);
		}
	}
	else if (chdir(data->argv[1]) != 0)
	{
		perror("Minishell : cd");
		free(home_dir);
		return (0);
	}
	maj_env(&data->env);
	free(home_dir);
	return (0);
}

void	ft_echo_n(t_data *data)
{
	int	i;

	i = 1;
	if (!data->argv)
	{
		printf("\n");
		return ;
	}
	while (data->argv[i])
	{
		printf("%s", data->argv[i]);
		i++;
		if (data->argv[i] != NULL)
			printf(" ");
	}
	printf("\n");
}

int	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd() a échoué");
		return (1);
	}
	else
		printf("%s\n", cwd);
	return (0);
}

int	ft_exit(t_data *data)
{
	(void)data;
	return (0);
}
