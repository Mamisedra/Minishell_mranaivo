/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:48:25 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/13 13:15:52 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "./parsing.h"

typedef struct s_shell	t_shell;

typedef struct s_env
{
	char			*key;
	char			*env_s;
	struct s_env	*next;
}					t_env;

typedef enum e_s_exp
{
	NO_EXPAND,
	TO_EXPAND
}			t_s_exp;

typedef struct	s_exp
{
	char			*token;
	t_s_exp			state;
	int				quote;
	struct s_exp	*next;
}					t_exp;

void	ft_exp_back(t_exp **exp, t_exp *newv);
void	ft_exp_clear(t_exp **exp);
t_exp	*ft_exp_last(t_exp *exp);
t_exp	*ft_exp_new(char *content);
int		ft_exp_len(t_exp *exp);
char	*_restore_prompt(t_exp	*exp);
void	_expand_(char *str, t_exp **exp);

/*============================EXPAND_ENV===========================*/

void	duplicate_env(char **env, t_env **envp);
void	ft_back_env(t_env **envp, t_env *env);
void	ft_env_clear(t_env **env);
t_env	*ft_new_env(char *key, char *env_s);

/*===========================EXPAND_UTILS==========================*/

void	print_env(t_env *evp);
void	expansion(t_exp **exp, t_env *env);

#endif