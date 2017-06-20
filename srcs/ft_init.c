/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:41:43 by biremong          #+#    #+#             */
/*   Updated: 2017/05/20 16:38:24 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_mlx		*ft_init_mlx(int fd)
{
	t_mlx	*mlx;
	char	*map_name;

	mlx = (t_mlx*)ft_malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	map_name = ft_parse_str(fd, "MAP NAME:");
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, map_name);
	free(map_name);
	mlx->img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	mlx->img_str = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->ls, &mlx->end);
	return (mlx);
}

t_camera	*ft_init_camera(void)
{
	t_camera	*cam;

	cam = (t_camera*)ft_malloc(sizeof(t_camera));
	cam->x = START_X;
	cam->y = START_Y;
	cam->angle = ft_add_angles(START_A, 0);
	cam->dist = (WIN_W * 0.5) / tan(FOV * 0.5);
	cam->h = PLAYER_H;
	return (cam);
}

t_events	*ft_init_events(void)
{
	t_events	*events;

	events = (t_events*)ft_malloc(sizeof(t_events));
	ft_bzero(events, sizeof(t_events));
	return (events);
}
