all:
	gcc MLX/libmlx42.a -ldl -lglfw -L/usr/local/opt/glfw/lib/ -pthread -lm -framework Cocoa -framework OpenGL -framework IOKit cub3d.c -fsanitize=address -g -o cub3d