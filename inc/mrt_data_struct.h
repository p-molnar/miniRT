/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mrt_data_struct.h                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:06:43 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/03 00:12:37 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_DATA_STRUCT_H
# define MRT_DATA_STRUCT_H

# include <MLX42.h>
# include <libft.h>
# include <mrt_macros.h>

typedef long double				t_coord;

typedef union u_color
{
	uint32_t					color;
	struct
	{
		uint8_t					a;
		uint8_t					b;
		uint8_t					g;
		uint8_t					r;
	};
}								t_color;

typedef struct s_coord_sys
{
	int							pixel_x;
	int							pixel_y;
	long double					x;
	long double					y;
}								t_coord_sys;

typedef struct s_range
{
	long double					min;
	long double					max;
}								t_range;

typedef struct s_line
{
	char						*content;
	char						*file;
	int							num;
}								t_line;

typedef struct s_err
{
	const char					*msg;
	char						*file;
	int							line;
	enum e_exit_method_code		exit_method;
	int							exit_code;
}								t_err;

typedef union u_coord3
{
	struct
	{
		t_coord					x;
		t_coord					y;
		t_coord					z;
	};
	t_coord						coord[3];
}								t_coord3;

typedef struct s_quad_params
{
	long double					a;
	long double					b;
	long double					c;
}								t_quad_param;

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
	t_vec3						orientation;
	long double					diameter;
	long double					radius;
	long double					height;
	long double					fov;
	long double					intensity;
	long double					spec_coeff;
	long double					refl_coeff;
	struct s_scn_el				*cap;
	t_mx						translation;
	t_mx						inv_translation;
	t_mx						rotation;
	t_mx						inv_rotation;
	t_color						color;
}								t_scn_el;

typedef struct s_hit_obj
{
	t_scn_el					*attr;
	bool						is_hit;
	t_coord3					inc_p_raw;
	t_coord3					inc_p;
	t_vec3						norm;
	long double					dist;
}								t_hit_obj;

typedef struct s_light_fn_arg
{
	t_scn_el					**objs;
	t_scn_el					light;
	t_ray						ray;
	t_hit_obj					hit_obj;
	t_vec3						light_dir;
	bool						visibility;
}								t_light_fn_arg;

typedef struct s_data
{
	t_list						*all_scn_el;
	t_scn_el					**scn_els[SCN_SIZE];
	t_mx						ctw_mx;
	mlx_t						*mlx;
	mlx_image_t					*img;
}								t_data;

#endif