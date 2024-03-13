/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnarvaez <lnarvaez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:05:36 by lnarvaez          #+#    #+#             */
/*   Updated: 2023/11/30 18:05:38 by lnarvaez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_player_move(t_game *game, int x, int y)
{
	if (game->map[x][y] == 'C')
	{
		game->collectibles--;
		game->player.moves++;
		if (game->collectibles == 0)
			game->map[game->exit_y][game->exit_x] = 'E';
	}
	else if (game->map[x][y] == 'E')
	{
		game->player.moves++;
		if (game->collectibles == 0)
			ft_end_game(game);
	}
	else if (game->map[x][y] == '0')
		game->player.moves++;
	if (game->map[x][y] != '1')
	{
		game->map[x][y] = 'P';
		game->map[game->player.y / BK_SIZE][game->player.x / BK_SIZE] = '0';
	}
	ft_draw_map(game);
}

int	ft_move(int key, t_game *game)
{
	int	x;
	int	y;

	y = game->player.x / BK_SIZE;
	x = game->player.y / BK_SIZE;
	if (key == KEY_ESC)
		ft_end_game(game);
	else if (key == KEY_A || key == KEY_LEFT)
		ft_player_move(game, x, y - 1);
	else if (key == KEY_D || key == KEY_RIGHT)
		ft_player_move(game, x, y + 1);
	else if (key == KEY_S || key == KEY_DOWN)
		ft_player_move(game, x + 1, y);
	else if (key == KEY_W || key == KEY_UP)
		ft_player_move(game, x - 1, y);
	return (0);
}

void	ft_animation(t_game *game)
{
	int	i;

	i = 0;
	printf("Movimientos: %d\n", game->player.moves);
	mlx_put_image_to_window(game->mlx, game->win,
		game->player.sprite.img,
		game->player.x, game->player.y);
}
