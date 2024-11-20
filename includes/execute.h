/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 10:04:42 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/20 16:25:42 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "./parsing.h"
# include "./builtins.h"
# include "./expand.h"
 
/*======================STRUCTURES======================*/

typedef	struct	s_data	t_data;

typedef enum	e_s_redir
{
	INPUT,
	OUTPUT
}	t_s_redir;

typedef struct	s_redir
{
	char			*str;
	t_s_redir		state;
	struct s_redir	*next;
}					t_redir;

typedef enum e_exc_bul
{
	BUILTINS,
	EXECVE
}	t_exc_bul;

/*========================MS_REDIR======================*/

void	get_redir(t_redir **redir, t_token *token);

/*===================MS_DATA_COPMLETE===================*/

void	ft_data_clear(t_data **data);
t_data	*ft_new_data(t_shell *shell, t_env *env, int id);
void	ft_data_add(t_data **data, t_data *new_data);
int		complete_data(t_data **data, t_shell *shell, t_env *env);

/*======================MS_EXECUTE======================*/

void	ft_execve(t_data *data);
int		ft_strlen_env(t_env *env);
char	**ft_get_arg(t_token *token);
char	*ft_get_cmd(t_token *token);

/*======================CLEAN_CODE======================*/

void	free_data(t_data *data);
void	free_str(char **str);

/*=======================MS_UTILS=======================*/

int		ms_redirect_in(t_shell *shell);
int		ms_redirect_out(t_shell *shell);
int		one_cmd(t_data *data);
void	ft_close(int fd[]);

void	execution(t_data *data, t_exc_bul exec);
int		exec_and_wait(t_data *data);
#endif