/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnarvaez <lnarvaez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:18:38 by lnarvaez          #+#    #+#             */
/*   Updated: 2024/03/13 15:18:39 by lnarvaez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_draw_collect(t_game *game, int i, int j)
{
	mlx_put_image_to_window(game->mlx, game->win, game->collectible.img,
		j * BK_SIZE, i * BK_SIZE);
}

static void	ft_draw_floor(t_game *game, int i, int j)
{
	mlx_put_image_to_window(game->mlx, game->win, game->floor.img,
		j * BK_SIZE, i * BK_SIZE);
}

static void	ft_draw_exit(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->exit.img,
		game->exit_x * BK_SIZE, game->exit_y * BK_SIZE);
}

static void	ft_draw_wall(t_game *game, int i, int j)
{
	mlx_put_image_to_window(game->mlx, game->win,
		game->wall.img, j * BK_SIZE, i * BK_SIZE);
}

void	ft_draw_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			ft_draw_floor(game, i, j);
			if (game->map[i][j] == '1')
				ft_draw_wall(game, i, j);
			else if (game->map[i][j] == 'P')
			{
				game->player.x = j * BK_SIZE;
				game->player.y = i * BK_SIZE;
				ft_animation(game);
			}
			else if (game->map[i][j] == 'C')
				ft_draw_collect(game, i, j);
			ft_draw_exit(game);
			j++;
		}
		i++;
	}
}
