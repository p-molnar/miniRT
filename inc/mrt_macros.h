/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mrt_macros.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:52:36 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/16 21:01:47 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MRT_MACROS_H
# define MRT_MACROS_H

enum	e_error_handler
{
	EXIT = 1,
	RETURN = 2,
};

enum	e_scn_el_type
{
	AMB_LIGHT=1,
	LIGHT,
	CAM,
	SPHERE,
	PLANE,
	CYLYNDER
};

enum	e_scn_el_member_flags
{
	F_COORD = 1 < 0,
	F_VEC = 1 < 1,
	F_DMETER = 1 < 2,
	F_HEIGHT = 1 < 3,
	F_FOV = 1 < 4,
	F_BRIGHT = 1 < 5,
	F_COLOR = 1 < 6,
};

#endif