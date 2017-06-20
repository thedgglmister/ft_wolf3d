/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_angles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:41:43 by biremong          #+#    #+#             */
/*   Updated: 2017/05/19 20:36:05 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double	*ft_get_col_angles(double cam_dist)
{
	double	*col_angles;
	int		col;

	col_angles = (double*)ft_malloc(sizeof(double) * WIN_W);
	col = -1;
	while (++col < WIN_W)
		col_angles[col] = atan2(col - (WIN_W - 1) * 0.5, cam_dist);
	return (col_angles);
}

double	*ft_get_tan_row_angles(double cam_dist)
{
	double	*tan_row_angles;
	int		row;

	tan_row_angles = (double*)ft_malloc(sizeof(double) * WIN_H);
	row = -1;
	while (++row < WIN_H)
		tan_row_angles[row] = fabs((row - (WIN_H - 1) * 0.5) / cam_dist);
	return (tan_row_angles);
}
