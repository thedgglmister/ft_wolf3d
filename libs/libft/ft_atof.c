/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 15:58:57 by biremong          #+#    #+#             */
/*   Updated: 2017/05/15 15:59:00 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_atof(char *str)
{
	double	result;
	int		sign;
	int		i;
	double	place_value;

	result = ft_atoi(str);
	sign = (result < 0 ? -1 : 1);
	if (!(str = ft_strchr(str, '.')))
		return (result);
	str++;
	i = 0;
	place_value = 0.1;
	while (ft_isdigit(str[i]))
	{
		result += (str[i] - '0') * place_value * sign;
		place_value /= 10;
		i++;
	}
	return (result);
}
