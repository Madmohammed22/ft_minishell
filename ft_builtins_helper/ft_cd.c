/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:20:44 by mmad              #+#    #+#             */
/*   Updated: 2024/05/24 08:57:02 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

char	*ft_search_if_key_exist_on_env(t_list **env, char *head)
{
	t_list	*temp_env;

	if (!head || !env || !(*env))
		return (NULL);
	else if (!ft_strcmp(head, "?"))
		return (ft_itoa(g_ptr.data->status));
	temp_env = *env;
	if (temp_env->key && temp_env->value)
	{
		while (temp_env)
		{
			if (head)
			{
				if (ft_strcmp((char *)temp_env->key, head) == 0)
					return ((char *)temp_env->value);
			}
			temp_env = temp_env->next;
		}
	}
	temp_env = *env;
	return (NULL);
}

char	*ft_getenv(char *search)
{
	if (!search)
		return (ft_strdup("$"));
	ft_separate_node(g_ptr.data->env_list);
	return (ft_search_if_key_exist_on_env(&(g_ptr.data->env_list), search));
}

void	ft_if_exist_var_v2(t_list *env, t_list *head)
{
	t_list	*temp_node;

	temp_node = head;
	if (temp_node->key && temp_node->value)
	{
		while (env)
		{
			while (temp_node)
			{
				if (ft_strcmp(env->key, temp_node->key) == 0
					&& ft_is_white_space(temp_node->value[0]) != 1)
				{
					env->content = ft_strdup(temp_node->content);
					env->value = ft_strdup(temp_node->value);
				}
				temp_node = temp_node->next;
			}
			temp_node = head;
			env = env->next;
		}
		temp_node = head;
	}
}

void	ft_dynamiq_pwd(void)
{
	char	*prev_pwd;
	t_list	*pp;
	t_list	*pp1;

	prev_pwd = malloc(sizeof(char) * 1024);
	g_ptr.dynamic_pwd = ft_getenv("PWD");
	pp = ft_lstnew(ft_strjoin("OLDPWD=", g_ptr.dynamic_pwd));
	ft_separate_node(pp);
	ft_separate_node(g_ptr.data->env_list);
	ft_if_exist_var_v2(g_ptr.data->env_list, pp);
	prev_pwd = getcwd(prev_pwd, 1024);
	pp1 = ft_lstnew(ft_strjoin("PWD=", prev_pwd));
	ft_separate_node(pp1);
	ft_separate_node(g_ptr.data->env_list);
	ft_if_exist_var_v2(g_ptr.data->env_list, pp1);
	free(prev_pwd);
}

void	ft_cd(t_list *head)
{
	if (ft_lstsize(head) == 2)
	{
		if (chdir(ft_strdup(head->next->content)))
		{
			perror(ft_strjoin("minishell: cd: ", (char *)head->next->content));
			ft_exit_status(1);
		}
	}
	else if (ft_lstsize(head) > 2)
	{
		printf("minishell: cd: too many arguments\n");
		ft_exit_status(1);
	}
	else
	{
		if (!ft_getenv("HOME"))
		{
			printf("minishell: cd: HOME not set\n");
			ft_exit_status(1);
		}
		else
			chdir(ft_getenv("HOME"));
	}
	ft_dynamiq_pwd();
}
