all: main demo counter_test

main: main.c async.c
	gcc -o main main.c queue.c scheduler.c *.s async.c -lrt

demo: demo.c async.c  
	gcc -o demo demo.c queue.c scheduler.c *.s async.c -lrt

counter_test: counter_test.c async.c
	gcc -o counter_test counter_test.c queue.c scheduler.c *.s async.c -lrt
	
clean:
	rm -f main demo counter_test
