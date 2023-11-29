#include <mlx.h>

#define MAP_WIDTH 5
#define MAP_HEIGHT 5

typedef struct {
    char map[MAP_HEIGHT][MAP_WIDTH];
} Map;

void load_map(Map *map) {
    // Definir manualmente el mapa o leerlo desde un archivo de texto
    char temp_map[MAP_HEIGHT][MAP_WIDTH] = {
        "11111",
        "1P00E",
        "1C001",
        "10001",
        "11111"
    };

    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            map->map[i][j] = temp_map[i][j];
        }
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
                mlx_pixel_put(mlx, win, x, y, 0xFF0000);
            } else if (map->map[i][j] == 'P') {
                // Dibujar posición inicial (color verde)
                mlx_pixel_put(mlx, win, x, y, 0x00FF00);
            } else if (map->map[i][j] == 'C') {
                // Dibujar coleccionable (color azul)
                mlx_pixel_put(mlx, win, x, y, 0x0000FF);
            } else if (map->map[i][j] == 'E') {
                // Dibujar salida (color amarillo)
                mlx_pixel_put(mlx, win, x, y, 0xFFFF00);
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
