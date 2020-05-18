CC = lcc -Wa-l -Wl-m -Wl-j

all: tiles
	$(CC) -c -o bin/main.o src/main.c
	$(CC) -o bin/main.gb bin/main.o bin/tiles/snake_sprite.o bin/tiles/snake_body.o bin/tiles/snake_map.o

tiles: prereq
	mkdir -p bin/tiles
	$(CC) -c -o bin/tiles/snake_sprite.o src/tiles/snake_sprite.c
	$(CC) -c -o bin/tiles/snake_body.o src/tiles/snake_body.c
	$(CC) -c -o bin/tiles/snake_map.o src/tiles/snake_map.c

prereq:
	mkdir -p bin

clean:
	rm -rf bin
