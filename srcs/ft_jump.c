/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_jump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/19 20:50:56 by biremong          #+#    #+#             */
/*   Updated: 2017/05/19 20:51:43 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double	ft_jump_height(uint64_t *jump_start)
{
	double height;
	double secs;

	secs = ft_elapsed_secs(*jump_start);
	height = PLAYER_H;
	height += JUMP_VELOCITY * secs;
	height += GRAVITY * secs * secs;
	if (height < PLAYER_H)
	{
		height = PLAYER_H;
		*jump_start = 0;
	}
	return (height);
}

double	ft_crouch_height(t_events *events, double cam_height)
{
	double height;

	height = cam_height;
	if (events->crouching > 0 && height >= PLAYER_H)
		events->crouching = 0;
	else if (events->crouching > 0)
	{
		events->crouched = 0;
		height += 3;
	}
	else if (events->crouching < 0 && height <= PLAYER_H / 2)
	{
		events->crouched = 1;
		events->crouching = 0;
	}
	else if (events->crouching < 0)
	{
		events->crouched = 0;
		height -= 3;
	}
	return (height);
}
