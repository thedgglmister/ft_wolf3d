/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 20:39:13 by biremong          #+#    #+#             */
/*   Updated: 2017/05/19 21:00:19 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

double	ft_elapsed_secs(uint64_t start)
{
	uint64_t							end;
	static mach_timebase_info_data_t	time_base;
	uint64_t							nsecs;
	double								secs;

	if (time_base.denom == 0)
		mach_timebase_info(&time_base);
	end = mach_absolute_time();
	nsecs = (double)((end - start) * time_base.numer) / time_base.denom;
	secs = (double)nsecs / 1000000000;
	return (secs);
}

void	ft_update_speeds(t_camera *cam, double loop_secs)
{
	cam->move_speed = MOVE_SPEED * loop_secs;
	cam->rot_speed = ROT_SPEED * loop_secs;
}
