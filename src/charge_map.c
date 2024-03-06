/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charge_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnarvaez <lnarvaez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:48:38 by lnarvaez          #+#    #+#             */
/*   Updated: 2024/03/05 15:48:44 by lnarvaez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	ft_make_map(t_game *game, int fd)
{
	char	*gnl;
	int		rows;
	int		cols;
	int		i;

	rows = 0;
	cols = 0;
	i = 0;
	gnl = get_next_line(fd);
	while (gnl != NULL)
	{
		rows++;
		cols = (ft_strlen(gnl) - 1);
		free(gnl);
		gnl = get_next_line(fd);
	}
	game->rows = rows;
	game->cols = cols;
	game->map = (char **)malloc(sizeof(char *) * rows + 1);
	while (gnl != NULL)
	{
		game->map[i] = gnl;
		printf("game->map[%d]: %s\n", i, game->map[i]);
		i++;
	}
	close(fd);
}

char *build_path(char *base_path, int frame_number)
{
    // Suponiendo que ft_strjoin concatena dos cadenas
    char *frame_path;
    char *full_path;

	frame_path = ft_strjoin(base_path, ft_itoa(frame_number));
	full_path = ft_strjoin(frame_path, ".xpm");
    free(frame_path);
    return full_path;
}


//Funcion para cargar el mapa en la estructura
void	ft_load_player(t_game *game)
{
	t_sprite	front;
	t_sprite	left;
	t_sprite	right;
	t_sprite	up;
	t_sprite	down;
	char		*path;
	int		i;

	i = 0;
	while (i < NUM_FRAMES)
	{
		path = build_path("player/g", i);
		front = load_texture(game->mlx, path);
		game->player.front[i] = front;
		game->player.front[i].path = path;
		printf("Path: %s\n", game->player.front[i].path);
		free(path);
		i++;
	}
	i = 0;
	while (i < NUM_FRAMES)
	{
		path = build_path("player/g", i);
		right = load_texture(game->mlx, path);
		game->player.right[i] = right;
		game->player.right[i].path = path;
		free(path);
		i++;
	}
	left = load_texture(game->mlx, "player/g0.xpm");
	up = load_texture(game->mlx, "player/g1.xpm");
	down = load_texture(game->mlx, "player/g2.xpm");
	game->player.left = left;
	game->player.up = up;
	game->player.down = down;
	game->player.frame = 0;
}

void	ft_charge_map(t_game *game, char *file_path)
{
	char		*gnl;
	int			i;
	int			fd;
	t_sprite	wall;
	t_sprite	collectible;
	t_sprite	exit;
	t_sprite	floor;
	t_sprite	front;

	wall = load_texture(game->mlx, "bloque.xpm");
	collectible = load_texture(game->mlx, "coin.xpm");
	exit = load_texture(game->mlx, "salida.xpm");
	floor = load_texture(game->mlx, "floor.xpm");
	front = load_texture(game->mlx, "player/g1.xpm");
	game->wall = wall;
	game->collectible = collectible;
	game->exit = exit;
	game->floor = floor;
	fd = open(file_path, O_RDONLY);
	gnl = get_next_line(fd);
	i = 0;
	while (gnl != NULL && gnl[0] != '\0' && i < game->rows)
	{
		game->map[i] = *ft_split(gnl, '\n');
		gnl = get_next_line(fd);
		i++;
	}
	game->collectibles = 0;
	game->player.moves = 0;
	game->player.action = "front";
	ft_load_player(game);

	ft_draw_map(game);
	ft_update_frames(&game->player);

}

void	ft_draw_map(t_game *game)
{
	int		i;
	int		j;
	int		block_size;

	block_size = 50;
	i = 0;
	printf("Movimientos: %d\n", game->player.moves);
	ft_update_frames(&game->player);
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			mlx_put_image_to_window(game->mlx, game->win, game->floor.img, j * block_size, i * block_size);
			if (game->map[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->wall.img, j * block_size, i * block_size);
			else if (game->map[i][j] == 'P')
			{
				game->player.x = j * block_size;
				game->player.y = i * block_size;
				mlx_put_image_to_window(game->mlx, game->win, game->player.front[game->player.frame].img, game->player.x, game->player.y);
			}
			else if (game->map[i][j] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->collectible.img, j * block_size, i * block_size);
			else if (game->map[i][j] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->exit.img, j * block_size, i * block_size);
			else if (game->map[i][j] == '0')
				mlx_put_image_to_window(game->mlx, game->win, game->floor.img, j * block_size, i * block_size);
			else
			{
				printf("Error: Mapa invalido\n");
				exit(EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
}
