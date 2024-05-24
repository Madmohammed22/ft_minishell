/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:59:46 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/24 10:46:48 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	ft_lstnew_back(t_list **head, char *cont, int flag)
{
	t_list	*node;

	node = ft_lstnew(ft_strtrim(cont, " "));
	if (node->content[0])
	{
		node->x = flag;
		ft_lstadd_back(head, node);
	}
}

void	utils_split(t_str *strr, t_list **head, int flag)
{
	if (strr->join)
		ft_lstnew_back(head, strr->join, 0);
	if (strr->flag == 1 && (strr->str[strr->i + 1]
			|| strr->str[strr->i] == strr->c))
	{
		if (strr->str[strr->i] != ' ')
			strr->join = ft_new_strjoin(NULL, strr->str[strr->i]);
		if (strr->str[strr->i + 1] == strr->c && strr->c != ' ')
		{
			strr->i = strr->i + 1;
			strr->join = ft_strjoin(strr->join, strr->join);
		}
		if (strr->str[strr->i] != ' ')
			ft_lstnew_back(head, strr->join, flag);
	}
	strr->join = NULL;
	strr->flag = 0;
}

t_list	*split_end_or(char *line, char *set, int check, int ff)
{
	t_list		*head;
	t_quotes	qutes;
	t_str		strr;

	head = NULL;
	ini_str(&strr);
	initialize(&qutes, NULL);
	strr.str = line;
	while (line[strr.i])
	{
		ft_check_quotes(line[strr.i], &qutes);
		charset(line[strr.i], set, &strr);
		if (line[strr.i] == strr.c && (line[strr.i + 1] == strr.c || check == 0)
			&& !qutes.cp && !qutes.cq && !qutes.cs)
			strr.flag = 1;
		else
			strr.join = ft_new_strjoin(strr.join, line[strr.i]);
		if (strr.flag == 1 || !line[strr.i + 1])
			utils_split(&strr, &head, ff);
		strr.i++;
	}
	return (head);
}

void	ft_print_error(char *cmd)
{
	char	*str;
	int		ex;

	ex = 127;
	if (cmd && cmd[0] == '.' && !access(cmd, F_OK) && access(cmd, X_OK))
	{
		str = "Permission denied";
		ex = 126;
	}
	else if (ft_strrchr(cmd, '/') && opendir(cmd))
	{
		str = "Is a directory";
		ex = 126;
	}
	else if (!ft_strrchr(cmd, '/'))
		str = "command not found";
	else
		str = "No such file or directory";
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" : ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(ex);
}

char	*ft_new_strjoin(char *str, char c)
{
	int		i;
	char	*join;

	join = malloc(ft_strlen(str) + 2);
	ft_lstadd_back(&(g_ptr.head_free), ft_lstnew_v1(join));
	i = 0;
	if (str != NULL)
	{
		while (str[i])
		{
			join[i] = str[i];
			i++;
		}
	}
	if (c == 0)
		join[i] = c;
	else
	{
		join[i] = c;
		i++;
		join[i] = 0;
	}
	return (join);
}
