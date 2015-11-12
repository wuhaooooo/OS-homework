all: main snake

main: main.c async.c
	gcc -o main main.c queue.c scheduler.c *.s async.c -lrt

snake: snake.c async.c  
	gcc -o snake snake.c queue.c scheduler.c *.s async.c -lrt

clean:
	rm -f main snake
