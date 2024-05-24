/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 18:45:16 by mmad              #+#    #+#             */
/*   Updated: 2024/05/24 09:00:13 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	ft_found_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (0);
}

char	*ft_strchr_plus_equals(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '+' && s[i + 1] == '=')
		{
			i += 2;
			return ((char *)&s[i]);
		}
		else if ((s[i] == '+' || s[i + 1] == '='))
		{
			i += 2;
			return ((char *)&s[i]);
		}
		i++;
	}
	if (s[i] == '=' || s[i + 1])
		return ((char *)&s[i]);
	return (NULL);
}

int	ft_strchr_if(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	if (s[i] == (char)c)
		return (1);
	return (0);
}

t_list	*ft_return_var(t_list **head, char *target)
{
	t_list	*temp;

	if (!*head || !head)
		return (NULL);
	temp = *head;
	while (temp)
	{
		if (ft_strcmp((char *)temp->key, target) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	ft_print_list(void)
{
	t_list	*head;
	t_list	*save;

	head = g_ptr.data->env_list;
	save = ft_return_var(&head, "_");
	ft_remove_if(&head, "_", 1);
	ft_lstadd_back(&head, ft_lstnew((char *)save->content));
	ft_separate_node(head);
	while (head)
	{
		if (ft_strchr_if((char *)head->content, '=') == 1)
			printf("%s=%s\n", head->key, head->value);
		head = head->next;
	}
}
