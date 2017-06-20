/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 20:36:20 by biremong          #+#    #+#             */
/*   Updated: 2017/05/19 20:50:29 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		ft_on_keypress(int keycode, void *param)
{
	t_globals	*glob;
	t_events	*events;

	glob = (t_globals*)param;
	events = glob->events;
	if (keycode == 0)
		events->l_r -= 1;
	else if (keycode == 2)
		events->l_r += 1;
	else if (keycode == 13)
		events->f_b += 1;
	else if (keycode == 1)
		events->f_b -= 1;
	else if (keycode == 124)
		events->pan += 1;
	else if (keycode == 123)
		events->pan -= 1;
	else if (keycode == 49 && !events->jump_start &&
			!events->crouching && !events->crouched)
		events->jump_start = mach_absolute_time();
	else if (keycode == 8 && !events->jump_start)
		events->crouching = -1;
	else if (keycode == 53)
		ft_on_exit(glob);
	return (0);
}

int		ft_on_keyrelease(int keycode, void *param)
{
	t_events *events;

	events = (t_events*)param;
	if (keycode == 0)
		events->l_r += 1;
	else if (keycode == 2)
		events->l_r -= 1;
	else if (keycode == 13)
		events->f_b -= 1;
	else if (keycode == 1)
		events->f_b += 1;
	else if (keycode == 124)
		events->pan -= 1;
	else if (keycode == 123)
		events->pan += 1;
	else if (keycode == 8 && !events->jump_start)
		events->crouching = 1;
	return (0);
}

int		ft_on_loop(void *param)
{
	t_globals	*glob;
	t_events	*events;
	t_camera	*cam;
	double		loop_secs;
	int			redraw;

	glob = (t_globals*)param;
	events = glob->events;
	cam = glob->cam;
	glob->total_secs = ft_elapsed_secs(glob->abs_start);
	loop_secs = glob->total_secs - glob->prev_total_secs;
	glob->prev_total_secs = glob->total_secs;
	redraw = 0;
	if (events->jump_start && (redraw = 1))
		cam->h = ft_jump_height(&events->jump_start);
	if (events->crouching && (redraw = 1))
		cam->h = ft_crouch_height(events, cam->h);
	if (events->pan && (redraw = 1))
		ft_update_angle(glob, TO_RAD(events->pan * cam->rot_speed));
	if ((events->l_r || events->f_b) && (redraw = 1))
		ft_update_pos(glob, events->l_r, events->f_b);
	if (redraw)
		ft_start_threads(glob, loop_secs);
	return (0);
}

int		ft_on_exit(void *param)
{
	t_globals *glob;

	glob = (t_globals*)param;
	ft_free_textures(glob);
	ft_free_maps(glob);
	ft_free_the_rest(glob);
	exit(0);
	return (0);
}

void	ft_set_hooks(t_globals *glob)
{
	mlx_do_key_autorepeatoff(glob->mlx->mlx);
	mlx_hook(glob->mlx->win, 2, 0, ft_on_keypress, glob);
	mlx_hook(glob->mlx->win, 3, 0, ft_on_keyrelease, glob->events);
	mlx_hook(glob->mlx->win, 17, 0, ft_on_exit, glob);
	mlx_loop_hook(glob->mlx->mlx, ft_on_loop, glob);
}
