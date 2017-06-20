/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_threads.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 20:39:13 by biremong          #+#    #+#             */
/*   Updated: 2017/05/20 16:30:05 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_start_threads(t_globals *glob, double loop_secs)
{
	int		i;

	glob->thread_job = 0;
	i = -1;
	while (++i < THREAD_CNT)
		pthread_create(&glob->threads[i], NULL, ft_draw_frame, glob);
	i = -1;
	while (++i < THREAD_CNT)
		pthread_join(glob->threads[i], NULL);
	ft_draw_sprites(glob);
	mlx_clear_window(glob->mlx->mlx, glob->mlx->win);
	mlx_put_image_to_window(
			glob->mlx->mlx, glob->mlx->win, glob->mlx->img, 0, 0);
	ft_update_speeds(glob->cam, loop_secs);
}

void	*ft_draw_frame(void *param)
{
	t_globals	*glob;
	double		ref_angle;
	double		ray_angle;
	int			col;
	t_hit		hit;

	glob = (t_globals*)param;
	while (glob->thread_job < WIN_W)
	{
		col = glob->thread_job++;
		ref_angle = glob->col_angles[col];
		ray_angle = ft_add_angles(glob->cam->angle, ref_angle);
		hit = ft_get_hit(glob, ray_angle, glob->sq_size);
		hit.norm_dist = hit.dist * cos(ref_angle);
		if (col < WIN_W)
			glob->z_buf[col] = hit.dist;
		ft_draw_col(glob, &hit, col);
	}
	return (NULL);
}
