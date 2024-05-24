/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 01:35:45 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/24 11:05:36 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	check_eo(t_list *head, int fd1, int fd0)
{
	char	*op;

	op = (char *)head->content;
	if (ft_strcmp(op, "&&") == 0)
	{
		if (g_ptr.data->status == 0)
			g_ptr.data->exec = 0;
		else
			g_ptr.data->exec = 1;
	}
	else if (ft_strcmp(op, "||") == 0)
	{
		if (g_ptr.data->status != 0)
			g_ptr.data->exec = 0;
		else
			g_ptr.data->exec = 1;
	}
	if (g_ptr.data->exec == 0)
	{
		g_ptr.data->out = fd1;
		g_ptr.data->in = fd0;
	}
}

void	wait_proccess(void)
{
	int	status;
	int	tmp;

	tmp = 0;
	while (1)
	{
		status = wait(&tmp);
		if (status == g_ptr.data->pid)
			g_ptr.data->status = tmp;
		if (status == -1)
			break ;
	}
	if (g_ptr.data->status > 255)
		g_ptr.data->status = g_ptr.data->status >> 8;
}

void	close_fd(t_list **tmp, int fd0)
{
	t_list	*head;

	head = *tmp;
	if (head->new_list->next != NULL)
	{
		close(g_ptr.data->fd[1]);
		if (g_ptr.data->in != fd0)
			close(g_ptr.data->in);
		g_ptr.data->in = g_ptr.data->fd[0];
	}
	else if (head->next == NULL)
	{
		if (g_ptr.data->in != fd0)
			close(g_ptr.data->in);
	}
}
