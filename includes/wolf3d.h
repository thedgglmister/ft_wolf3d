/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: biremong <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 16:09:21 by biremong          #+#    #+#             */
/*   Updated: 2017/05/22 11:59:56 by biremong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H

# define WOLF3D_H

# include <math.h>
# include <pthread.h>
# include <mach/mach_time.h>
# include "mlx.h"
# include "libft.h"

# define TO_RAD(deg) (deg * M_PI / 180)

# define WIN_W 1000
# define WIN_H 700
# define THREAD_CNT 32

# define START_X 1.5
# define START_Y 1.5
# define START_A TO_RAD(45)
# define FOV TO_RAD(66)
# define PLAYER_H 60

# define MOVE_SPEED 250
# define ROT_SPEED 80
# define GRAVITY -190
# define JUMP_VELOCITY 200

typedef struct	s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_str;
	int		bpp;
	int		ls;
	int		end;
}				t_mlx;

typedef struct	s_camera
{
	double	x;
	double	y;
	double	angle;
	double	dist;
	double	h;
	double	move_speed;
	double	rot_speed;
}				t_camera;

typedef struct	s_hit
{
	int		n;
	double	x;
	double	y;
	double	dist;
	double	norm_dist;
	char	side;
	double	mod;
	int		wall_h;
	int		start_row;
	int		end_row;
}				t_hit;

typedef struct	s_events
{
	int			l_r;
	int			f_b;
	int			pan;
	int			crouching;
	int			crouched;
	uint64_t	jump_start;
}				t_events;

typedef struct	s_tex
{
	void	*img;
	char	*img_str;
	int		h;
	int		w;
	double	x;
	double	y;
	double	ratio;
}				t_tex;

typedef struct	s_sprite
{
	t_tex	*tex;
	double	h;
	double	w;
	double	base_h;
	double	x;
	double	y;
	double	r;
	double	dx;
	double	dy;
	double	dist;
	double	norm_dist;
	double	para_dist;
	double	angle;
	double	ref_angle;
	double	draw_h;
	double	draw_w;
	double	draw_b;
	double	mid_col;
	int		start_col;
	int		start_row;
}				t_sprite;

typedef struct	s_textures
{
	int		wl_tex_cnt;
	int		fl_tex_cnt;
	int		cl_tex_cnt;
	int		spr_tex_cnt;
	t_tex	**walls;
	t_tex	**floors;
	t_tex	**ceils;
	t_tex	**sprites;
}				t_textures;

typedef struct	s_maps
{
	int	w;
	int	h;
	int **walls;
	int **floors;
	int **ceils;
}				t_maps;

typedef struct	s_globals
{
	t_mlx		*mlx;
	t_camera	*cam;
	t_events	*events;
	t_textures	*texs;
	int			spr_cnt;
	int			wall_h;
	int			sq_size;
	t_sprite	**sprites;
	t_maps		*maps;
	double		*col_angles;
	double		*tan_row_angles;
	pthread_t	threads[THREAD_CNT];
	double		z_buf[WIN_W];
	int			thread_job;
	uint64_t	abs_start;
	double		total_secs;
	double		prev_total_secs;
	int			sky_flag;
}				t_globals;

/*
**main.c
*/
int				ft_open_file(char *map_name);

/*
**ft_time.c
*/
double			ft_elapsed_secs(uint64_t start);
void			ft_update_speeds(t_camera *cam, double loop_secs);

/*
**ft_threads.c
*/
void			ft_start_threads(t_globals *glob, double loop_secs);
void			*ft_draw_frame(void *param);

/*
**ft_textures.c
*/
void			ft_load_textures(t_mlx *mlx, t_textures *txs, char *map_n);
char			*ft_get_tex_filename(char *path, int i, char *map_name);
t_tex			*ft_load_tex(t_mlx *mlx, int i, char *path, char *map_name);

/*
**ft_sprites.c
*/
void			ft_draw_sprites(t_globals *glob);
void			ft_draw_sprite_col(
					t_mlx *mlx, t_sprite *sprite, int w, int col);
void			ft_get_sprite_stats(
					t_sprite **sprites, t_camera *cam, int spr_cnt);
void			ft_sort_sprites(t_sprite **sprites, int spr_cnt);

/*
**ft_parse.c
*/
void			ft_skip_empty_line(int fd);
char			*ft_parse_str(int fd, char *category);
void			ft_parse_vec(int fd, char *category, double *x, double *y);
double			ft_parse_val(int fd, char *category);

/*
**ft_move.c
*/
void			ft_update_pos(t_globals *glob, int l_r, int f_b);
void			ft_update_angle(t_globals *glob, double d_angle);
double			ft_add_angles(double start, double change);

/*
**ft_maps.c
*/
void			ft_load_sprites(
					t_globals *glob, t_tex **spr_texs, int fd, int i);
void			ft_load_maps(int fd, t_globals *glob);
int				ft_validate_map_row(
					char **split, t_maps *maps, int tex_cnt, int row);
int				**ft_load_map(int fd, t_maps *maps, int tex_cnt);
void			ft_get_map_info(int fd, t_maps *maps, t_globals *glob);

/*
**ft_jump.c
*/
double			ft_jump_height(uint64_t *jump_start);
double			ft_crouch_height(t_events *events, double cam_height);

/*
**ft_init.c
*/
t_mlx			*ft_init_mlx(int fd);
t_camera		*ft_init_camera(void);
t_events		*ft_init_events(void);

/*
**ft_hooks.c
*/
int				ft_on_keypress(int keycode, void *param);
int				ft_on_keyrelease(int keycode, void *param);
int				ft_on_loop(void *param);
int				ft_on_exit(void *param);
void			ft_set_hooks(t_globals *glob);

/*
**ft_hits.c
*/
t_hit			ft_get_hit(t_globals *glob, double ray_angle, int sq_size);
void			ft_get_ver_hit(
					t_globals *glob, t_hit *hit, double tan_ray, int sq_size);
void			ft_get_hor_hit(
					t_globals *glob, t_hit *hit, double tan_ray, int sq_size);
void			ft_get_hit_info(
					t_maps *maps, t_camera *cam, t_hit *hit, int sq_size);

/*
**ft_free.c
*/
void			ft_free_textures(t_globals *glob);
void			ft_free_maps(t_globals *glob);
void			ft_free_the_rest(t_globals *glob);

/*
**ft_draw.c
*/
void			ft_draw_col(t_globals *glob, t_hit *hit, int col);
void			ft_draw_wall(t_globals *glob, t_hit *hit, int *row, int *img_i);
void			ft_draw_flcl(t_globals *glob, t_hit *hit, int *row, int *img_i);
int				ft_flcl_texel(
					t_globals *glob, t_hit *hit, int row, int ceil_flag);
int				ft_flcl_color(
					t_globals *glob, double flcl_x, double flcl_y, int cl_flg);

/*
**ft_darken.c
*/
void			ft_darken(int *color);

/*
**ft_collision.c
*/
int				ft_spr_collision(
					t_globals *glob, double *dx, double *dy);
int				ft_spr_coll_check(
					t_camera *cam, t_sprite *spr, double *dx, double *dy);
int				ft_wall_collision_x(t_globals *glob, double *dx);
int				ft_wall_collision_y(t_globals *glob, double *dy);

/*
**ft_angles.c
*/
double			*ft_get_col_angles(double cam_dist);
double			*ft_get_tan_row_angles(double cam_dist);

#endif
