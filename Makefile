CC = lcc -Wa-l -Wl-m -Wl-j

all: tile_objs bin_objs
	$(CC) -o bin/snakes.gb $(wildcard bin/*.o) $(wildcard bin/tiles/*.o)

bin_objs: obj_dir
	$(CC) -c -o bin/utils.o src/utils.c
	$(CC) -c -o bin/main.o src/main.c 

tile_objs: obj_dir
	mkdir -p bin/tiles
	$(CC) -c -o bin/tiles/snake_sprite.o src/tiles/snake_sprite.c
	$(CC) -c -o bin/tiles/snake_body.o src/tiles/snake_body.c
	$(CC) -c -o bin/tiles/snake_map.o src/tiles/snake_map.c
	$(CC) -c -o bin/tiles/prey_tiles.o src/tiles/prey_tiles.c

obj_dir:
	mkdir -p bin

clean:
	rm -rf bin
