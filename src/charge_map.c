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

#include "so_long.h"

void	ft_make_map(t_game *game, int fd)
{
	char	*gnl;
	int		rows;
	int		cols;

	rows = 0;
	cols = 0;
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
	if (game->map == NULL)
		ft_errors(1, "Error:\nNo se pudo reservar memoria para el mapa");
	close(fd);
}

char	*ft_build_path(char *base_path, int frame_number)
{
	char	*frame_path;
	char	*full_path;

	frame_path = ft_strjoin(base_path, ft_itoa(frame_number));
	full_path = ft_strjoin(frame_path, ".xpm");
	free(frame_path);
	return (full_path);
}

char	**ft_matriz_aux(t_game *game)
{
	int		i;
	char	**matriz;

	i = 0;
	matriz = (char **)malloc(sizeof(char *) * (game->cols + 1));
	while (i < game->rows)
	{
		matriz[i] = ft_strdup(game->map[i]);
		++i;
	}
	matriz[i] = NULL;
	return (matriz);
}

void	ft_charge_map(t_game *game, char *file_path)
{
	char		*gnl;
	int			i;
	int			fd;

	fd = open(file_path, O_RDONLY);
	ft_errors((fd < 0), "Error:\nEl Archivo no existe o se se puede abrir");
	gnl = get_next_line(fd);
	i = 0;
	while (gnl != NULL && gnl[0] != '\0' && i < game->rows)
	{
		game->map[i] = *ft_split(gnl, '\n');
		free(gnl);
		gnl = get_next_line(fd);
		i++;
	}
	close(fd);
}

void	ft_charge_extra(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			mlx_put_image_to_window(game->mlx, game->win, game->floor.img,
				j * BK_SIZE, i * BK_SIZE);
			if (game->map[i][j] == '1')
				ft_charge_wall(game, i, j);
			else if (game->map[i][j] == 'E')
			{
				game->exit_x = j * BK_SIZE;
				game->exit_y = i * BK_SIZE;
				mlx_put_image_to_window(game->mlx, game->win,
					game->exit.img, game->exit_x, game->exit_y);
			}
			j++;
		}
		i++;
	}
}

void	ft_draw_map(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	printf("Movimientos: %d\n", game->player.moves);
	while (i < game->rows)
	{
		j = 0;
		while (j < game->cols)
		{
			printf("%c", game->map[i][j]);
			mlx_put_image_to_window(game->mlx, game->win, game->floor.img,
				j * BK_SIZE, i * BK_SIZE);
			if (game->map[i][j] == '1')
				ft_charge_wall(game, i, j);
			else if (game->map[i][j] == 'P')
			{
				game->player.x = j * BK_SIZE;
				game->player.y = i * BK_SIZE;
				ft_animation(game);
			}
			else if (game->map[i][j] == 'C')
				mlx_put_image_to_window(game->mlx, game->win,
					game->collectible.img, j * BK_SIZE, i * BK_SIZE);
			else if (game->map[i][j] == '0')
				mlx_put_image_to_window(game->mlx, game->win,
					game->floor.img, j * BK_SIZE, i * BK_SIZE);
			mlx_put_image_to_window(game->mlx, game->win,
				game->exit.img,
				game->exit_x * BK_SIZE, game->exit_y * BK_SIZE);
			j++;
		}
		printf("\n");
		i++;
	}
}
