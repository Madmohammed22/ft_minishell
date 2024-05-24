/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 04:34:29 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/24 12:02:43 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINISHELL_H
# define FT_MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <libgen.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct Data
{
	char		*save;
	int			status;
	int			fd[2];
	int			in;
	int			out;
	int			red;
	int			pid;
	int			exec;
	t_list		*env_list;
	int			data_mode;
	int			size;
}				t_data;

typedef struct quotes
{
	int			cp;
	int			cq;
	int			cs;
	int			en;
	int			bk;
}				t_quotes;

typedef struct STR
{
	char		*str;
	char		*join;
	char		c;
	int			i;
	int			flag;
}				t_str;

typedef struct Globall
{
	t_list		*head_free;
	t_data		*data;
	int			mode;
	int			shell;
	char		*backup;
	int			syntax;
	char		*line;
	int			xx;
	t_list		*save_file;
	t_list		*save_desc;
	int			flag;
	t_list		*save_invalid_var;
	char		*dynamic_pwd;
	int			last_wildcard_idx;

	int			s_backtrack_idx;
	int			next_to_wildcard_idx;
}				t_global;

extern t_global	g_ptr;

t_list			*ft_lstnew_v1(void *content);
void			ft_free(void);
void			ft_if_exist_var_v2(t_list *env, t_list *head);
int				ft_count_qutes(char *line, t_quotes *qutes);
void			ft_handel_redic(t_list **redic, int flag);
void			ft_exec_utils(t_list *head, int flag);
void			ft_entry_values(void);
void			ft_exec_redic(t_list *head, int flag);
void			ft_lstnew_back(t_list **head, char *cont, int flag);
int				ft_check_syntax(t_list *head, int flag);
void			ft_nested_pip_ex(t_list *head, int fd1, int fd0);
void			ini_str(t_str *data);
t_list			*ft_nested_pip(char *line);
t_list			*split_end_or(char *str, char *set, int flag, int ff);
void			ft_check_string(char *str);
void			ft_display(t_list *ptr);
int				access_intfile(char *path);
int				access_outfile(char *path);
void			ft_unlink(int flag);
t_list			*ft_lstnew_v2(int content);
char			*ft_qutes(t_str *strr, int flag);
t_list			*ft_handel_qutes(t_list *head, int flag);
void			ft_error(char *path);
char			*ft_pwd(void);
void			ft_check_quotes(char c, t_quotes *data);
int				ft_read_stdin(char *end);
void			ft_command(t_list *head);
void			ft_split_rediction(char *line, t_list **new);
void			ft_syntax(char *line);
char			*join_command(t_list *head);
int				ft_read_stdin(char *end);
char			*ft_check_command(char *command);
char			**last_command(t_list *head);
int				access_outfile_herdoc(char *path);
int				ft_wild_card_string_matching(char *s, char *p);
t_list			*ft_wild_card(char *p);
int				ft_check_wildcard(char *line);

void			ft_print_error(char *cmd);
void			ft_fork_exit(int er);
void			initialize(t_quotes *qutes, t_data *data);
t_list			*ft_wild_card(char *p);
char			*ft_return_variable(char *str, int *i);
char			*ft_new_strjoin(char *str, char c);
char			*ft_getenv(char *search);
void			close_fd(t_list **tmp, int fd0);
void			check_eo(t_list *head, int fd1, int fd0);
void			wait_proccess(void);
void			ft_handel_expend(t_list **head, t_str *strr, int flag);
char			*ft_search_if_key_exist_on_env(t_list **env, char *head);
t_list			*ft_create_var(char *command, char c);
void			ft_print_list(void);
void			ft_buffer_to_list(t_list **head, char **command);
void			ft_edit_if_exist_var(t_list *env, t_list *head);
void			ft_separate_node(t_list *head);
t_list			*ft_grep_env(t_list **env_list, t_list *head);
void			echo_container(t_list *env, t_list *command);
int				ft_strchr_specific_char(const char *s, int c);
void			ft_cd(t_list *head);
char			*ft_delete_from_string(char *str, char c);
void			ft_buffer_linked_list(t_list **head, t_list *command);
int				ft_builting(t_list *command);
void			ft_exit(t_list *head);
void			handle_signal(int sig);
void			handle_signal_cat(int sig);
char			*ft_remove(char *str, int flag, t_list **head);
void			handle_signal(int sig);
void			handle_signal_cat(int sig);
void			ft_handle_signals(void);
void			ft_for_wild(char *str, t_list **head);
void			charset(char c, char *set, t_str *strr);
void			ft_export(t_list *command_list);
int				ft_strcmp(char *s1, char *s2);
int				ft_is_white_space(char c);
int				ft_if_plus_eql(char *str);
int				ft_found_equal(char *str);
char			*ft_search_if_key_exist_on_env(t_list **env, char *head);
int				ft_search_if_key_exist(t_list **env, t_list *head);
int				ft_scan_var(char *var);
void			ft_print_error_var(t_list *command_list);
void			ft_print_export(t_list *head);
void			ft_remove_if(t_list **head, char *target, int flag);
int				ft_strchr_if(const char *s, int c);
void			echo_container(t_list *env, t_list *command);
void			ft_unset(t_list *command_list);
int				ft_strnstr_edit(char *big);
void			ft_exit_status(int er);
void			ft_buffer_linked_list_env_insert(t_list **head,
					t_list *command);
t_list			*ft_pars_vars_and_return(t_list *new_command, t_list *command);
#endif
