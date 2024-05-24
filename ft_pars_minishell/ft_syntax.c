/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:49:51 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/24 10:47:11 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	ft_nested_syntax(t_list **head)
{
	char		*cmd;
	t_quotes	qutes;
	t_list		*list;
	t_list		*ss;

	list = *head;
	ss = split_end_or(list->content, "<> ", 0, 2);
	g_ptr.data->red = ft_check_syntax(ss, 2);
	if (!g_ptr.data->red)
		ft_split_rediction(list->content, head);
	cmd = join_command(list->command);
	if (cmd && !g_ptr.data->red)
	{
		ft_check_string(cmd);
		if (ft_count_qutes(cmd, &qutes) == 1 && !g_ptr.data->red)
		{
			cmd = ft_substr(cmd, 1, ft_strlen(cmd) - 2);
			ft_syntax(cmd);
		}
	}
}

void	ft_syntax(char *line)
{
	t_list	*head;
	t_list	*list;

	head = split_end_or(line, "|&", 1, 4);
	g_ptr.data->red = ft_check_syntax(head, 4);
	while (head && !g_ptr.data->red)
	{
		if (head->x != 4)
		{
			list = split_end_or(head->content, "|", 0, 4);
			g_ptr.data->red = ft_check_syntax(list, 4);
			while (list && !g_ptr.data->red)
			{
				if (list->x != 4)
					ft_nested_syntax(&list);
				list = list->next;
			}
		}
		head = head->next;
	}
}

void	ft_exec_here(t_list *head, int j)
{
	int	i;

	i = 0;
	while (head && i < j)
	{
		if (!ft_strcmp(head->content, "<<") && head->next)
			ft_read_stdin(head->next->content);
		head = head->next;
		i++;
	}
}

int	ft_check_syntax(t_list *head, int flag)
{
	int		i;
	int		value;
	t_list	*tmp;

	value = 0;
	i = 0;
	tmp = head;
	while (head && !value)
	{
		if ((head->x == flag && (!head->next || head->next->x == flag))
			|| (head->x == 4 && i == 0))
			value = 1;
		head = head->next;
		i++;
	}
	if (value == 1)
	{
		ft_exec_here(tmp, i);
		ft_unlink(3);
		ft_unlink(0);
		g_ptr.save_file = NULL;
	}
	return (value);
}

void	ft_check_string(char *line)
{
	int			i;
	t_quotes	qutes;

	i = 0;
	initialize(&qutes, NULL);
	while (line[i])
	{
		ft_check_quotes(line[i], &qutes);
		i++;
	}
	if (qutes.cp || qutes.cq || qutes.cs || (qutes.en % 2) || (qutes.bk % 2))
		g_ptr.data->red = 1;
}
