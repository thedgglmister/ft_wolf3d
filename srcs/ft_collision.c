/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_collision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 20:36:20 by biremong          #+#    #+#             */
/*   Updated: 2017/05/22 12:00:10 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_spr_collision(t_globals *glob, double *dx, double *dy)
{
	t_sprite	*spr;
	int			i;
	int			collision;

	collision = 1;
	i = -1;
	while (++i < glob->spr_cnt)
	{
		spr = glob->sprites[i];
		if (spr->r > 10 && spr->r + 20 > spr->dist)
			collision *= ft_spr_coll_check(glob->cam, spr, dx, dy);
	}
	return (collision);
}

int		ft_spr_coll_check(t_camera *cam, t_sprite *spr, double *dx, double *dy)
{
	double	new_x;
	double	new_y;
	double	new_dist;

	spr->dx -= *dx;
	spr->dy -= *dy;
	new_dist = sqrt(spr->dx * spr->dx + spr->dy * spr->dy);
	if (new_dist < spr->r)
	{
		spr->dx += *dx * 0.5;
		spr->dy += *dy * 0.5;
		new_dist = sqrt(spr->dx * spr->dx + spr->dy * spr->dy);
		spr->dx = spr->dx / new_dist * spr->r;
		spr->dy = spr->dy / new_dist * spr->r;
		new_x = spr->x - spr->dx;
		new_y = spr->y - spr->dy;
		*dx = new_x - cam->x;
		*dy = new_y - cam->y;
		return (0);
	}
	return (1);
}

int		ft_wall_collision_x(t_globals *glob, double *dx)
{
	double	new_x;
	int		grid_x;
	int		grid_y;
	int		pad;
	int		extra;

	pad = (*dx < 0 ? -10 : 10);
	extra = (*dx < 0 ? glob->sq_size : 0);
	new_x = glob->cam->x + *dx + pad;
	grid_x = floor(new_x / glob->sq_size);
	grid_y = floor(glob->cam->y / glob->sq_size);
	if (glob->maps->walls[grid_y][grid_x] == 0)
		return (0);
	*dx -= fmod(new_x, glob->sq_size);
	*dx += extra;
	return (1);
}

int		ft_wall_collision_y(t_globals *glob, double *dy)
{
	double	new_y;
	int		grid_x;
	int		grid_y;
	int		pad;
	int		extra;

	pad = (*dy < 0 ? -10 : 10);
	extra = (*dy < 0 ? glob->sq_size : 0);
	new_y = glob->cam->y + *dy + pad;
	grid_x = floor(glob->cam->x / glob->sq_size);
	grid_y = floor(new_y / glob->sq_size);
	if (glob->maps->walls[grid_y][grid_x] == 0)
		return (0);
	*dy -= fmod(new_y, glob->sq_size);
	*dy += extra;
	return (1);
}
