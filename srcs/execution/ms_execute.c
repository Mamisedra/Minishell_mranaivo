/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:04:00 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/21 17:23:01 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

char	*ft_get_cmd(t_token *token)
{
	if (!token)
		return (NULL);
	while(token)
	{
		if (token->state == COMMANDE)
			return (ft_strdup(token->token));
		token = token->next;
	}
	return (NULL);
}

int	ft_count_arg(t_token *token)
{
	int	len;

	len = 0;
	if (!token)
		return (0);
	while (token)
	{
		if (token->state == ARGUMENT)
			len++;
		token = token->next;
	}
	return (len + 1);
}

char	**ft_get_arg(t_token *token)
{
	int		len;
	int		i;
	char	**arg;

	len = ft_count_arg(token);
	if (len == 0)
		return (NULL);
	i = 0;
	arg = malloc(sizeof(char*) * (len + 1));
	if (!arg)
		return (NULL);
	arg[i++] = ft_get_cmd(token);
	while (token)
	{
		if (token->state == ARGUMENT)
			arg[i++]= ft_strdup(token->token);
		token = token->next;
	}
	arg[i] = NULL;
	return (arg);
}

void	putstrdouble(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		printf("%s\n", str[i]);
		i++;
	}
}

void	data_complete(t_data *data, t_token *token, t_env *env)
{
	data->env = env;
	data->fd_in = 0;
	data->fd_out = 0;
	data->exit = 0;
	data->cmd = ft_get_cmd(token);
	data->argv = ft_get_arg(token);
}

char	*get_path(t_env *env, char *cmd)
{
	char	*path;
	char	*result;
	char	*result_2;
	char	**multi;
	int		i;

	path = get_env("PATH", env);
	if (!path)
		return (ft_strdup(""));
	result = NULL;
	multi = ft_split(path, ':');
	if (!multi)
		return (free(path), ft_strdup(""));
	i = 0;
	while (multi[i])
	{
		result = ft_strjoin(multi[i], "/");
		result_2 = ft_strjoin(result, cmd);
		if (!access(result_2, F_OK | X_OK))
		{
			free(path);
			free_str(multi);
			free(result);
			return (result_2);
		}
		free(result);
		free(result_2);
		result = NULL;
		result_2 = NULL;
		i++;
	}
	free(path);
	free_str(multi);
	return (ft_strdup(""));
}

char	**copy_env_value(t_env *env)
{
	char	**strenv;
	char	*tmp;
	int		len;
	int		i;

	len = ft_strlen_env(env);
	strenv = malloc(sizeof(char *) * (len + 1));
	if (!strenv)
		return (NULL);
	i = 0;
	tmp = NULL;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		strenv[i] = ft_strjoin(tmp, env->value);
		i++;
		free(tmp);
		tmp = NULL;
		env = env->next;
	}
	strenv[i] = NULL;
	return (strenv);
}

void	ft_execve(t_data *data)
{
	char **cenv;
	char	*path;
	pid_t	pid;

	cenv = copy_env_value(data->env);
	if (!cenv)
		return ;
	path = get_path(data->env, data->cmd);
	if (!path)
		return ;
	pid = fork();
	if (pid == 0)
	{
		// if (cmd_absolute())
		// {}
		if (execve(path, data->argv, cenv) < 0)
		{
			printf("Minishell: Command not found : %s\n", data->cmd);
		}
	}
	waitpid(pid, NULL, 0);
	free(path);
	free_str(cenv);
}

void	execution(t_data *data, t_exc_bul state)
{
	char **cenv;
	char	*path;

	cenv = copy_env_value(data->env);
	if (!cenv)
		return ;
	path = get_path(data->env, data->cmd);
	if (!path)
		return ;
	if (state == EXECVE)
	{
		if (execve(path, data->argv, cenv) < 0)
			printf("Minishell: Command not found : %s\n", data->cmd);
	}
	else if (state == BUILTINS)
		ft_builtins_execute(data, is_builtins(data->cmd));
	free(path);
	free_str(cenv);
}

int exec_and_wait(t_data *data)
{
    pid_t   pid;
    int     status = 0;
    int     prev_pipe[2] = {-1, -1};
    int     curr_pipe[2];
    int     standard[2];

	copy_standard(&standard[0], &standard[1], 1);
    while (data)
    {
        if (pipe(curr_pipe) < 0)
            return ( perror("pipe"), 1);
        if (is_builtins(data->cmd))
            execution(data, BUILTINS);
        else
        {
            pid = fork();
            if (pid < 0)
                return (perror("fork"), 1);
            if (pid == 0)
            {
                if (prev_pipe[0] != -1)
                {
                    dup2(prev_pipe[0], STDIN_FILENO);
                    close(prev_pipe[0]);
                }
                else if (data->fd_in > 2)
                {
                    dup2(data->fd_in, STDIN_FILENO);
					perror("Ao gaga kely");
                    close(data->fd_in);
                }
                if (data->fd_out > 2)
                {
                    dup2(data->fd_out, STDOUT_FILENO);
					perror("Ao gaga kely 2");
				    close(data->fd_out);
                }
                else if (data->next)
                    dup2(curr_pipe[1], STDOUT_FILENO);
                close(curr_pipe[0]);
                close(curr_pipe[1]);
                if (prev_pipe[0] != -1)
					close(prev_pipe[1]);
                execution(data, EXECVE);
                exit(1);
            }
            if (prev_pipe[0] != -1)
            {
                close(prev_pipe[0]);
                close(prev_pipe[1]);
            }
            prev_pipe[0] = curr_pipe[0];
            prev_pipe[1] = curr_pipe[1];
        }
        data = data->next;
    }
	copy_standard(&standard[0], &standard[1], 1);
    if (prev_pipe[0] != -1)
    {
        close(prev_pipe[0]);
        close(prev_pipe[1]);
    }
    while (wait(&status) > 0)
			;
    return (WIFEXITED(status) ? WEXITSTATUS(status) : 1);
}
