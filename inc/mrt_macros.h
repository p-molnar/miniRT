/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mrt_macros.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:52:36 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/07/29 13:19:21 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_MACROS_H
# define MRT_MACROS_H
// # define CANVAS_W 10
// # define CANVAS_H 10
# define CANVAS_W 1280
# define CANVAS_H 720
# define INF 99999
# define BACKGROUND_COLOR 0x000000FF
# define EPS 0.00001


enum	e_range
{
	MIN,
	MAX,
	RANGE_SIZE,
};

enum	e_isect
{
	CLOSEST_EL,
	SHADOW
};

enum	e_exit_method_code
{
	EXIT = 1,
	RETURN = 2,
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

enum	e_scn_el_field_flags
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

enum	e_scn_el_type_flags
{
	F_TYPE_UNDEF = 0,
	F_AMB_LIGHT = 1 << 0,
	F_CAM = 1 << 1,
	F_TG_CAM = 1 << 2,
	F_POINT_LIGHT = 1 << 3,
	F_DIR_LIGHT = 1 << 4,
	F_SPHERE = 1 << 5,
	F_PLANE = 1 << 6,
	F_CYLINDER = 1 << 7,
	F_CYLINDER_CAP = 1 << 8,
	F_SCN_SIZE = F_CYLINDER_CAP + 1,
};

enum	e_scn_el_type
{
	TYPE_UNDEF,
	AMB_LIGHT,
	CAM,
	TG_CAM,
	POINT_LIGHT,
	DIR_LIGHT,
	SPHERE,
	PLANE,
	CYLINDER,
	CYLINDER_CAP,
	ALL_LIGHTS,
	ALL_OBJS,
	SCN_SIZE,
};

enum	e_field_flags
{
	AMB_LIGHT_FIELDS = F_INTENSITY | F_COLOR,
	LIGHT_FIELDS = F_COORD | F_INTENSITY | F_COLOR,
	DIR_LIGHT_FIELDS = F_COORD | F_TG_COORD | F_INTENSITY | F_COLOR,
	CAM_FIELDS = F_COORD | F_N_VEC | F_FOV,
	TG_CAM_FIELDS = F_COORD | F_TG_COORD | F_FOV,
	SPHERE_FIELDS = F_COORD | F_DMETER | F_COLOR | F_SPECULAR | F_REFLECTION,
	PLANE_FIELDS = F_COORD | F_N_VEC | F_COLOR | F_SPECULAR | F_REFLECTION,
	CYLINDER_FIELDS = F_COORD | F_N_VEC | F_DMETER | F_HEIGHT | F_COLOR | \
											F_SPECULAR | F_REFLECTION,
};

#endif