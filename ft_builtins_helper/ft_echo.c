/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 03:16:22 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/24 08:58:45 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

char	*ft_delete_from_string(char *str, char c)
{
	char	*dest;
	int		i;
	int		j;

	dest = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	ft_lstadd_back(&(g_ptr.head_free), ft_lstnew_v1(dest));
	if (!dest)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == c)
		{
			i++;
		}
		dest[j] = str[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

void	ft_if_exist_var_echo(t_list *env, t_list *head)
{
	t_list	*temp_env;
	char	**result;
	int		i;

	temp_env = env;
	while (head)
	{
		while (temp_env)
		{
			if (ft_strcmp((char *)temp_env->key, (char *)head->content) == 0)
			{
				result = ft_split((char *)temp_env->value, ' ');
				i = 0;
				while (result[i])
					printf("%s ", result[i++]);
			}
			temp_env = temp_env->next;
		}
		temp_env = env;
		head = head->next;
	}
	temp_env = env;
}

void	echo_container(t_list *env, t_list *command)
{
	int	flag_op;

	(void)env;
	flag_op = 0;
	command = command->next;
	if (command && ft_strnstr_edit(command->content) == 1)
	{
		while (ft_strnstr_edit(command->content) == 1)
			command = command->next;
		flag_op = 1;
	}
	while (command)
	{
		ft_putstr_fd(command->content, 1);
		if (command->next)
			ft_putchar_fd(' ', 1);
		command = command->next;
	}
	if (flag_op == 1)
		return ;
	else
		printf("\n");
}
