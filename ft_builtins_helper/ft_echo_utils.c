/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmad <mmad@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 21:58:59 by mmad              #+#    #+#             */
/*   Updated: 2024/05/24 08:57:36 by mmad             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"

int	ft_found_dolar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (0);
}

int	ft_strnstr_edit(char *big)
{
	int	i;

	i = 0;
	if ((big[i] == '-' && big[i + 1] == 'n'))
	{
		i++;
		while (big[i] == 'n')
			i++;
		if (big[i] == 0)
			return (1);
	}
	return (0);
}
