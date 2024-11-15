/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 00:50:06 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/13 15:39:25 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./parsing.h"
# include "./expand.h"
# include "./builtins.h"

typedef	struct	s_data
{
	t_env	*env;
	char	*cmd;
	char	**argv;
	int		exit;
	int		fd_in;
	int		fd_out;
}			t_data;

#endif
