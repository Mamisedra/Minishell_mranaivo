/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 12:27:52 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/12 17:28:03 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char *argv[], char **env)
{
	t_shell	*shell;
	t_env	*envp;
	char	*prompt;

	shell = NULL;
	envp = NULL;
	(void)argc;
	(void)argv;
	duplicate_env(env, &envp);
	while (1)
	{
		prompt = readline("parsing > ");
		add_history(prompt);
		if (!prompt)
			return (1);
		parsing(prompt, &shell, envp);
		if (strcmp(prompt, "exit") == 0)
		{
			free_shell(&shell);
			free(prompt);
			break ;
		}
		free(prompt);
		print_shell(shell);
		free_shell(&shell);
	}
	ft_env_clear(&envp);
	rl_clear_history();
	return (0);
}
