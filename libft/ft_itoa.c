/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abquaoub <abquaoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 08:45:44 by abquaoub          #+#    #+#             */
/*   Updated: 2024/05/21 21:49:14 by abquaoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minishell.h"
#include "libft.h"

static int	ft_len(long int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n = n * (-1);
		count++;
	}
	else if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static void	ft_rev(char *str)
{
	char	tmp;
	size_t	i;
	size_t	j;

	i = ft_strlen(str);
	j = 0;
	if (str[0] == '-')
		j++;
	while (j < i)
	{
		tmp = str[j];
		str[j] = str[i - 1];
		str[i - 1] = tmp;
		i--;
		j++;
	}
}

static void	ft_test(char *arr, int i, int len, long int number)
{
	if (number < 0)
	{
		arr[0] = '-';
		number = number * (-1);
		i++;
	}
	while (i < len && number > 0)
	{
		arr[i] = (number % 10) + 48;
		number = number / 10;
		i++;
	}
	arr[i] = '\0';
}

char	*ft_itoa(int n)
{
	size_t	number;
	char	*arr;
	int		len;
	int		i;

	i = 0;
	number = n;
	len = ft_len(number);
	if (number == 0)
	{
		arr = ft_strdup("0");
		return (arr);
	}
	arr = (char *)malloc(len + 1);
	ft_lstadd_back(&(g_ptr.head_free), ft_lstnew_v1(arr));
	if (!arr)
		return (0);
	ft_test(arr, i, len, number);
	ft_rev(arr);
	return (arr);
}
