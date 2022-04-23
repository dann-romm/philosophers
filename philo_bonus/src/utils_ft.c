/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ft.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doalbaco <doalbaco@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 18:48:05 by doalbaco          #+#    #+#             */
/*   Updated: 2022/04/24 00:37:28 by doalbaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdint.h>

int32_t	ft_atoi(const char *str)
{
	int32_t	i;
	int32_t	sign;
	int32_t	ans;

	i = 0;
	ans = 0;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		sign = (str[i] == '-') * (-1) + (str[i] == '+');
		i++;
	}
	while (str[i] == '0')
		i++;
	if (str[i] > '0' && str[i] <= '9')
		ans = sign * (str[i++] - '0');
	while (str[i] >= '0' && str[i] <= '9')
	{
		if ((ans * 10 + sign * (str[i] - '0') > 0) != (ans > 0))
			return (0);
		ans = ans * 10 + sign * (str[i] - '0');
		i++;
	}
	return (ans);
}

char	*ft_strcpy(char *dest, char *src)
{
	char	*_dest;

	_dest = dest;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (_dest);
}
