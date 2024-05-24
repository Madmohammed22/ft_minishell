/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 01:43:33 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/24 10:47:06 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	ft_entry_values(void)
{
	g_ptr.data = malloc(sizeof(t_data));
	g_ptr.head_free = NULL;
	g_ptr.save_file = NULL;
	g_ptr.save_desc = NULL;
	g_ptr.shell = 0;
	g_ptr.shell++;
	g_ptr.xx = 0;
	g_ptr.mode = 0;
	g_ptr.line = NULL;
	g_ptr.syntax = 0;
	g_ptr.flag = 0;
	g_ptr.backup = NULL;
	g_ptr.data->env_list = NULL;
}

void	ft_check(char c, t_quotes *data)
{
	if (c == 34 && !data->cq && !data->cs)
		data->cq++;
	else if (c == 34 && !data->cs)
		data->cq--;
	if (c == 39 && !data->cq && !data->cs)
		data->cs++;
	else if (c == 39 && !data->cq)
		data->cs--;
}

int	ft_check_str(char *str)
{
	t_quotes	qutes;
	int			i;

	i = 0;
	qutes.cp = 0;
	qutes.cq = 0;
	qutes.cs = 0;
	qutes.en = 0;
	qutes.bk = 0;
	while (str[i])
	{
		ft_check_quotes(str[i], &qutes);
		if (qutes.cp)
			return (1);
		i++;
	}
	return (0);
}

int	ft_count_qutes(char *line, t_quotes *qutes)
{
	int	i;
	int	flag;

	flag = ft_check_str(line);
	i = 0;
	initialize(qutes, NULL);
	while (line[i])
	{
		ft_check(line[i], qutes);
		if (line[i] == '(' && !qutes->cq && !qutes->cs)
		{
			if (line[i + 1] == ')')
				g_ptr.data->red = 1;
			qutes->cp++;
		}
		else if (line[i] == ')' && !qutes->cq && !qutes->cs)
			qutes->cp--;
		else if (!qutes->cp && flag)
			g_ptr.data->red = 1;
		i++;
	}
	return (flag);
}
