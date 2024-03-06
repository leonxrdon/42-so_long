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


//Funcion para cargar el mapa en la estructura
void	ft_load_player(t_game *game)
{
	printf("Funcion load player\n");
	int		i;
	int		j;
	int		block_size;

	i = 0;
	j = 0;
	block_size = 50;
	printf("game->rows: %d\n", game->rows);
	printf("game->cols: %d\n", game->cols);
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
	front = load_texture(game->mlx, "mario.xpm");
	game->wall = wall;
	game->collectible = collectible;
	game->exit = exit;
	game->floor = floor;
	game->player.front = front;
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
	ft_load_player(game);
	ft_draw_map(game);
}

void	ft_draw_map(t_game *game)
{
	int		i;
	int		j;
	int		block_size;

	block_size = 50;
	i = 0;
	printf("Movimientos: %d\n", game->player.moves);
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			mlx_put_image_to_window(game->mlx, game->win, game->floor.img, j * block_size, i * block_size);
			if (game->map[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->wall.img, j * block_size, i * block_size);
			if (game->map[i][j] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, game->player.front.img, j * block_size, i * block_size);
			if (game->map[i][j] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->collectible.img, j * block_size, i * block_size);
			if (game->map[i][j] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->exit.img, j * block_size, i * block_size);
			j++;
		}
		i++;
	}
}
