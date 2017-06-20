/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 12:41:43 by biremong          #+#    #+#             */
/*   Updated: 2017/05/19 21:12:30 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_draw_sprites(t_globals *glob)
{
	t_sprite	*spr;
	int			spr_i;
	int			w;
	int			col;
	double		offset;

	ft_get_sprite_stats(glob->sprites, glob->cam, glob->spr_cnt);
	ft_sort_sprites(glob->sprites, glob->spr_cnt);
	spr_i = -1;
	while (++spr_i < glob->spr_cnt)
	{
		spr = glob->sprites[spr_i];
		if (spr->norm_dist < 0 || spr->start_col > WIN_W)
			continue ;
		offset = glob->cam->h / spr->norm_dist * glob->cam->dist;
		spr->start_row = WIN_H * 0.5 + offset - spr->draw_h - spr->draw_b;
		w = (spr->start_col < 0 ? -spr->start_col : 0) - 1;
		col = (spr->start_col < 0 ? 0 : spr->start_col) - 1;
		while (++w < spr->draw_w && ++col < WIN_W)
			if (spr->dist < glob->z_buf[col])
				ft_draw_sprite_col(glob->mlx, spr, w, col);
	}
}

void	ft_draw_sprite_col(t_mlx *mlx, t_sprite *sprite, int w, int col)
{
	int				h;
	int				row;
	int				tex_x;
	int				tex_y;
	unsigned int	color;

	h = (sprite->start_row < 0 ? -sprite->start_row : 0) - 1;
	row = (sprite->start_row < 0 ? 0 : sprite->start_row) - 1;
	tex_x = w / sprite->draw_w * sprite->tex->w;
	while (++h < sprite->draw_h && ++row < WIN_H)
	{
		tex_y = h / sprite->draw_h * sprite->tex->h;
		color = ((int*)(sprite->tex->img_str))[tex_y * sprite->tex->w + tex_x];
		if (color < 0xFF000000)
			((int*)(mlx->img_str))[row * WIN_W + col] = color;
	}
}

void	ft_get_sprite_stats(t_sprite **sprites, t_camera *cam, int spr_cnt)
{
	t_sprite	*spr;
	int			spr_i;

	spr_i = -1;
	while (++spr_i < spr_cnt)
	{
		spr = sprites[spr_i];
		spr->dx = spr->x - cam->x;
		spr->dy = spr->y - cam->y;
		spr->angle = atan2(spr->dy, spr->dx);
		if (fabs(spr->angle) == M_PI_2)
			spr->dist = fabs(spr->dy);
		else
			spr->dist = spr->dx / cos(spr->angle);
		spr->ref_angle = ft_add_angles(spr->angle - cam->angle, 0);
		if (spr->ref_angle > M_PI)
			spr->ref_angle -= M_PI + M_PI;
		spr->norm_dist = spr->dist * cos(spr->ref_angle);
		spr->draw_h = spr->h / spr->norm_dist * cam->dist;
		spr->draw_w = spr->tex->ratio * spr->draw_h;
		spr->draw_b = spr->base_h / spr->norm_dist * cam->dist;
		spr->mid_col = tan(spr->ref_angle) * cam->dist + (WIN_W * 0.5);
		spr->start_col = spr->mid_col - (spr->draw_w * 0.5);
	}
}

void	ft_sort_sprites(t_sprite **sprites, int spr_cnt)
{
	t_sprite	*temp_sprite;
	int			i;
	int			j;

	i = 1;
	while (i < spr_cnt)
	{
		j = i;
		while (j > 0 && sprites[j]->dist > sprites[j - 1]->dist)
		{
			temp_sprite = sprites[j];
			sprites[j] = sprites[j - 1];
			sprites[j - 1] = temp_sprite;
			j--;
		}
		i++;
	}
}
