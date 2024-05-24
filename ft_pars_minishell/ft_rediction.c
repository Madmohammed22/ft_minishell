/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rediction.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 23:19:20 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/24 10:46:56 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	ft_handel_redic(t_list **redic, int flag)
{
	t_list	*head;

	head = *redic;
	while (head)
	{
		ft_exec_utils(head, flag);
		if (g_ptr.data->out == -1 || g_ptr.data->in == -1)
			break ;
		head = head->next;
	}
}

void	ft_rediction_v1(char *str, t_list *head)
{
	if (!ft_strcmp(str, ">>") || !ft_strcmp(str, ">"))
	{
		if (!ft_strcmp(str, ">>"))
			g_ptr.data->out = access_outfile_herdoc(head->next->content);
		else
			g_ptr.data->out = access_outfile(head->next->content);
		if (g_ptr.data->out != -1)
		{
			dup2(g_ptr.data->out, 1);
			close(g_ptr.data->out);
			g_ptr.data->out = 1;
		}
	}
	else if (!ft_strcmp(str, "<"))
	{
		g_ptr.data->in = access_intfile(head->next->content);
		if (g_ptr.data->in != -1)
		{
			dup2(g_ptr.data->in, 0);
			close(g_ptr.data->in);
			g_ptr.data->in = 0;
		}
	}
}

void	ft_exec_utils(t_list *head, int flag)
{
	char	*str;

	str = head->content;
	if (!ft_strcmp(str, "<<") && !flag)
		g_ptr.data->in = ft_read_stdin(head->next->content);
	else
		ft_rediction_v1(str, head);
}

void	ft_exec_redic(t_list *head, int flag)
{
	while (head)
	{
		ft_exec_utils(head, flag);
		if (g_ptr.data->out == -1 || g_ptr.data->in == -1)
			break ;
		head = head->next;
	}
}

void	ft_split_rediction(char *line, t_list **command)
{
	t_list	*head;
	t_list	**node;

	head = split_end_or(line, ">< ", 0, 4);
	while (head)
	{
		if (head->x == 4 && head->next->x != 4)
		{
			if (!ft_strcmp(head->content, "<<"))
				node = &((*command)->here_doc);
			else
				node = &((*command)->redic);
			if (!ft_strcmp(head->content, "<"))
				(*command)->int_file = 1;
			else if (!ft_strcmp(head->content, "<<"))
				(*command)->int_file = 2;
			ft_lstnew_back(node, head->content, 0);
			head = head->next;
			ft_lstnew_back(node, head->content, 4);
		}
		else
			ft_lstnew_back(&(*command)->command, head->content, 0);
		head = head->next;
	}
}
