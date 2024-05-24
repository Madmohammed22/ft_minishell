/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 11:03:56 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/24 11:09:12 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	ft_check_01(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_print_err(char *str1, char *str2, char *str3)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(str3, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_exit(t_list *head)
{
	int	size;

	size = ft_lstsize(head);
	if (size > 2)
	{
		ft_print_err("minishell: exit:", " too ", "many arguments");
		ft_fork_exit(1);
	}
	else
	{
		head = head->next;
		if (!head)
			exit(0);
		else if (ft_check_01(head->content) == 1)
		{
			ft_print_err("minishell: exit:", head->content,
				": numeric argument required");
			exit(2);
		}
		exit(ft_atoi(head->content));
	}
}
