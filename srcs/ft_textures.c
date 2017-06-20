/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:41:43 by biremong          #+#    #+#             */
/*   Updated: 2017/05/20 11:21:35 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_load_textures(t_mlx *mlx, t_textures *txs, char *map_n)
{
	int	i;

	txs->walls = (t_tex**)ft_malloc(sizeof(t_tex*) * (txs->wl_tex_cnt + 1));
	txs->floors = (t_tex**)ft_malloc(sizeof(t_tex*) * (txs->fl_tex_cnt + 1));
	txs->ceils = (t_tex**)ft_malloc(sizeof(t_tex*) * (txs->cl_tex_cnt + 1));
	txs->sprites = (t_tex**)ft_malloc(sizeof(t_tex*) * (txs->spr_tex_cnt + 1));
	i = 0;
	while (++i < txs->wl_tex_cnt + 1)
		txs->walls[i] = ft_load_tex(mlx, i, "textures/walls/wall", map_n);
	i = 0;
	while (++i < txs->fl_tex_cnt + 1)
		txs->floors[i] = ft_load_tex(mlx, i, "textures/floors/floor", map_n);
	i = 0;
	while (++i < txs->cl_tex_cnt + 1)
		txs->ceils[i] = ft_load_tex(mlx, i, "textures/ceilings/ceiling", map_n);
	i = 0;
	while (++i < txs->spr_tex_cnt + 1)
		txs->sprites[i] = ft_load_tex(mlx, i, "textures/sprites/sprite", map_n);
}

char	*ft_get_tex_filename(char *path, int i, char *map_name)
{
	char	*filename;
	char	*i_str;

	i_str = ft_itoa(i);
	filename = (char*)ft_malloc(ft_strlen(path)
						+ ft_strlen(i_str)
						+ ft_strlen(map_name)
						+ 10);
	ft_strcpy(filename, "maps/");
	ft_strcat(filename, map_name);
	ft_strcat(filename, "/");
	ft_strcat(filename, path);
	ft_strcat(filename, i_str);
	ft_strcat(filename, ".xpm");
	free(i_str);
	return (filename);
}

t_tex	*ft_load_tex(t_mlx *mlx, int i, char *path, char *map_name)
{
	t_tex	*tex;
	char	*filename;
	int		w;
	int		h;
	int		dummy;

	tex = (t_tex*)ft_malloc(sizeof(t_tex));
	filename = ft_get_tex_filename(path, i, map_name);
	if (access(filename, F_OK) == -1)
		ft_error("Error: Texture File Missing");
	tex->img = mlx_xpm_file_to_image(mlx->mlx, filename, &w, &h);
	tex->w = w;
	tex->h = h;
	tex->ratio = (double)tex->w / tex->h;
	tex->img_str = mlx_get_data_addr(tex->img, &dummy, &dummy, &dummy);
	free(filename);
	return (tex);
}
