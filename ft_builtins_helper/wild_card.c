/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 10:21:59 by mmad              #+#    #+#             */
/*   Updated: 2024/05/24 10:00:47 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	ft_wild_card_container(char *str, char *pattern, int *s_index, int *p_index)
{
	while (str[*s_index] != '\0')
	{
		if (pattern[*p_index] != '\0' && (pattern[*p_index] == str[*s_index]))
		{
			(*s_index)++;
			(*p_index)++;
		}
		else if (pattern[*p_index] != '\0' && pattern[*p_index] == '*')
		{
			g_ptr.last_wildcard_idx = *p_index;
			g_ptr.next_to_wildcard_idx = ++(*p_index);
			g_ptr.s_backtrack_idx = *s_index;
		}
		else if (g_ptr.s_backtrack_idx == -1)
			return (0);
		else
		{
			*p_index = g_ptr.next_to_wildcard_idx;
			*s_index = ++(g_ptr.s_backtrack_idx);
		}
	}
	return (1);
}

int	ft_wild_card_string_matching(char *str, char *pattern)
{
	int	s_index;
	int	p_index;

	s_index = 0;
	p_index = 0;
	g_ptr.last_wildcard_idx = -1;
	g_ptr.s_backtrack_idx = -1;
	g_ptr.next_to_wildcard_idx = -1;
	if (!ft_wild_card_container(str, pattern, &s_index, &p_index))
		return (0);
	while (pattern[p_index] != '\0')
	{
		if (pattern[p_index] != '*')
			return (0);
		p_index++;
	}
	return (1);
}

t_list	*ft_wild_card(char *p)
{
	t_list			*buff;
	DIR				*dir;
	struct dirent	*dirptr;

	buff = NULL;
	while (*p == '.' && *++p == '/')
		p++;
	dir = opendir(".");
	if (!dir)
		ft_exit_status(1);
	else
	{
		dirptr = readdir(dir);
		while (dirptr)
		{
			if (ft_wild_card_string_matching((char *)dirptr->d_name, p))
				ft_lstadd_back(&buff, ft_lstnew((char *)dirptr->d_name));
			dirptr = readdir(dir);
		}
	}
	if (!buff)
		buff = ft_lstnew(p);
	closedir(dir);
	return (buff);
}

void	ft_for_wild(char *str, t_list **head)
{
	t_list	*node;

	node = NULL;
	node = ft_wild_card(str);
	if (!node)
		node = ft_lstnew(str);
	ft_lstadd_back(head, node);
}
