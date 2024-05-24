/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 04:33:37 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/23 23:26:20 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_global	g_ptr;

void	ft_exec_pro(char *line)
{
	t_list	*head;

	head = NULL;
	ft_syntax(line);
	if (g_ptr.data->red == 1)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		g_ptr.data->red = 0;
		g_ptr.data->status = 2;
	}
	else
	{
		g_ptr.mode = 1;
		head = ft_nested_pip(line);
		ft_nested_pip_ex(head, 1, 0);
	}
}

char	*ft_handel_tab(char *line)
{
	int		size;
	char	*new;
	int		i;

	size = ft_strlen(line);
	new = malloc(size + 1);
	ft_lstadd_back(&g_ptr.head_free, ft_lstnew_v1(new));
	i = 0;
	while (line[i])
	{
		if (line[i] == '\t' || (line[i] >= 9 && line[i] <= 13))
			line[i] = ' ';
		new[i] = line[i];
		i++;
	}
	new[i] = 0;
	return (new);
}

void	change_env(void)
{
	t_list	*pp1;
	t_list	*pp2;
	t_list	*split;

	if (g_ptr.line)
	{
		split = split_end_or(g_ptr.line, " ", 0, 4);
		if (!split)
			return ;
		pp1 = ft_lstnew(ft_strjoin("_=", split->content));
		ft_separate_node(pp1);
		ft_separate_node(g_ptr.data->env_list);
		ft_if_exist_var_v2(g_ptr.data->env_list, pp1);
	}
	if (g_ptr.shell > 999)
		g_ptr.shell = 1;
	pp2 = ft_lstnew(ft_strjoin("SHLVL=", ft_itoa(g_ptr.shell)));
	ft_separate_node(pp2);
	ft_separate_node(g_ptr.data->env_list);
	ft_if_exist_var_v2(g_ptr.data->env_list, pp2);
}

int	main(int ac, char **av, char **env)
{
	char	*line;

	(void)av;
	ft_entry_values();
	initialize(NULL, g_ptr.data);
	ft_buffer_to_list(&g_ptr.data->env_list, env);
	if (ac != 1)
		return (1);
	while (1)
	{
		g_ptr.mode = 0;
		ft_handle_signals();
		line = ft_pwd();
		line = readline(line);
		ft_lstadd_back(&(g_ptr.head_free), ft_lstnew_v1(line));
		add_history(line);
		if (!line)
			break ;
		line = ft_handel_tab(line);
		change_env();
		g_ptr.flag = 0;
		ft_exec_pro(line);
	}
	ft_free();
	return (0);
}

void	ft_free(void)
{
	t_list	*tmp;
	t_list	*head;

	head = g_ptr.head_free;
	tmp = NULL;
	while (head)
	{
		tmp = head->next;
		free(head->addr);
		ft_lstdelone(head, free);
		head = tmp;
	}
	free(g_ptr.data);
	printf("exit\n");
}
