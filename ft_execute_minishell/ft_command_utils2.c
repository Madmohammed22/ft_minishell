/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:39:58 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/24 11:05:30 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

char	*ft_qutes(t_str *strr, int flag)
{
	char	*var;
	char	*join;

	(strr->i)++;
	join = NULL;
	while (strr->str[strr->i] && strr->str[strr->i] != strr->c)
	{
		if (strr->str[strr->i] == '$' && strr->c == 34 && !flag)
		{
			var = ft_return_variable(strr->str, &(strr->i));
			join = ft_strjoin(join, var);
		}
		else
			join = ft_new_strjoin(join, strr->str[(strr->i)++]);
	}
	(strr->i)++;
	return (join);
}

char	*ft_return_variable(char *str, int *i)
{
	char	*var;

	var = NULL;
	(*i)++;
	if (str[*i] == '?')
	{
		var = ft_getenv("?");
		(*i)++;
		return (var);
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
	{
		var = ft_new_strjoin(var, str[*i]);
		(*i)++;
	}
	var = ft_getenv(var);
	return (var);
}

void	ft_handel_expend(t_list **head, t_str *strr, int flag)
{
	t_list	*expend;
	char	*var;

	expend = NULL;
	g_ptr.xx = 1;
	var = ft_return_variable(strr->str, &(strr->i));
	if (var && var[0] && !flag)
	{
		expend = split_end_or(var, " ", 0, 4);
		expend->content = ft_strjoin(strr->join, expend->content);
		while (expend->next)
		{
			ft_for_wild(expend->content, head);
			expend = expend->next;
			strr->join = NULL;
			var = ft_strdup(expend->content);
		}
	}
	if (!var)
		var = ft_strdup("");
	strr->join = ft_strjoin(strr->join, var);
}

char	*ft_remove(char *str, int flag, t_list **head)
{
	t_str	strr;

	g_ptr.xx = 0;
	ini_str(&strr);
	strr.str = str;
	while (str[strr.i])
	{
		g_ptr.xx = 0;
		if (str[strr.i] == 34 || str[strr.i] == 39)
			strr.c = str[strr.i];
		if (str[strr.i] == '$' && !flag)
			ft_handel_expend(head, &strr, 0);
		else if (str[strr.i] == strr.c && strr.c)
			strr.join = ft_strjoin(strr.join, ft_qutes(&strr, flag));
		else
		{
			strr.join = ft_new_strjoin(strr.join, str[strr.i]);
			strr.i++;
		}
	}
	return (strr.join);
}

t_list	*ft_handel_qutes(t_list *head, int flag)
{
	t_list	*command;
	char	*cmd;
	t_list	*node;

	command = NULL;
	while (head)
	{
		if (ft_strchr(head->content, '*') && !ft_check_wildcard(head->content)
			&& !flag)
			node = ft_wild_card(head->content);
		else
		{
			cmd = ft_remove(head->content, flag, &command);
			node = ft_lstnew(cmd);
		}
		if (!g_ptr.xx || (g_ptr.xx && node->content[0]))
			ft_lstadd_back(&command, node);
		node = NULL;
		head = head->next;
	}
	return (command);
}
