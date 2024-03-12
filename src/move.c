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

void	ft_player_move(t_game *game, int i, int j, int x, int y)
{
	ft_update_frames(&game->player);
	if (game->map[x][y] == '1')
	{
		printf("No se puede mover\n");
	}
	else if (game->map[x][y] == 'C')
	{
		game->player.moves++;
		game->collectibles--;
		game->map[x][y] = 'P';
		game->map[i][j] = '0';
		printf("Se ha recogido una Esfera\n");
		if (game->collectibles == 0)
			game->map[game->exit_y][game->exit_x] = 'E';
	}
	else if (game->map[x][y] == 'E')
	{
		if (game->collectibles == 0)
		{

			game->player.moves++;
			printf("Se ha llegado a la salida\n");
			ft_free_map(game->map, game->rows);
			ft_close_esc(game);
		}
		else
		{
			game->player.moves++;
			game->map[x][y] = 'P';
			game->map[i][j] = '0';
		}
	}
	else if (game->map[x][y] == '0')
	{
		game->player.moves++;
		game->map[x][y] = 'P';
		game->map[i][j] = '0';
	}
	ft_draw_map(game);
}

int	ft_move(int key, t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			if (game->map[i][j] == 'P')
			{
				if (key == KEY_ESC)
				{
					printf("Salir\n");
					ft_close_esc(game);
				}
				else if (key == KEY_A || key == KEY_LEFT)
				{
					game->player.action = "left";
					ft_player_move(game, i, j, i, j - 1);
				}
				else if (key == KEY_D || key == KEY_RIGHT)
				{
					game->player.action = "right";
					ft_player_move(game, i, j, i, j + 1);
				}
				else if (key == KEY_S || key == KEY_DOWN)
				{
					game->player.action = "down";
					ft_player_move(game, i, j, i + 1, j);
				}
				else if (key == KEY_W || key == KEY_UP)
				{
					game->player.action = "up";
					ft_player_move(game, i, j, i - 1, j);
				}
				return (0);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_animation(t_game *game)
{
	int	i;

	i = 0;
	if (ft_strncmp(game->player.action, "front", 5) == 0)
		mlx_put_image_to_window(game->mlx, game->win,
			game->player.front[game->player.frame].img,
			game->player.x, game->player.y);
	else if (ft_strncmp(game->player.action, "right", 5) == 0)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->player.right[game->player.frame].img, game->player.x, game->player.y);
	}
	else if (ft_strncmp(game->player.action, "left", 4) == 0)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->player.left[game->player.frame].img, game->player.x, game->player.y);
	}
	else if (ft_strncmp(game->player.action, "up", 2) == 0)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->player.up[game->player.frame].img, game->player.x, game->player.y);
	}
	else if (ft_strncmp(game->player.action, "down", 4) == 0)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->player.down[game->player.frame].img, game->player.x, game->player.y);
	}
}
