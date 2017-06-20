/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 20:36:20 by biremong          #+#    #+#             */
/*   Updated: 2017/05/19 20:53:23 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_update_pos(t_globals *glob, int l_r, int f_b)
{
	double	rel_move_angle;
	double	move_angle;
	double	dx;
	double	dy;
	int		wall_col;

	rel_move_angle = atan2(l_r, f_b);
	move_angle = ft_add_angles(glob->cam->angle, rel_move_angle);
	dx = glob->cam->move_speed * cos(move_angle);
	dy = glob->cam->move_speed * sin(move_angle);
	ft_spr_collision(glob, &dx, &dy);
	wall_col = 0;
	wall_col += ft_wall_collision_x(glob, &dx);
	wall_col += ft_wall_collision_y(glob, &dy);
	if (wall_col && (ft_spr_collision(glob, &dx, &dy) == 0))
		return ;
	glob->cam->x += dx;
	glob->cam->y += dy;
}

void	ft_update_angle(t_globals *glob, double d_angle)
{
	glob->cam->angle = ft_add_angles(glob->cam->angle, d_angle);
}

double	ft_add_angles(double start, double change)
{
	double new_angle;

	new_angle = fmod(start + change, M_PI + M_PI);
	if (new_angle < 0)
		new_angle += M_PI + M_PI;
	return (new_angle);
}
