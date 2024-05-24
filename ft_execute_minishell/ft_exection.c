/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:58:14 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/24 11:05:38 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	ft_exec_recursive(t_list **head)
{
	int	p;

	p = fork();
	if (p == 0)
	{
		if (g_ptr.data->in == -1 || g_ptr.data->out == -1)
			exit(1);
		ft_nested_pip_ex((*head)->new_list->new_list, g_ptr.data->out,
			g_ptr.data->in);
		exit(g_ptr.data->status);
	}
	wait(&(g_ptr.data->status));
}

void	ft_dup2_v1(int *in, int *out)
{
	dup2(*out, 1);
	close(*out);
	dup2(*in, 0);
	close(*in);
	ft_unlink(3);
	ft_unlink(0);
}

void	exec_utils(t_list *head, int fd1, int fd0)
{
	int	out;
	int	in;

	if (head->new_list->next)
	{
		pipe(g_ptr.data->fd);
		g_ptr.data->out = g_ptr.data->fd[1];
	}
	else
		g_ptr.data->out = fd1;
	if (head->new_list->x == 1)
	{
		out = dup(1);
		in = dup(0);
		ft_handel_redic(&head->new_list->redic, 1);
		if (head->new_list->int_file == 2)
			g_ptr.data->in = head->new_list->in;
		ft_exec_recursive(&head);
		ft_dup2_v1(&in, &out);
	}
	else
		ft_command(head->new_list);
	close_fd(&head, fd0);
}

void	ft_nested_pip_ex(t_list *head, int fd1, int fd0)
{
	t_list	*tmp;

	g_ptr.data->out = fd1;
	g_ptr.data->in = fd0;
	g_ptr.data->exec = 0;
	while (head)
	{
		check_eo(head, fd1, fd0);
		if (g_ptr.data->exec == 0)
		{
			tmp = head->new_list;
			g_ptr.data->size = ft_lstsize(tmp);
			while (head->new_list)
			{
				if (head->new_list->x != 4)
					exec_utils(head, fd1, fd0);
				head->new_list = head->new_list->next;
			}
			wait_proccess();
		}
		head = head->next;
	}
}
