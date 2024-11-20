/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 00:50:06 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/20 11:48:42 by mranaivo         ###   ########.fr       */
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
# include "./execute.h"
# include <sys/types.h>
# include <sys/wait.h>

typedef	struct	s_data
{
	int				id;
	t_env			*env;
	char			*cmd;
	char			**argv;
	int				exit;
	int				fd_in;
	int				fd_out;
	struct s_data	*next;
}					t_data;

#endif
