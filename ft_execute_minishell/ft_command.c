/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:14:52 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/24 11:05:33 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	ft_exec_child(t_list *head, char *cmd, char **command)
{
	int	flag;

	flag = 0;
	if (g_ptr.data->in != 0)
	{
		dup2(g_ptr.data->in, 0);
		close(g_ptr.data->in);
	}
	if (g_ptr.data->out != 1)
	{
		dup2(g_ptr.data->out, 1);
		close(g_ptr.data->out);
		close(g_ptr.data->fd[0]);
	}
	flag = ft_builting(head);
	if (flag == 1)
	{
		execve(cmd, command, last_command(g_ptr.data->env_list));
		ft_print_error(cmd);
	}
}

void	exec_command(t_list *head, char *cmd, char **command)
{
	g_ptr.data->pid = fork();
	if (!g_ptr.data->pid)
	{
		if (g_ptr.data->out == -1 || g_ptr.data->in == -1)
			exit(1);
		if (head && cmd[0])
			ft_exec_child(head, cmd, command);
		exit(0);
	}
}

void	ft_exec_command(t_list *head)
{
	char	**command;
	char	*cmd;

	command = last_command(head);
	cmd = ft_check_command(command[0]);
	if (!ft_strcmp(cmd, "./minishell"))
		g_ptr.shell++;
	g_ptr.line = ft_strdup(cmd);
	if (g_ptr.data->size == 1)
		if (head && !ft_builting(head))
			return ;
	exec_command(head, cmd, command);
}

void	ft_unlink(int flag)
{
	t_list	*head;

	if (flag == 0)
	{
		head = g_ptr.save_file;
		while (head)
		{
			unlink(head->content);
			head = head->next;
		}
	}
	else
	{
		head = g_ptr.save_desc;
		while (head)
		{
			close(head->fds);
			head = head->next;
		}
	}
}

void	ft_command(t_list *head)
{
	int	out;
	int	in;

	if (g_ptr.flag)
		return ;
	out = dup(1);
	in = dup(0);
	ft_handel_redic(&(head->redic), 1);
	if (head->int_file == 2 && g_ptr.data->in != -1)
		g_ptr.data->in = head->in;
	ft_exec_command(head->command);
	dup2(out, 1);
	close(out);
	dup2(in, 0);
	close(in);
	ft_unlink(3);
	ft_unlink(0);
	g_ptr.save_file = NULL;
}
