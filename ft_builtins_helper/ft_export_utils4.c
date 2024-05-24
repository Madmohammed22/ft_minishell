/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:45:16 by mmad              #+#    #+#             */
/*   Updated: 2024/05/24 09:00:18 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

void	ft_exit_status(int er)
{
	g_ptr.data->pid = fork();
	if (g_ptr.data->pid == 0)
		exit(er);
}

void	ft_print_error_var(t_list *command_list)
{
	ft_separate_node(command_list);
	while (command_list)
	{
		if (ft_scan_var(command_list->key) == 1)
			printf("minishell: export: %s: not a valid identifier\n",
				command_list->content);
		command_list = command_list->next;
	}
	ft_exit_status(1);
}

void	ft_buffer_linked_list_env_insert(t_list **head, t_list *command)
{
	while (command)
	{
		ft_lstadd_back(head, ft_lstnew(command->content));
		command = command->next;
	}
	ft_separate_node(*head);
	ft_print_export(*head);
}

t_list	*ft_pars_vars_and_return(t_list *new_command, t_list *command)
{
	t_list	*temp;
	int		flag;

	temp = command;
	ft_separate_node(temp);
	flag = 0;
	while (temp)
	{
		if (ft_scan_var(temp->key) == 0)
			ft_lstadd_back(&new_command, ft_lstnew(temp->content));
		temp = temp->next;
	}
	return (new_command);
}
