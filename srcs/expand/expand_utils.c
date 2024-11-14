/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 14:46:32 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/14 11:54:21 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expand.h"
#include <stdio.h>

int	ft_strlen_doll(char *str, char *delim)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		ft_esquive_quote(&str[i], &i);
		if (ft_strdelim_p(delim, str[i]))
			break ;
		i++;
	}
	return (i);
}

void	print_env(t_env *evp)
{
	while (evp != NULL)
	{
		printf("%s=", evp->key);
		printf("%s\n", evp->value);
		evp = evp->next;
	}
}

int	ft_count_exp(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '$')
	{
		while (str[i] == '$' && str[i] != '\0')
			i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] == '$' || str[i] == '\'' || str[i] == ' ' || str[i] == '"' || str[i] == '\t' || str[i] != '\0')
			break ;
		i++;
	}
	return (i);
}
void	add_one(t_list **lst, char **str, int *i)
{
	int	len;

	len = 0;
	while ((*str)[*i] != '\0' && (*str)[*i] != '$')
	{
		len++;
		(*i)++;
	}
	if (len > 0)
		ft_lstadd_back(lst, ft_lstnew(ft_strndup(&(*str)[*i - len], len)));
}

int check_all(char c)
{
	if (!ft_isalpha(c) && !ft_isdigit((char)c) && c != '_')
		return (0);
	return (1);
}

void	add_two(t_list **lst, char **str, int *i)
{
	int	len;

	len = 0;
	while ((*str)[*i] == '$')
	{
		(*i)++;
		len++;
	}
	while (check_all((*str)[*i]))
	{
		len++;
		(*i)++;
	}
	if (len > 0)
		ft_lstadd_back(lst, ft_lstnew(ft_strndup(&(*str)[*i - len], len)));
}

int	check_expansion(char *str)
{
	int	cpt;

	cpt = 0;
	while (str[cpt] == '$')
		cpt++;
	if (cpt % 2 == 0)
		return (0);
	if (check_all(str[cpt]))
		return (cpt);
	else
		return (0);
}

char	*get_env(char *str, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(str, env->key) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

void	change_var(t_list **lst, t_env *env)
{
	t_list	*curr;
	t_list	*top;
	char	*tmp;
	int		len;

	curr = *lst;
	top = *lst;
	while (curr)
	{
		len = check_expansion(curr->content);
		if (len)
		{
			tmp = get_env(curr->content + len, env);
			free(curr->content);
			curr->content = ft_strdup(tmp);
			free(tmp);
		}
		curr = curr->next;
	}
	*lst = top;
}

int	ft_list_len(t_list *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len += ft_strlen(lst->content);
		lst = lst->next;
	}
	return (len);
}

char	*resotre_list(t_list *lst)
{
	char	*old;
	int		len;
	int		i;
	int		j;

	len = ft_list_len(lst);
	old = malloc(sizeof(char) * len + 1);
	if (!old)
		return (NULL);
	j = 0;
	while (lst)
	{
		i = 0;
		while(lst->content[i] != '\0')
		{
			old[j] = lst->content[i];
			j++;
			i++;
		}
		lst = lst->next;
	}
	old[j] = '\0';
	return (old);
}

void ft_use(char **str, t_env *env)
{
    t_list *lstr;
    int i;
    
    lstr = NULL;
    i = 0;
    (void)env;
    while ((*str)[i] != '\0')
    {
		add_one(&lstr, str, &i);
        if ((*str)[i] == '$')
			add_two(&lstr, str, &i);
    }
	change_var(&lstr, env);
	free(*str);
	*str = resotre_list(lstr);
	ft_lstclear(&lstr, free);
}

void	expansion(t_exp **exp, t_env *env)
{
	t_exp	*curr;
	t_exp	*top;

	curr = *exp;
	top = *exp;
	while (curr)
	{
		if (curr->state == TO_EXPAND)
			ft_use(&curr->token, env);
		curr = curr->next;
	}
	*exp = top;
}