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

void *whileRead(int *sockfd)
{
    char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        read(*sockfd, buff, sizeof(buff));
        printf("From Client : %s", buff);
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    }
}

void *whileWrite(int *sockfd)
{
    char buff[MAX];
    int n;
    for (;;) {
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
}
void boucleServeur(SOCKET csock)
{
    pthread_t thread;
    pthread_t threadW;
    //thread whileread
    pthread_create(&thread, NULL, whileRead, &csock);
    //thread whilewrite
    pthread_create(&threadW, NULL, whileWrite, &csock);
    //end of thread
    pthread_join(thread, NULL);
    pthread_join(threadW, NULL);

}   

//acceptclient
void acceptClient(SOCKET sock)
{
    SOCKADDR_IN csin;
    SOCKET csock;
    socklen_t recsize = sizeof(csin);
    csock = accept(sock, (SOCKADDR*)&csin, &recsize);
    printf("Client connected\n");
    printf("ip : %s\n", inet_ntoa(csin.sin_addr));
    char buffer[] = "Bonjour le client =)";
    send(csock, buffer, strlen(buffer), 0);
    printf("Message sent\n");
    
    boucleServeur(csock);
    close(sock);
}


void createSocket(){
    SOCKET sock;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN sin;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(11111);
    //print port
    printf("Port: %d\n", ntohs(sin.sin_port));
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
}


