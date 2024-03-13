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

void	ft_player_move(t_game *game, int x, int y, char *action)
{
	ft_update_frames(&game->player);
	game->player.action = action;
	printf("x: %d, y: %d\n", x, y);
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
		ft_player_move(game, x, y - 1, "left");
	else if (key == KEY_D || key == KEY_RIGHT)
		ft_player_move(game, x, y + 1, "right");
	else if (key == KEY_S || key == KEY_DOWN)
		ft_player_move(game, x + 1, y, "down");
	else if (key == KEY_W || key == KEY_UP)
		ft_player_move(game, x - 1, y, "up");
	return (0);
}

void	ft_animation(t_game *game)
{
	int	i;

	i = 0;
	printf("Movimientos: %d\n", game->player.moves);
	if (ft_strncmp(game->player.action, "front", 5) == 0)
		mlx_put_image_to_window(game->mlx, game->win,
			game->player.front[game->player.frame].img,
			game->player.x, game->player.y);
	else if (ft_strncmp(game->player.action, "right", 5) == 0)
		mlx_put_image_to_window(game->mlx, game->win,
			game->player.right[game->player.frame].img,
			game->player.x, game->player.y);
	else if (ft_strncmp(game->player.action, "left", 4) == 0)
		mlx_put_image_to_window(game->mlx, game->win,
			game->player.left[game->player.frame].img,
			game->player.x, game->player.y);
	else if (ft_strncmp(game->player.action, "up", 2) == 0)
		mlx_put_image_to_window(game->mlx, game->win,
			game->player.up[game->player.frame].img,
			game->player.x, game->player.y);
	else if (ft_strncmp(game->player.action, "down", 4) == 0)
		mlx_put_image_to_window(game->mlx, game->win,
			game->player.down[game->player.frame].img,
			game->player.x, game->player.y);
}
