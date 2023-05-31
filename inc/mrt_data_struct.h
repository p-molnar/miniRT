/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mrt_data_struct.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:06:43 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/31 13:17:06 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_DATA_STRUCT_H
# define MRT_DATA_STRUCT_H

# include <MLX42.h>
# include <libft.h>
# include <mrt_macros.h>

// typedef struct s_color
// {
// 	unsigned int	r;
// 	unsigned int	g;
// 	unsigned int	b;
// }	t_color;

// typedef struct s_coord_3d
// {
// 	int	x;
// 	int	y;
// 	int	z;
// }	t_coord_3d;

// typedef struct s_cam
// {
// 	int				type;
// 	t_coord_3d		coord;
// 	t_coord_3d		norm_vec;
// 	unsigned int	fov;
// }	t_cam;

// typedef struct s_amb_light
// {
// 	int				type;
// 	unsigned int	intensity;
// 	t_color			color;
// }	t_amb_light;

// typedef struct s_sphere
// {
// 	int				type;
// 	t_coord_3d		coord;
// 	int				diamtr;
// 	t_color			color;
// }	t_sphere;

// typedef struct s_plane
// {
// 	int				type;
// 	t_coord_3d		coord;
// 	t_coord_3d		norm_vec;
// 	t_color			color;
// }	t_plane;

// typedef struct s_cylinder
// {
// 	int				type;
// 	t_coord_3d		coord;
// 	t_coord_3d		norm_vec;
// 	int				diamtr;
// 	int				height;
// 	t_color			color;
// }	t_cylinder;

// typedef struct s_light
// {
// 	int				type;
// 	t_coord_3d		pos;
// 	unsigned int	intensity;
// 	t_color			color;
// }	t_light;

typedef int			t_color;
typedef long double	t_coord3;
typedef long double	t_coord4;
typedef long double	t_mx4;
typedef long double	t_mx3;

typedef struct s_mx
{
	long double	*m;
	int			r;
	int			c;
}	t_mx;

typedef struct s_vec
{
	long double		len;
	t_coord3		dir[COORD_SIZE];
}					t_vec3;

typedef struct s_scn_el
{
	int				type;
	t_coord3		coord[COORD_SIZE];
	t_coord3		tg_coord[COORD_SIZE];
	t_vec3			*n_vec;
	long double		diameter;
	long double		radius;
	long double		height;
	long double		fov;
	long double		intensity;
	long double		specular;
	long double		reflection;
	struct s_scn_el	*cap;
	t_color			color;
}					t_scn_el;

typedef struct	s_closest
{
	t_scn_el	*el;
	long double	dist;
}	t_closest;

typedef struct s_data
{
	t_list			*scn_el;
	t_scn_el		*cam;
	long double		viewport[COORD_SIZE];
	t_vec3			*v[VEC_SIZE];
	t_coord3		*p[POINT_SIZE];
	t_vec3			*rot_axis;
	long double		rot_angle;
	long double		*rot_angles;
	mlx_t			*mlx;
	mlx_image_t		*img;
}					t_data;

#endif