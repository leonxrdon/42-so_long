/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnarvaez <lnarvaez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:59:21 by lnarvaez          #+#    #+#             */
/*   Updated: 2024/03/11 12:02:54 by lnarvaez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_load_front(t_game *game)
{
	t_sprite	front;
	char		*path;
	int			i;

	i = 0;
	while (i < NUM_FRAMES)
	{
		path = ft_build_path("god_", i);
		front = ft_load_texture(game->mlx, path);
		free(path);
		game->player.front[i] = front;
		i++;
	}
}

void	ft_load_left(t_game *game)
{
	t_sprite	left;
	char		*path;
	int			i;

	i = 0;
	while (i < NUM_FRAMES)
	{
		path = ft_build_path("g_left_", i);
		left = ft_load_texture(game->mlx, path);
		free(path);
		game->player.left[i] = left;
		i++;
	}
}

void	ft_load_right(t_game *game)
{
	t_sprite	right;
	char		*path;
	int			i;

	i = 0;
	while (i < NUM_FRAMES)
	{
		path = ft_build_path("g_right_", i);
		right = ft_load_texture(game->mlx, path);
		free(path);
		game->player.right[i] = right;
		i++;
	}
}

void	ft_load_up_down(t_game *game)
{
	t_sprite	up;
	t_sprite	down;
	char		*path;
	int			i;

	i = 0;
	while (i < NUM_FRAMES)
	{
		path = ft_build_path("g_up_", i);
		up = ft_load_texture(game->mlx, path);
		down = ft_load_texture(game->mlx, path);
		free(path);
		game->player.up[i] = up;
		game->player.down[i] = down;
		i++;
	}
}

void	ft_load_player(t_game *game)
{
	game->player.x = 0;
	game->player.y = 0;
	game->player.moves = 0;
	game->player.frame = 0;
	game->player.action = "front";
	ft_load_front(game);
	ft_load_left(game);
	ft_load_right(game);
	ft_load_up_down(game);
}
