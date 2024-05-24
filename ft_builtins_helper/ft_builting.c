/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 19:25:03 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/24 11:11:37 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	ft_sort_env(t_list **head, int swapped)
{
	t_list	*ptr;
	t_list	*last_node;
	char	*temp;

	last_node = NULL;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr = *head;
		while (ptr->next != last_node)
		{
			if (ft_strcmp((char *)ptr->content, (char *)ptr->next->content) > 0)
			{
				temp = ptr->content;
				ptr->content = ptr->next->content;
				ptr->next->content = temp;
				swapped = 1;
			}
			ptr = ptr->next;
		}
		last_node = ptr;
	}
}

void	ft_print_export(t_list *head)
{
	t_list	*tmp;
	int		c;
	int		swapped;

	swapped = 1;
	tmp = head;
	ft_sort_env(&head, swapped);
	ft_separate_node(tmp);
	c = 34;
	while (tmp)
	{
		if (ft_strchr_if((char *)tmp->content, '=') == 0)
			printf("declare -x %s=%c%s%c\n", (char *)tmp->key, c,
				(char *)tmp->value, c);
		else
			printf("declare -x %s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}

void	ft_echo(t_list *command)
{
	ft_separate_node(g_ptr.data->env_list);
	echo_container(g_ptr.data->env_list, command);
}

void	ft_pwd_display(void)
{
	char	*path;

	path = (char *)malloc(sizeof(char) * 1024);
	ft_lstadd_back(&(g_ptr.head_free), ft_lstnew_v1(path));
	if (!path)
		return ;
	path = getcwd(path, 1024);
	printf("%s\n", path);
}

int	ft_builting(t_list *command)
{
	char	*str;

	if (g_ptr.data->in == -1 || g_ptr.data->out == -1)
		return (1);
	str = ft_strtrim(command->content, " ");
	if (!ft_strcmp(str, "env") && ft_lstsize(command) == 1)
		ft_print_list();
	else if (!ft_strcmp(str, "export"))
		ft_export(command);
	else if (!ft_strcmp(str, "unset"))
		ft_unset(command);
	else if (!ft_strcmp(str, "echo"))
		ft_echo(command);
	else if (!ft_strcmp(str, "cd"))
		ft_cd(command);
	else if (!ft_strcmp(str, "pwd"))
		ft_pwd_display();
	else if (!ft_strcmp(str, "exit"))
		ft_exit(command);
	else
		return (1);
	g_ptr.data->status = 0;
	return (0);
}
