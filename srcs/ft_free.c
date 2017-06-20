/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 20:47:41 by biremong          #+#    #+#             */
/*   Updated: 2017/05/19 20:48:03 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_free_textures(t_globals *glob)
{
	int i;

	i = 0;
	while (++i < glob->texs->wl_tex_cnt + 1)
	{
		mlx_destroy_image(glob->mlx->mlx, glob->texs->walls[i]->img);
		free(glob->texs->walls[i]);
	}
	free(glob->texs->walls);
	i = 0;
	while (++i < glob->texs->fl_tex_cnt + 1)
	{
		mlx_destroy_image(glob->mlx->mlx, glob->texs->floors[i]->img);
		free(glob->texs->floors[i]);
	}
	free(glob->texs->floors);
	i = 0;
	while (++i < glob->texs->cl_tex_cnt + 1)
	{
		mlx_destroy_image(glob->mlx->mlx, glob->texs->ceils[i]->img);
		free(glob->texs->ceils[i]);
	}
	free(glob->texs->ceils);
}

void	ft_free_maps(t_globals *glob)
{
	int i;

	i = -1;
	while (++i < glob->maps->h)
		free(glob->maps->walls[i]);
	free(glob->maps->walls);
	i = -1;
	while (++i < glob->maps->h)
		free(glob->maps->floors[i]);
	free(glob->maps->floors);
	i = -1;
	while (++i < glob->maps->h)
		free(glob->maps->ceils[i]);
	free(glob->maps->ceils);
	free(glob->maps);
}

void	ft_free_the_rest(t_globals *glob)
{
	int i;

	i = -1;
	while (++i < glob->spr_cnt)
		free(glob->sprites[i]);
	i = 0;
	while (++i < glob->texs->spr_tex_cnt + 1)
	{
		mlx_destroy_image(glob->mlx->mlx, glob->texs->sprites[i]->img);
		free(glob->texs->sprites[i]);
	}
	mlx_destroy_image(glob->mlx->mlx, glob->mlx->img);
	free(glob->sprites);
	free(glob->texs->sprites);
	free(glob->texs);
	free(glob->col_angles);
	free(glob->tan_row_angles);
	free(glob->cam);
	free(glob->events);
	free(glob->mlx);
}
