/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:27:06 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/24 10:47:15 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

char	*join_command(t_list *head)
{
	char	*join;

	join = NULL;
	while (head)
	{
		join = ft_strjoin(join, head->content);
		if (head->next)
			join = ft_strjoin(join, " ");
		head = head->next;
	}
	return (join);
}

void	ft_nested(t_list *head)
{
	char		*cmd;
	char		*save;
	t_quotes	qutes;
	t_list		*list;

	save = NULL;
	list = head;
	ft_split_rediction(list->content, &(list));
	cmd = join_command(list->command);
	if (cmd)
	{
		if (ft_count_qutes(cmd, &qutes) == 1)
		{
			list->x = 1;
			cmd = ft_strtrim(cmd, " ");
			save = ft_substr(cmd, 1, ft_strlen(cmd) - 2);
			list->new_list = ft_nested_pip(save);
		}
	}
	list->command = ft_handel_qutes(list->command, 0);
	list->redic = ft_handel_qutes(list->redic, 0);
	list->here_doc = ft_handel_qutes(list->here_doc, 1);
	ft_handel_redic(&(list->here_doc), 0);
	list->in = (g_ptr.data)->in;
}

t_list	*ft_nested_pip(char *line)
{
	t_list	*head;
	t_list	*new;
	t_list	*list;

	head = split_end_or(line, "|&", 1, 4);
	new = head;
	while (head)
	{
		if (!head->x)
		{
			list = split_end_or(head->content, "|", 0, 4);
			head->new_list = list;
			while (list)
			{
				if (list->x != 4)
					ft_nested(list);
				list = list->next;
			}
		}
		head = head->next;
	}
	return (new);
}
