/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_event.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 21:22:58 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/02 21:26:47 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <minirt.h>
#include <MLX42.h>

void	close_window(mlx_key_data_t keydata, t_data d)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		clean_up(&d);
		mlx_terminate(d.mlx);
		exit(0);
	}
}
