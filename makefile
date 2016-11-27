xSnake: xSnake.o
	gcc -std=gnu11 xSnake.o -o xSnake -lX11
xSnake.o: xSnake.c
	gcc -std=gnu11 -c xSnake.c -o xSnake.o -lX11
rm:
	rm xSnake.o xSnake