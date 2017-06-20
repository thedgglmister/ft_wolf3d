/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hits.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 20:24:36 by biremong          #+#    #+#             */
/*   Updated: 2017/05/20 16:35:52 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_hit	ft_get_hit(t_globals *glob, double ray_angle, int sq_size)
{
	t_hit	ver_hit;
	t_hit	hor_hit;
	double	tan_ray;

	ver_hit.side = ray_angle < M_PI_2 || ray_angle > M_PI + M_PI_2 ? 'l' : 'r';
	hor_hit.side = ray_angle < M_PI ? 't' : 'b';
	tan_ray = tan(ray_angle);
	ft_get_ver_hit(glob, &ver_hit, tan_ray, sq_size);
	ft_get_hor_hit(glob, &hor_hit, tan_ray, sq_size);
	if (ver_hit.n < 0 || (hor_hit.n > 0 && hor_hit.dist < ver_hit.dist))
		return (hor_hit);
	else
		return (ver_hit);
}

void	ft_get_ver_hit(t_globals *glob, t_hit *hit, double tan_ray, int sq_size)
{
	double	dist_x;
	double	dx;
	double	dy;

	if (hit->side == 'l')
		hit->x = ceil(glob->cam->x / sq_size) * sq_size;
	else
		hit->x = floor(glob->cam->x / sq_size) * sq_size;
	dist_x = hit->x - glob->cam->x;
	hit->y = glob->cam->y + dist_x * tan_ray;
	ft_get_hit_info(glob->maps, glob->cam, hit, sq_size);
	dx = (hit->side == 'l' ? sq_size : -sq_size);
	dy = dx * tan_ray;
	while (!hit->n)
	{
		hit->x += dx;
		hit->y += dy;
		ft_get_hit_info(glob->maps, glob->cam, hit, sq_size);
	}
}

void	ft_get_hor_hit(t_globals *glob, t_hit *hit, double tan_ray, int sq_size)
{
	double	dist_y;
	double	dx;
	double	dy;

	if (hit->side == 't')
		hit->y = ceil(glob->cam->y / sq_size) * sq_size;
	else
		hit->y = floor(glob->cam->y / sq_size) * sq_size;
	dist_y = hit->y - glob->cam->y;
	hit->x = glob->cam->x + dist_y / tan_ray;
	ft_get_hit_info(glob->maps, glob->cam, hit, sq_size);
	dy = (hit->side == 't' ? sq_size : -sq_size);
	dx = dy / tan_ray;
	while (!hit->n)
	{
		hit->y += dy;
		hit->x += dx;
		ft_get_hit_info(glob->maps, glob->cam, hit, sq_size);
	}
}

void	ft_get_hit_info(t_maps *maps, t_camera *cam, t_hit *hit, int sq_size)
{
	int	grid_x;
	int	grid_y;

	grid_y = (int)hit->y / sq_size;
	grid_x = (int)hit->x / sq_size;
	if (hit->side == 'b')
		grid_y--;
	if (hit->side == 'r')
		grid_x--;
	if (grid_x < 0 || grid_x >= maps->w || grid_y < 0 || grid_y >= maps->h)
		hit->n = -1;
	else
	{
		hit->n = maps->walls[grid_y][grid_x];
		if (hit->n)
			hit->dist = hypot(hit->x - cam->x, hit->y - cam->y);
		if (hit->side == 'l' || hit->side == 'r')
			hit->mod = fmod(hit->y / sq_size, 1);
		else
			hit->mod = fmod(hit->x / sq_size, 1);
	}
}
