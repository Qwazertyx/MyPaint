/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsedat <vsedat@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 10:06:39 by vsedat            #+#    #+#             */
/*   Updated: 2022/01/21 16:20:32 by vsedat           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractol.h"

int	close(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win);
	exit(EXIT_SUCCESS);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	erase(t_data *data)
{
	int	i;
	int	y;

	i = 0;
	while (i < 640)
	{
		y = 0;
		while (y < 480)
		{
			my_mlx_pixel_put(data, i, y, 0x00FFFFFF);
			y++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	if (keycode == 53)	//quit echap
		close(data);
	if (keycode == 8)
		erase(data);
	return (0);
}

int	mouse_hook(int keycode,int x,int y, t_data *data)
{
	if (data->uwu == 1)
		data->uwu = 0;
	else
		data->uwu = 1;
	return (0);
}

int	locmouse(int x, int y, t_data *data)
{
	if ((x > 0 && x < 640 && y > 0 && y < 480) && data->uwu == 1)
	{
		my_mlx_pixel_put(data, x, y, 0x00FF0000);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	return (0);
}

int	main(void)
{
	t_data	data;

	data.uwu = 0;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 640, 480, "sussy baka");
	data.img = mlx_new_image(data.mlx, 640, 480);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel,
			&data.line_length, &data.endian);
	erase(&data);
	mlx_key_hook(data.win, key_hook, &data);	//keyboard click
	mlx_hook(data.win, 17, 1L << 2, close, &data);	//quit red cross
	mlx_hook(data.win, 06, 1L << 6, locmouse, &data);	//loc mouse
	mlx_mouse_hook(data.win, mouse_hook, &data);	//mouse click
	mlx_loop(data.mlx);
}
