all:
	gcc -o server server.c sudokusolver.c -pthread
	gcc -o client client.c sudokusolver.c

clean:
	rm server
	rm client
