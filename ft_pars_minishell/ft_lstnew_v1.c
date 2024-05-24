/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_v1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 18:44:47 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/24 10:46:44 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

t_list	*ft_lstnew_v1(void *content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (0);
	new_node->addr = content;
	new_node->content = NULL;
	new_node->next = NULL;
	return (new_node);
}

t_list	*ft_lstnew_v2(int content)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	ft_lstadd_back(&g_ptr.head_free, ft_lstnew_v1(new_node));
	if (!new_node)
		return (0);
	new_node->fds = content;
	new_node->content = NULL;
	new_node->next = NULL;
	return (new_node);
}
