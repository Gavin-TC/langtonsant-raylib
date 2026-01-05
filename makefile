all: build run clean

build:
	gcc -o main.exe main.c -I include -L lib -lraylib -lgdi32 -lwinmm

run:
	./main.exe

clean:
	rm main.exe
