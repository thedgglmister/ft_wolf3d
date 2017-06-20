/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maps.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:41:43 by biremong          #+#    #+#             */
/*   Updated: 2017/05/22 12:20:21 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		**ft_load_map(int fd, t_maps *maps, int tex_cnt)
{
	int		**map;
	char	*line;
	char	**split;
	int		i;
	int		j;

	map = (int**)ft_malloc(sizeof(int*) * maps->h);
	i = -1;
	while (++i < maps->h)
	{
		ft_gnl(fd, &line);
		split = ft_strsplit(line, ' ');
		if (!ft_validate_map_row(split, maps, tex_cnt, i))
			ft_error("Error Loading Map");
		map[i] = (int*)ft_malloc(sizeof(int) * maps->w);
		j = -1;
		while (++j < maps->w)
			map[i][j] = ft_atoi(split[j]);
		ft_arrdel2(split);
		free(line);
	}
	return (map);
}

int		ft_validate_map_row(char **split, t_maps *maps, int tex_cnt, int row)
{
	int			i;
	int			val;
	static int	wall_flag = 0;

	if (ft_arrlen2(split) != maps->w)
		return (0);
	i = -1;
	while (++i < maps->w)
	{
		val = ft_atoi(split[i]);
		if (val < 0 || val > tex_cnt)
			return (0);
		if (wall_flag < maps->h)
		{
			if ((row == 0 || row == maps->h - 1) && val == 0)
				return (0);
			if ((i == 0 || i == maps->w - 1) && val == 0)
				return (0);
		}
	}
	wall_flag++;
	return (1);
}

void	ft_load_maps(int fd, t_globals *glob)
{
	t_maps		*maps;
	t_textures	*texs;

	glob->maps = (t_maps*)ft_malloc(sizeof(t_maps));
	glob->texs = (t_textures*)ft_malloc(sizeof(t_textures));
	maps = glob->maps;
	texs = glob->texs;
	ft_skip_empty_line(fd);
	ft_get_map_info(fd, maps, glob);
	ft_skip_empty_line(fd);
	texs->wl_tex_cnt = ft_parse_val(fd, "WALL TEXTURE COUNT:");
	ft_skip_empty_line(fd);
	maps->walls = ft_load_map(fd, maps, texs->wl_tex_cnt);
	ft_skip_empty_line(fd);
	texs->fl_tex_cnt = ft_parse_val(fd, "FLOOR TEXTURE COUNT:");
	ft_skip_empty_line(fd);
	maps->floors = ft_load_map(fd, maps, texs->fl_tex_cnt);
	ft_skip_empty_line(fd);
	texs->cl_tex_cnt = ft_parse_val(fd, "CEILING TEXTURE COUNT:");
	ft_skip_empty_line(fd);
	maps->ceils = ft_load_map(fd, maps, texs->cl_tex_cnt);
	ft_skip_empty_line(fd);
	texs->spr_tex_cnt = ft_parse_val(fd, "SPRITE TEXTURE COUNT:");
}

void	ft_get_map_info(int fd, t_maps *maps, t_globals *glob)
{
	char *sky;

	maps->w = ft_parse_val(fd, "MAP WIDTH:");
	ft_skip_empty_line(fd);
	maps->h = ft_parse_val(fd, "MAP HEIGHT:");
	ft_skip_empty_line(fd);
	glob->wall_h = ft_parse_val(fd, "WALL HEIGHT:");
	if (glob->wall_h < PLAYER_H + 55)
		ft_error("Error: Wall Height Too Low");
	ft_skip_empty_line(fd);
	glob->sq_size = ft_parse_val(fd, "SQUARE SIZE:");
	ft_skip_empty_line(fd);
	sky = ft_parse_str(fd, "SKY:");
	ft_str_tolower(&sky);
	glob->sky_flag = ft_strequ(sky, "on") || ft_strequ(sky, "1");
}

void	ft_load_sprites(t_globals *glob, t_tex **spr_texs, int fd, int i)
{
	int			tex_number;
	t_sprite	*spr;

	ft_skip_empty_line(fd);
	glob->spr_cnt = ft_parse_val(fd, "SPRITE COUNT:");
	glob->sprites = (t_sprite**)ft_malloc(sizeof(t_sprite*) * glob->spr_cnt);
	while (++i < glob->spr_cnt)
	{
		glob->sprites[i] = (t_sprite*)ft_malloc(sizeof(t_sprite));
		spr = glob->sprites[i];
		ft_skip_empty_line(fd);
		ft_parse_str(fd, "SPRITE:");
		tex_number = ft_parse_val(fd, "\tTEXTURE:");
		if (tex_number < 1 || tex_number > glob->texs->spr_tex_cnt)
			ft_error("Invalid Sprite Texture #");
		spr->tex = spr_texs[tex_number];
		ft_parse_vec(fd, "\tPOSITION:", &(spr->x), &(spr->y));
		spr->x *= glob->sq_size;
		spr->y *= glob->sq_size;
		spr->h = ft_parse_val(fd, "\tHEIGHT:");
		spr->w = spr->tex->ratio * spr->h;
		spr->base_h = ft_parse_val(fd, "\tBASE HEIGHT:");
		spr->r = ft_parse_val(fd, "\tCOLLISION RADIUS:");
	}
}
