all:
	gcc -fsanitize=address -g cub3d.c tools.c draw_map.c raycasting.c mouve_mouse.c -o cub3d MLX/libmlx42.a -ldl -lglfw -L ~/.brew/Cellar/glfw/3.3.8/lib -pthread -lm -framework Cocoa -framework OpenGL -framework IOKit

	# gcc MLX/libmlx42.a -ldl -lglfw -L/usr/local/opt/glfw/lib/ -pthread -lm -framework Cocoa -framework OpenGL -framework IOKit cub3d.c   -o cub3d