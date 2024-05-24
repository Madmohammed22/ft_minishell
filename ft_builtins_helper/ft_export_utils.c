/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:04:41 by mmad              #+#    #+#             */
/*   Updated: 2024/05/24 09:00:06 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	ft_grep_size_of_env(char **command)
{
	int	i;

	i = 0;
	while (command[i])
		i++;
	return (i);
}

void	ft_buffer_to_list(t_list **head, char **command)
{
	int		i;
	char	*join;
	char	*buff;

	i = 0;
	if (ft_grep_size_of_env(command) != 0)
	{
		while (command[i])
			ft_lstadd_back(head, ft_lstnew(command[i++]));
	}
	else
	{
		buff = malloc(1024);
		ft_lstadd_back(&g_ptr.head_free, ft_lstnew_v1(buff));
		ft_lstadd_back(head, ft_lstnew(ft_strjoin("PWD=", getcwd(buff, 1024))));
		join = ft_strjoin("SHLVL=", ft_itoa(g_ptr.shell));
		ft_lstadd_back(head, ft_lstnew(join));
		ft_lstadd_back(head, ft_lstnew("_=/usr/bin/env"));
	}
}

void	ft_buffer_linked_list(t_list **head, t_list *command)
{
	while (command)
	{
		ft_lstadd_back(head, ft_lstnew(command->content));
		command = command->next;
	}
}

int	ft_if_plus_eql(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && str[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	ft_strchr_specific_char(const char *s, int c)
{
	int	i;

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
