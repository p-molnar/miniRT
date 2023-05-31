/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mrt_macros.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:52:36 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/05/30 16:07:16 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_MACROS_H
# define MRT_MACROS_H
# define CANVAS_W 800
# define CANVAS_H 800
# define INF 99999
// # define BACKGROUND_COLOR 0xFFFFFFFF
# define BACKGROUND_COLOR 0x000000FF
# define EPS 0.00001

# ifndef RECURSIVE_DEPTH
#  define RECURSIVE_DEPTH 0
# endif

enum	e_dim_size
{
	WIDTH,
	HEIGHT,
	DEPTH,
	DIM_SIZE,
};

enum	e_range
{
	MIN,
	MAX,
	RANGE_SIZE,
};

enum	e_error_handler
{
	EXIT = 1,
	RETURN = 2,
};

enum	e_vec_params
{
	RAY,
	NORM,
	REFLECTION,
	LIGHT,
	VEC_SIZE,
};

enum	e_points
{
	INCIDENT,
	POINT_SIZE,
};

enum	e_coord
{
	X,
	Y,
	Z,
	COORD_SIZE,
};

enum	e_color
{
	A,
	B,
	G,
	R,
	COLOR_SIZE,
};

enum	e_scn_el_member_flags
{
	F_COORD = 1 << 0,
	F_TG_COORD = 1 << 1,
	F_N_VEC = 1 << 2,
	F_DMETER = 1 << 3,
	F_HEIGHT = 1 << 4,
	F_FOV = 1 << 5,
	F_INTENSITY = 1 << 6,
	F_COLOR = 1 << 7,
	F_SPECULAR = 1 << 8,
	F_REFLECTION = 1 << 9,
};

enum	e_scn_el_type
{
	TYPE_UNDEF = 0,
	AMB_LIGHT = 1 << 0,
	CAM = 1 << 1,
	TG_CAM = 1 << 2,
	POINT_LIGHT = 1 << 3,
	DIR_LIGHT = 1 << 4,
	SPHERE = 1 << 5,
	PLANE = 1 << 6,
	CYLINDER = 1 << 7,
	CYLINDER_CAP = 1 << 8,
	SCN_SIZE = CYLINDER_CAP + 1
};

enum	e_field_flags
{
	F_AMB_LIGHT = F_INTENSITY | F_COLOR,
	F_LIGHT = F_COORD | F_INTENSITY | F_COLOR,
	F_DIR_LIGHT = F_COORD | F_INTENSITY | F_COLOR,
	F_CAM = F_COORD | F_N_VEC | F_FOV,
	F_TG_CAM = F_COORD | F_TG_COORD | F_FOV,
	F_SPHERE = F_COORD | F_DMETER | F_COLOR | F_SPECULAR | F_REFLECTION,
	F_PLANE = F_COORD | F_N_VEC | F_COLOR | F_SPECULAR | F_REFLECTION,
	F_CYLINDER = F_COORD | F_N_VEC | F_DMETER | F_HEIGHT | F_COLOR | \
											F_SPECULAR | F_REFLECTION,
};

enum	e_groupped_el
{
	G_LIGHT = AMB_LIGHT | POINT_LIGHT | DIR_LIGHT,
	G_CAM = CAM | TG_CAM,
	G_OBJS = SPHERE | PLANE | CYLINDER,
};
#endif