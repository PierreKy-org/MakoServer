#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define MAX 20

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

void whileRead(int *sockfd)
{
    char buff[MAX];
    int n;
    while(1) {
        bzero(buff, sizeof(buff));
        //if something in the buffer then print it  
        if(read(*sockfd, buff, sizeof(buff)) > 0){
            printf("From Server : %s", buff);
            if ((strncmp(buff, "exit", 4)) == 0) {
                printf("Client Exit...\n");
                break;
        }
        }
    }
}
/*
void *whileWrite(int *sockfd)
{
    char buff[MAX];
    int n;
    while(1) {
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(*sockfd, buff, sizeof(buff));
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Server Exit...\n");
            break;
        }
    }
}*/
void *boucleServeur(void * csock_arg)
{
    SOCKET csock = *((SOCKET*) csock_arg);
    whileRead(&csock);
    close(csock);

}   

//acceptclient
void acceptClient(SOCKET sock)
{
    SOCKADDR_IN csin;
    SOCKET csocks[5]; 
    socklen_t recsize = sizeof(csin);
    pthread_t thread;
    int i = 0;
    while(1){
        if((csocks[i] = accept(sock, (SOCKADDR *) &csin, &recsize)) != INVALID_SOCKET && i < 5) {
            printf("Client connected\n");
            printf("ip : %s\n", inet_ntoa(csin.sin_addr));
            int x = pthread_create(&thread, NULL, boucleServeur, (void*) &csocks[i]);

            i++;
        }
    }
    pthread_join(thread, NULL);
}


void createSocket(){
    SOCKET sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN sin;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(11111);
    //print port
    printf("Port: %d\nSocket ready...\n", ntohs(sin.sin_port));
    bind(sock, (SOCKADDR*)&sin, sizeof(sin));
    listen(sock, 5);
    //fonction acceptclient
    
    acceptClient(sock);
    
}

int main(int argc, char* argv[])
{
    /* if(argc != 3 || argv[1] == NULL ||argv[2] == NULL){
        printf("Usage: ./main <source> <destination> \n");
        return 1;
    }
    //read the input file from the user
    FILE *input = fopen(argv[1], "r");
    FILE *output = fopen(argv[2], "w");
    //check if the file is empty
    if (input == NULL)
    {
        printf("Error: File is empty or does not exist\n");
        return 1;
    }
    
    int c;
    while ((c = getc(input)) != EOF)
    {
        putc(c,output);
    }
    fclose(output);
    fclose(input);
    printf("File copied successfully\n");
    return 0; */
   createSocket();
   return EXIT_SUCCESS;
}


//function return size of the file
int sizeFile(FILE *file)
{
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}