/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_darken.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 20:39:13 by biremong          #+#    #+#             */
/*   Updated: 2017/05/19 20:47:07 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_darken(int *color)
{
	char	r;
	char	g;
	char	b;
	int		dark_color;

	r = (*color & 0xFF0000) >> 17;
	g = (*color & 0x00FF00) >> 9;
	b = (*color & 0x0000FF) >> 1;
	dark_color = 0;
	dark_color |= r;
	dark_color <<= 8;
	dark_color |= g;
	dark_color <<= 8;
	dark_color |= b;
	*color = dark_color;
}
