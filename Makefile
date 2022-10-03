clean :
	rm *.o

main : 
	gcc -pthread -o main.o main.c

client : 
	gcc -pthread -o client.o client.c