/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 20:39:13 by biremong          #+#    #+#             */
/*   Updated: 2017/05/22 12:03:53 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_draw_col(t_globals *glob, t_hit *hit, int col)
{
	double	st_offst;
	double	end_offset;
	int		row;
	int		img_i;

	st_offst = (glob->wall_h - glob->cam->h) / hit->norm_dist * glob->cam->dist;
	end_offset = glob->cam->h / hit->norm_dist * glob->cam->dist;
	hit->start_row = WIN_H * 0.5 - st_offst;
	hit->end_row = WIN_H * 0.5 + end_offset;
	hit->wall_h = hit->end_row - hit->start_row;
	row = 0;
	img_i = col;
	ft_draw_flcl(glob, hit, &row, &img_i);
	ft_draw_wall(glob, hit, &row, &img_i);
	ft_draw_flcl(glob, hit, &row, &img_i);
}

void	ft_draw_wall(t_globals *glob, t_hit *hit, int *row, int *img_i)
{
	t_tex	*tex;
	int		color;
	double	tex_y_increment;
	double	tex_x;
	double	tex_y;

	tex = glob->texs->walls[hit->n];
	tex_y_increment = (double)tex->h / hit->wall_h;
	tex_x = tex->w * hit->mod;
	tex_y = (*row - hit->start_row) * tex_y_increment;
	while (*row < hit->end_row && *row < WIN_H)
	{
		color = ((int*)(tex->img_str))[tex->w * (int)tex_y + (int)tex_x];
		if (hit->side == 't' || hit->side == 'b')
			ft_darken(&color);
		((int*)(glob->mlx->img_str))[*img_i] = color;
		tex_y += tex_y_increment;
		*img_i += WIN_W;
		(*row)++;
	}
}

void	ft_draw_flcl(t_globals *glob, t_hit *hit, int *row, int *img_i)
{
	int		color;
	int		limit;
	int		ceil_flag;
	int		sky_shade;

	ceil_flag = (*row < WIN_H * 0.5);
	limit = (ceil_flag ? hit->start_row : WIN_H);
	while (*row < limit)
	{
		if (ceil_flag && glob->sky_flag)
		{
			sky_shade = *row / (WIN_H / 120);
			color = 0x5080E0 + (sky_shade < 32 ? sky_shade * 0x010101 :
								31 * 0x010101 + (sky_shade - 31) * 0x010100);
		}
		else
		{
			color = ft_flcl_texel(glob, hit, *row, ceil_flag);
			if (ceil_flag)
				ft_darken(&color);
		}
		((int*)(glob->mlx->img_str))[*img_i] = color;
		*img_i += WIN_W;
		(*row)++;
	}
}

int		ft_flcl_texel(t_globals *glob, t_hit *hit, int row, int ceil_flag)
{
	double	dist;
	double	scalar;
	double	flcl_x;
	double	flcl_y;

	if (ceil_flag)
		dist = (glob->wall_h - glob->cam->h) / glob->tan_row_angles[row];
	else
		dist = glob->cam->h / glob->tan_row_angles[row];
	scalar = dist / hit->norm_dist;
	flcl_x = scalar * (hit->x - glob->cam->x) + glob->cam->x;
	flcl_y = scalar * (hit->y - glob->cam->y) + glob->cam->y;
	return (ft_flcl_color(glob, flcl_x, flcl_y, ceil_flag));
}

int		ft_flcl_color(t_globals *glob, double flcl_x, double flcl_y, int cl_flg)
{
	t_tex	*tex;
	int		tx_i;
	int		tex_x;
	int		tex_y;

	tex_y = (int)flcl_y / glob->sq_size;
	tex_x = (int)flcl_x / glob->sq_size;
	if (tex_y < 0 || tex_y >= glob->maps->h ||
			tex_x < 0 || tex_x >= glob->maps->w)
		return (0);
	if (cl_flg)
	{
		tx_i = glob->maps->ceils[tex_y][tex_x];
		tex = (tx_i ? glob->texs->ceils[tx_i] : glob->texs->ceils[tx_i + 1]);
	}
	else
	{
		tx_i = glob->maps->floors[tex_y][tex_x];
		tex = (tx_i ? glob->texs->floors[tx_i] : glob->texs->floors[tx_i + 1]);
	}
	if (!tex)
		return (0);
	tex_x = fmod(flcl_x, glob->sq_size) / glob->sq_size * tex->w;
	tex_y = fmod(flcl_y, glob->sq_size) / glob->sq_size * tex->h;
	return (((int*)(tex->img_str))[tex->w * tex_y + tex_x]);
}
