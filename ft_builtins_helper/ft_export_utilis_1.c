/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utilis_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:37:03 by mmad              #+#    #+#             */
/*   Updated: 2024/05/24 08:59:27 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	ft_count_plus(char *head)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (head[i])
	{
		if (head[i] == '+')
			count++;
		i++;
	}
	return (count);
}

int	ft_scan_var(char *var)
{
	int	flag;
	int	i;

	flag = 0;
	i = 0;
	if (var[0] == '_' && !var[1])
		return (0);
	else if (var[0] == '=' || ft_isalpha(var[0]) == 0 || ft_count_plus(var) > 1)
		return (1);
	while (var[i])
	{
		if (ft_isalpha(var[i]) == 1 || ft_isdigit((int)var[i]) == 1
			|| (var[i] == '_') || ((var[i] == '+' && var[i + 1] == '\0')
				|| (var[i] == '_' && var[i + 1] == '\0')))
			flag = 1;
		else
			return (1);
		i++;
	}
	if (flag == 1)
		return (0);
	return (1);
}

int	ft_search_if_key_exist(t_list **env, t_list *head)
{
	t_list	*temp_env;
	t_list	*temp_head;

	if (!head || !head->key || !head->value || !env || !(*env))
		return (0);
	temp_env = *env;
	temp_head = head;
	if (temp_env->key && temp_env->value)
	{
		while (temp_env)
		{
			if (ft_strncmp(temp_env->key, temp_head->key,
					ft_strlen(temp_env->key)) == 0)
				return (0);
			temp_env = temp_env->next;
		}
	}
	temp_env = *env;
	return (1);
}

int	ft_is_white_space(char c)
{
	if (c <= 32)
		return (1);
	return (0);
}
