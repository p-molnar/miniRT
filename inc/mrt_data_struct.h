/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mrt_data_struct.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:06:43 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/19 13:20:48 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_DATA_STRUCT_H
# define MRT_DATA_STRUCT_H

# include <MLX42.h>
# include <libft.h>
# include <mrt_macros.h>

typedef int						t_color;
typedef long double				t_coord;

typedef union u_coord3 
{
	struct {
		t_coord	x;
		t_coord	y;
		t_coord	z;
	};
	t_coord	coord[3];
}	t_coord3;

typedef struct s_quad_params
{
	long double	a;
	long double	b;
	long double	c;
}	t_quad_param;

typedef struct s_mx
{
	long double					m[16];
	int							r;
	int							c;
}								t_mx;

typedef struct s_vec
{
	long double					len;
	t_coord3					dir;
}								t_vec3;

typedef struct s_ray
{
	t_coord3					origin;
	t_vec3						dir;
}								t_ray;

typedef struct s_scn_el
{
	enum e_scn_el_type_flags	type;
	t_coord3					pos;
	t_coord3					target;
	t_vec3						n_vec;
	long double					diameter;
	long double					radius;
	long double					height;
	long double					fov;
	long double					intensity;
	long double					specular;
	long double					reflection;
	struct s_scn_el				*cap;
	t_mx						translation;
	t_mx						inv_translation;
	t_mx						rotation;
	t_mx						inv_rotation;
	t_color						color;
}								t_scn_el;

typedef struct s_closest
{
	t_scn_el					*el;
	t_coord3					inc_p;
	long double					dist;
}								t_closest;

typedef struct s_data
{
	t_list						*all_scn_el;
	t_scn_el					**scn_els[SCN_SIZE];
	t_mx						ctw_mx;
	mlx_t						*mlx;
	mlx_image_t					*img;
}								t_data;

#endif