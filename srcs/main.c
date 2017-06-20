/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:41:43 by biremong          #+#    #+#             */
/*   Updated: 2017/05/22 12:17:19 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	main(int ac, char **av)
{
	t_globals	glob;
	int			fd;

	if (ac != 2)
		ft_error("Usage: ./wolf3d map_name");
	fd = ft_open_file(av[1]);
	glob.mlx = ft_init_mlx(fd);
	glob.cam = ft_init_camera();
	glob.events = ft_init_events();
	ft_load_maps(fd, &glob);
	ft_load_textures(glob.mlx, glob.texs, av[1]);
	ft_load_sprites(&glob, glob.texs->sprites, fd, -1);
	ft_close(fd);
	glob.cam->x *= glob.sq_size;
	glob.cam->y *= glob.sq_size;
	glob.col_angles = ft_get_col_angles(glob.cam->dist);
	glob.tan_row_angles = ft_get_tan_row_angles(glob.cam->dist);
	ft_set_hooks(&glob);
	glob.abs_start = mach_absolute_time();
	ft_start_threads(&glob, 0);
	mlx_loop(glob.mlx->mlx);
	return (0);
}

int	ft_open_file(char *map_name)
{
	int		fd;
	char	*filename;

	filename = (char*)ft_malloc(2 * ft_strlen(map_name) + 10);
	ft_strcpy(filename, "maps/");
	ft_strcat(filename, map_name);
	ft_strcat(filename, "/");
	ft_strcat(filename, map_name);
	ft_strcat(filename, ".wlf");
	fd = ft_open(filename);
	free(filename);
	return (fd);
}
