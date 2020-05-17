CC	= ../../bin/lcc -Wa-l -Wl-m -Wl-j

all:
	mkdir -p bin
	lcc -Wa-l -Wl-m -Wl-j -c -o bin/main.o src/main.c
	lcc -Wa-l -Wl-m -Wl-j -o bin/main.gb bin/main.o

clean:
	rm -rf bin