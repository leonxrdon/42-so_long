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
#include <mlx.h>

#define MAP_WIDTH 7
#define MAP_HEIGHT 7

typedef struct {
    char map[MAP_HEIGHT][MAP_WIDTH];
} Map;

void load_map(Map *map) {
    // Definir manualmente el mapa o leerlo desde un archivo de texto
    char temp_map[MAP_HEIGHT][MAP_WIDTH] = {
        "1111111",
        "1P0010E",
        "1C00101",
        "1000101",
        "10C0101",
        "1000001",
        "1111111"
    };

    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            map->map[i][j] = temp_map[i][j];
        }
    }
}

void mlx_rectangle(void *mlx, void *win, int x, int y, int width, int height, int color) {
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

void draw_map(void *mlx, void *win, Map *map) {
    int block_size = 30; // Tamaño de cada bloque en píxeles

    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            int x = j * block_size;
            int y = i * block_size;

           if (map->map[i][j] == '1') {
                // Dibujar pared (color rojo)
                mlx_rectangle(mlx, win, x, y, block_size, block_size, 0xFF0000);
            } else if (map->map[i][j] == 'P') {
                // Dibujar posición inicial (color verde)
                mlx_rectangle(mlx, win, x, y, block_size, block_size, 0x00FF00);
            } else if (map->map[i][j] == 'C') {
                // Dibujar coleccionable (color azul)
                mlx_rectangle(mlx, win, x, y, block_size, block_size, 0x0000FF);
            } else if (map->map[i][j] == 'E') {
                // Dibujar salida (color amarillo)
                mlx_rectangle(mlx, win, x, y, block_size, block_size, 0xFFFF00);
            }
            // No dibujar nada para espacios vacíos ('0')
        }
    }
}




int main(void) {
    void *mlx;
    void *mlx_win;
    Map game_map;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, MAP_WIDTH * 30, MAP_HEIGHT * 30, "Map Viewer");

    load_map(&game_map);
    draw_map(mlx, mlx_win, &game_map);

    mlx_loop(mlx);

    return 0;
}
