/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:56:47 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/13 16:00:34 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "./parsing.h"
# include "./expand.h"

/*======================STRUCTURES======================*/

typedef	struct	s_data	t_data;

/*======================BUILTINS_ENV======================*/

int		ft_export(t_data *data);
int		ft_unset(t_data *data);
int		ft_env(t_data *data);

/*========================BUILTINS========================*/

int		ft_cd(t_data *data);
void	ft_echo_n(t_data *data);
int		ft_pwd(t_data *data);
int		ft_exit(t_data *data);


/*========================DELETE_ONE=======================*/

void	delete_one(t_env **env, char *key);

#endif