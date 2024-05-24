/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:56:16 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/24 09:00:22 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	ft_edit_if_exist_var(t_list *env, t_list *head)
{
	t_list	*temp_node;

	temp_node = head;
	while (env)
	{
		while (temp_node && temp_node->key && temp_node->value)
		{
			if (ft_strncmp(env->key, temp_node->key, ft_strlen(env->key)) == 0
				&& ft_if_plus_eql(temp_node->content) == 0
				&& ft_is_white_space(temp_node->value[0]) != 1)
			{
				env->content = ft_strdup(temp_node->content);
				env->value = ft_strdup(temp_node->value);
			}
			else if (ft_if_plus_eql(temp_node->content) == 1
				&& ft_strncmp(env->key, temp_node->key,
					ft_strlen(env->key)) == 0)
				env->content = ft_strjoin(env->key, ft_strjoin("=",
							ft_strjoin(env->value, temp_node->value)));
			temp_node = temp_node->next;
		}
		temp_node = head;
		env = env->next;
	}
}

void	ft_separate_node(t_list *head)
{
	t_list	*temp;

	temp = head;
	while (temp)
	{
		if (ft_strchr_specific_char(temp->content, '=') == 1
			|| ft_strchr_specific_char(temp->content, '+') == 1)
		{
			temp->key = ft_substr(temp->content, 0,
					ft_found_equal(temp->content));
			temp->value = ft_substr(temp->content, ft_found_equal(temp->content)
					+ 1, ft_strlen(temp->content));
		}
		else
		{
			temp->key = ft_substr(temp->content, 0, ft_strlen(temp->content));
			temp->value = ft_strdup("");
		}
		temp = temp->next;
	}
	temp = head;
}

t_list	*ft_grep_env(t_list **env_list, t_list *head)
{
	t_list	*temp;
	t_list	*temp_env_list;

	if (!head)
		return (NULL);
	temp_env_list = *env_list;
	temp = head;
	ft_separate_node(temp);
	while (temp != NULL)
	{
		if (ft_search_if_key_exist(&temp_env_list, temp) == 1)
		{
			ft_lstadd_back(env_list,
				ft_lstnew(ft_delete_from_string(temp->content, '+')));
			ft_separate_node(*env_list);
		}
		temp_env_list = (*env_list);
		temp = temp->next;
	}
	temp = head;
	return (*env_list);
}

int	ft_pars_vars(t_list *command)
{
	t_list	*temp;
	int		flag;

	temp = command;
	ft_separate_node(temp);
	flag = 0;
	while (temp)
	{
		if (ft_scan_var(temp->key) == 1)
			flag = 1;
		temp = temp->next;
	}
	if (flag == 1)
		return (1);
	return (0);
}

void	ft_export(t_list *command_list)
{
	t_list	*test;
	t_list	*new_command;
	int		flag;

	flag = 0;
	new_command = NULL;
	if (!command_list->next)
	{
		test = NULL;
		ft_buffer_linked_list_env_insert(&test, g_ptr.data->env_list);
	}
	else
	{
		ft_separate_node(command_list->next);
		if (ft_pars_vars(command_list->next) == 1)
			flag = 1;
		new_command = ft_pars_vars_and_return(new_command, command_list->next);
		ft_separate_node(new_command);
		ft_separate_node(g_ptr.data->env_list);
		ft_edit_if_exist_var(g_ptr.data->env_list, new_command);
		g_ptr.data->env_list = ft_grep_env(&g_ptr.data->env_list,
				new_command);
	}
	if (flag == 1)
		ft_print_error_var(command_list->next);
}
