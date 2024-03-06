/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnarvaez <lnarvaez@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:18:22 by lnarvaez          #+#    #+#             */
/*   Updated: 2023/07/12 18:18:27 by lnarvaez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void mlx_rectangle(void *mlx, void *win, int x, int y, int width, int height, int color)
{
	int i = 0;
	while (i < height) {
		int j = 0;
		while (j < width) {
			mlx_pixel_put(mlx, win, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

// void draw_map(void *mlx, void *win, Map *map, Texture *wall_texture, Texture *user_texture, Texture *coin, Texture *salida)
// {
// 	int block_size = 50;
// 	for (int i = 0; i < 7; i++) {
// 		for (int j = 0; j < 7; j++) {
// 			int x = j * block_size;
// 			int y = i * block_size;

// 			if (map->map[i][j] == '1') {
// 				mlx_put_image_to_window(mlx, win, wall_texture->img, x, y);
// 			} else if (map->map[i][j] == 'P') {
// 				mlx_put_image_to_window(mlx, win, user_texture->img, x, y);
// 			} else if (map->map[i][j] == 'C') {
// 				mlx_put_image_to_window(mlx, win, coin->img, x, y);
// 			} else if (map->map[i][j] == 'E') {
// 				mlx_put_image_to_window(mlx, win, salida->img, x, y);
// 			} else {
// 				mlx_rectangle(mlx, win, x, y, block_size, block_size, 0x000000);
// 			}
// 		}
// 	}
// }

// Texture load_texture(void *mlx, char *file_path){
// 	Texture texture;
// 	texture.img = mlx_xpm_file_to_image(mlx, file_path, &texture.width, &texture.height);

// 	if (!texture.img) {
//         printf("Error al cargar la textura desde %s\n", file_path);

// 	}
// 	return texture;
// }

//dibujar la matriz en el mapa
void draw_map_matriz(void *mlx, void *win, char **map)
{
	int block_size;
	int	i;
	int	j;
	int	x;
	int	y;
	printf("entro a la funcion\n");
	printf("%c\n", map[0][0]);
	block_size = 50;
	i = 0;
	j = 0;
	while (i < 7)
	{
		while(j < 7)
		{
			x = j * block_size;
			y = i * block_size;
			j++;
			if (map[i][j] == '1')
				//color rojo
				mlx_rectangle(mlx, win, x, y, block_size, block_size, 0xFF0000);
			else if (map[i][j] == 'P')
				mlx_rectangle(mlx, win, x, y, block_size, block_size, 0x0000FF);
			else if (map[i][j] == 'C')
				mlx_rectangle(mlx, win, x, y, block_size, block_size, 0xFF0000);
			else if (map[i][j] == 'E')
				mlx_rectangle(mlx, win, x, y, block_size, block_size, 0xFFFF00);
			else
				mlx_rectangle(mlx, win, x, y, block_size, block_size, 0x000000);
		}
		i++;
	}
}

t_sprite	load_texture(void *mlx, char *file_path)
{
	t_sprite	texture;
	char	*route;

	route = ft_strjoin(XPM_ROUTE, file_path);
	texture.height = 50;
	texture.width = 50;
	texture.path = route;
	texture.img = mlx_xpm_file_to_image(mlx, route, &texture.width, &texture.height);
	if (!texture.img)
	{
		printf("Error al cargar la textura desde %s\n", route);
		exit(1);
	}
	return (texture);
}

void	ft_game_init(t_game *game, int fd, char *file_path)
{
	game->mlx = mlx_init();
	ft_make_map(game, fd);
	game->win = mlx_new_window(game->mlx, (game->cols * 50), (game->rows * 50), "so_long");
	ft_charge_map(game, file_path);
	mlx_key_hook(game->win, ft_move, game);
	mlx_loop(game->mlx);
}

//funcion para validar la extencion del argumento
int	main(int argc, char **argv) {
	t_game	game;
	int		fd;
	//char	*gnl;
	// Map *str;
	// Texture	wall_texture;
	// Texture	user_texture;
	// Texture	coin_texture;
	// Texture	exit_texture;
	if (argc != 2)
		return (0);
	if (argv[0] != 0)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			exit(EXIT_FAILURE);
		if (ft_validate_ext(argv[1], ".ber"))
		{
			printf("Error: El archivo no tiene la extencion .ber\n");
			exit(EXIT_FAILURE);
		}
		ft_game_init(&game, fd, argv[1]);


		// if (fd < 0)
		// {
		// 	printf("Error al abrir el archivo\n");
		// 	exit(1);
		// }
		// gnl = get_next_line(fd);
		// while (gnl != NULL && gnl[0] != '\0')
		// {
		// 	printf("%s", gnl);
		// 	//matriz = ft_split(gnl, '\n');
		// 	gnl = get_next_line(fd);
		// }
		// // crear una funcion para cargar el mapa
		// // load_map(&str);
		// wall_texture = load_texture(mlx, "texturas/bloque.xpm");
		// user_texture = load_texture(mlx, "texturas/mario.xpm");
		// coin_texture = load_texture(mlx, "texturas/coin.xpm");
		// exit_texture = load_texture(mlx, "texturas/salida.xpm");

		// draw_map(mlx, mlx_win, &str, &wall_texture, &user_texture, &coin_texture, &exit_texture);
		// mlx_hook(mlx_win, 2, 1L<<0, move, &vars);
		// mlx_key_hook(mlx_win, move, &vars);
	}
	return 0;
}
