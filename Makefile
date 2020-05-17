CC	= lcc -Wa-l -Wl-m -Wl-j

all: sprites
	$(CC) -c -o bin/main.o src/main.c
	$(CC) -o bin/main.gb bin/main.o bin/sprites/sprites.o

sprites: prereq
	mkdir -p bin/sprites
	$(CC) -c -o bin/sprites/sprites.o src/sprites/snake_sprite.c

prereq:
	mkdir -p bin

clean:
	rm -rf bin