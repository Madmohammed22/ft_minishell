/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 01:37:39 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/24 11:05:25 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

char	*ft_check_command(char *command)
{
	char	*path;
	t_list	*head;
	char	*cmd;

	path = ft_getenv("PATH");
	if (path && !ft_strrchr(command, '/') && command[0] && !ft_strrchr(command,
			'.'))
	{
		head = split_end_or(path, ":", 0, 4);
		cmd = ft_strjoin("/", command);
		while (head)
		{
			if (head->x == 0)
			{
				path = ft_strjoin(head->content, cmd);
				if (access(path, F_OK) == 0)
					return (path);
			}
			head = head->next;
		}
	}
	return (ft_strdup(command));
}

int	ft_lstsize_v1(t_list *head)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (head)
	{
		if ((head->content)[0] || flag == 1)
		{
			i++;
			flag = 1;
		}
		head = head->next;
	}
	if (i == 0)
		i++;
	return (i);
}

char	**last_command(t_list *head)
{
	int		i;
	int		size;
	char	**arr;
	int		flag;

	i = 0;
	flag = 0;
	size = ft_lstsize_v1(head);
	arr = malloc(sizeof(char *) * (size + 1));
	ft_lstadd_back(&(g_ptr.head_free), ft_lstnew_v1(arr));
	while (head)
	{
		if ((head->content)[0] || flag == 1)
		{
			arr[i] = ft_strdup(head->content);
			flag = 1;
			i++;
		}
		head = head->next;
	}
	if (i == 0)
		arr[i++] = ft_strdup("");
	arr[i] = NULL;
	return (arr);
}

void	ft_display(t_list *ptr)
{
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	while (ptr)
	{
		printf("--%s--\n", (char *)ptr->content);
		ptr = ptr->next;
	}
	printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
}

void	ft_fork_exit(int er)
{
	g_ptr.data->pid = fork();
	if (g_ptr.data->pid == 0)
		exit(er);
}
