/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JFikents <Jfikents@student.42Heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 15:52:21 by apeposhi          #+#    #+#             */
/*   Updated: 2024/07/17 15:55:51 by JFikents         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

const char	**get_map(t_player player[1])
{
	static const char	*map[11] = {
		"111111111111",
		"100010000001",
		"100010000001",
		"100001000001",
		"10000N000001",
		"100000000001",
		"100100000001",
		"100010000001",
		"100000000001",
		"111111111111",
		NULL
	};

	player->x = 5;
	player->y = 4;
	player->angle = 3 * PI / 2;
	player->delta_x = 17 * (1 + cos(player->angle));
	player->delta_y = 17 * (1 + sin(player->angle));
	return (map);
}

mlx_image_t	*get_wall_img(mlx_t *window)
{
	mlx_image_t	*img;
	int			x;
	int			y;

	img = mlx_new_image(window, 64, 64);
	y = 0;
	while (y < 63)
	{
		x = 0;
		while (x < 63)
			mlx_put_pixel(img, x++, y, 0x00FFFFFF);
		y++;
	}
	return (img);
}

mlx_image_t	*get_floor_img(mlx_t *window)
{
	mlx_image_t	*img;
	int			x;
	int			y;

	img = mlx_new_image(window, 64, 64);
	y = 0;
	while (y < 63)
	{
		x = 0;
		while (x < 63)
			mlx_put_pixel(img, x++, y, 0x000000FF);
		y++;
	}
	return (img);
}

int	put_map(mlx_t *window, const char **map)
{
	uint32_t	x;
	uint32_t	y;
	mlx_image_t	*wall;
	mlx_image_t	*floor;

	wall = get_wall_img(window);
	floor = get_floor_img(window);
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '1')
				mlx_image_to_window(window, wall, x * 64, y * 64);
			else
				mlx_image_to_window(window, floor, x * 64, y * 64);
			x++;
		}
		y++;
	}
	return (0);
}

int	main(void)
{
	t_loop_data	data[1];

	data->map = get_map(data->player);
	data->window = mlx_init(WIDTH, HEIGHT, "Cub3D", true);
	data->player->img = NULL;
	put_map(data->window, data->map);
	put_player(data->window, data->player);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx_set_setting(MLX_FULLSCREEN, true);
	mlx_key_hook(data->window, player_moves, (void *)data);
	mlx_loop(data->window);
	return (0);
}
