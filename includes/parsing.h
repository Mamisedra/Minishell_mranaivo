/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mranaivo <mranaivo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:24:46 by mranaivo          #+#    #+#             */
/*   Updated: 2024/11/13 13:42:08 by mranaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../lib/libft/libft.h"
# include "../lib/libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# undef INT_MAX
# define INT_MAX 2147483647

typedef struct s_env	t_env;

typedef enum e_state
{
	COMMANDE,
	ARGUMENT,
	HEREDOC,
	IN_FILE,
	OUT_FILE,
	FILE_NAME_O,
	FILE_NAME_I,
	FILE_NAME,
	APPEND
}	t_state;

typedef enum e_input
{
	STD_IN,
	PIPE_IN,
	FILE_IN
}	t_input;

typedef enum e_output
{
	STD_OUT,
	PIPE_OUT,
	FILE_OUT
}	t_output;

typedef struct s_token
{
	int				id;
	char			*token;
	int				quote;
	t_state			state;
	struct s_token	*next;
}					t_token;

typedef struct s_shell
{
	int				id;
	char			*lexer;
	t_token			*token;
	t_list			*f_in;
	t_list			*f_out;
	t_input			in;
	t_output		out;
	struct s_shell	*next;
}					t_shell;

/*==========================UTILS=========================*/

void		ft_esquive_quote(char *str, int *i);
void		ft_esquive_space(char *str, int *i);
int			ft_strlen_chr(char *str, char c);
bool		ft_strdelim_p(const char *str, char c);
char		*ft_strcatquote(char *str);

/*======================PARSING_UTILs=====================*/

int			check_quote_unclose(char *str);
int			ft_strlen_quote(char *str);
char		*ft_strtok_p(char *str, int *i, char *delim);
char		*ft_delimtok_p(char *str, int *i, char *delim);
int			check_quote(char *str);

/*==========================LEXER=========================*/

void		prompt_lexer(char *str, t_shell **shell);
void		token_complete(t_shell *shell);
void		loop_token(t_shell **shell);

/*=======================SHELL_LIST=======================*/

t_shell		*new_shell_list_p(char *str, int i);
t_shell		*shelllast_p(t_shell *shell);
void		shell_add_back_p(t_shell **shell, t_shell *new_shell);
void		_complete_shell(t_shell **shell);
void		_input_output_file(t_shell *shell);

/*=======================TOKEN_LIST========================*/

t_token		*new_token_list_p(char *str, int i);
t_token		*tokenlast_p(t_token *token);
void		token_add_back_p(t_token **token, t_token *new_token);
void		add_token(t_token **token, char *str, int *i, int id);
void		add_delimiter(t_token **token, char *str, int *i, int id);

/*=======================PARSING==========================*/

int			parsing(char *str, t_shell **shell, t_env *env);
int			check_quote_unclose(char *str);
void		tokenisation(char *str, t_list **lst);

/*=======================CLEAN_CODE=======================*/

void		free_heredoc(t_list **lst);
void		free_token(t_token **tkn);
void		free_shell(t_shell **shell);
void		remove_heredoc(t_list **file);

/*======================CHECK_SYNTAX======================*/

void		capture_heredoc(char *str, t_env *env);
void		copy_char_to_file(char *content);
int			get_err_value(t_list *curr, int state, t_env *env);
int			check_syntax(t_list *lst, t_env *env);

/*========================PRINT_SHELL=====================*/

void		print_shell(t_shell *shell);
void		print_token(t_token *token);
void		print_list(t_list *lst);

/*=======================CODE_STATUS========================*/

void		_token_state(t_token **token);
t_input		ft_flags_in(t_shell *current);
t_output	ft_flags_out(t_shell *current);

/*=========================LIBFT============================*/

void		print_error(int err, char *str);
int			ft_strchr_quote(char *str, char c);
bool		is_heredoc(char *str);
bool		is_pipe(char *str);
bool		is_token(char *str, int pipe);

/*=========================PIPE_FILE=========================*/

bool		pipe_end(char *str);
int			complete_pipe(t_shell *shell, t_env *env);
int			close_pipe(char *str, t_shell *shell, t_env *env);


void	_expand_shell(t_shell **shell, t_env *env);
void 	ft_use(char **str, t_env *env);

#endif
