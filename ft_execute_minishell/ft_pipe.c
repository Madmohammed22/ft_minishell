/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 15:24:21 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/24 11:05:47 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

void	initialize(t_quotes *qutes, t_data *data)
{
	if (qutes)
	{
		qutes->cp = 0;
		qutes->cq = 0;
		qutes->cs = 0;
		qutes->en = 0;
		qutes->bk = 0;
	}
	if (data)
	{
		data->env_list = NULL;
		data->status = 0;
		data->exec = 0;
		data->red = 0;
	}
}
