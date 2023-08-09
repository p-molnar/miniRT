/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_event.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: pmolnar <pmolnar@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/02 21:22:58 by pmolnar       #+#    #+#                 */
/*   Updated: 2023/08/09 18:13:00 by pmolnar       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minirt.h>
#include <stdlib.h>
#include <MLX42.h>

mlx_keyfunc	close_window(mlx_key_data_t keydata, t_data *d)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		clean_up(d);
		mlx_terminate(d->mlx);
		exit(0);
	}
	return (0);
}
