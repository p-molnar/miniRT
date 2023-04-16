/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mrt_macros.h                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/13 12:52:36 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/04/16 20:26:49 by pmolnar       ########   odam.nl         */
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

#endif