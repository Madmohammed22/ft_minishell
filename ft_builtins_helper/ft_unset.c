/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:09:51 by mmad              #+#    #+#             */
/*   Updated: 2024/05/24 09:00:27 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	ft_remove_if(t_list **head, char *target, int flag)
{
	t_list	*temp;
	t_list	*prev;

	temp = *head;
	prev = NULL;
	while (temp)
	{
		if (ft_strcmp((char *)temp->key, target) == 0)
		{
			if (ft_strcmp(target, "_") == 0 && flag == 0)
				return ;
			if (prev)
			{
				prev->next = temp->next;
				temp = temp->next;
			}
			else
			{
				*head = temp->next;
				temp = temp->next;
			}
		}
		else
		{
			prev = temp;
			temp = temp->next;
		}
	}
}

void	ft_unset(t_list *command_list)
{
	t_list	*temp;

	ft_separate_node(g_ptr.data->env_list);
	ft_separate_node(command_list->next);
	temp = command_list->next;
	while (temp)
	{
		ft_remove_if(&g_ptr.data->env_list, temp->content, 0);
		temp = temp->next;
	}
}
