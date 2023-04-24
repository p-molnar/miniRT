/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mrt_data_struct.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:06:43 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/24 23:15:41 by pmolnar       ########   odam.nl         */
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
// 	unsigned int	brightness;
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
// 	unsigned int	brightness;
// 	t_color			color;
// }	t_light;

typedef int				t_el_type;
typedef int				t_color;

typedef struct s_scn_el
{
	t_el_type			type;
	double				coord[COORD_SIZE];
	double				norm_vec[COORD_SIZE];
	double				diameter;
	double				height;
	double				fov;
	double				brightness;
	t_color				color;
}						t_scn_el;

// typedef struct coord_2d
// {
// 	int	x;
// 	int	y;
// }	t_coord_2d;

typedef struct s_vec
{
	double				norm;
	double				coord[COORD_SIZE];
}						t_vec;

typedef struct s_data
{
	t_list				*scn_el;
	mlx_t				*mlx;
	mlx_image_t			*img;
}						t_data;

#endif