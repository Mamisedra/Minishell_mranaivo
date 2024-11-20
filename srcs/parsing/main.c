/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 12:27:52 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/20 14:03:08 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ms_execute(t_shell *shell, t_env *env)
{
	int		ret;
	int		exec;
	int		cdl;
	t_data	*data;

	data = NULL;
	ret = complete_data(&data, shell, env);
	exec = 0;
	if (ret == 1)
	{
		cdl = is_builtins(data->cmd);
		if (cdl)
		{
			ft_builtins_execute(data, cdl);
			exec = 2;
		}
		else
		{
			ft_execve(data);
			exec = 1;
		}
	}
	else if (ret > 1)
		exec = exec_and_wait(data);
	return (exec);
}

int	main(int argc, char *argv[], char **env)
{
	t_shell	*shell;
	t_env	*envp;
	char	*prompt;
	int		cmd;

	shell = NULL;
	envp = NULL;
	(void)argc;
	(void)argv;
	duplicate_env(env, &envp);
	cmd = 0;
	while (1)
	{
		prompt = readline("parsing > ");
		add_history(prompt);
		if (!prompt)
			return (1);
		if (!parsing(prompt, &shell, envp))
			cmd = ms_execute(shell, envp);
		if (strcmp(prompt, "exit") == 0)
		{
			free_shell(&shell);
			free(prompt);
			break ;
		}
		free(prompt);
		free_shell(&shell);
	}
	ft_env_clear(&envp);
	rl_clear_history();
	return (cmd);
}
