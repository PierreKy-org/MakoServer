
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

#include <stdio.h>
#include <stdlib.h>
#define PORT 11111
#define MAX 20
#define SIZE 1024
struct arg_struct {
        SOCKET sock;
        FILE* input;
    };


void *whileWrite(void* arg)
{
    /* char buff[MAX];
    int n;
    for (;;) {
        bzero(buff, sizeof(buff));
        printf("Enter the string : ");
        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(*sockfd, buff, sizeof(buff));
        if ((strncmp(buff, "exit", 4)) == 0) {
            printf("Client Exit...\n");
            break;
        }
    } */
    //cast arg
    int n;
    char data[SIZE] = {0};
    
    struct arg_struct *args = (struct arg_struct*)arg;
    while(fgets(data, SIZE, args->input) != NULL) {
        if (send(args->sock, data, sizeof(data), 0) < 0) {
            perror("[-]Error in sending file.");
            exit(1);
        }
        bzero(data, SIZE);
    }
}


int main(int argc, char* argv[])
{
    struct arg_struct args;

    if(argc != 2 || argv[1] == NULL){
        printf("Usage: ./client <file>\n");
        return 1;
    }
    //read the input file from the user
    args.input = fopen(argv[1], "r");
    //check if the file is empty
    if (args.input == NULL)
    {
        printf("Error: File is empty or does not exist\n");
        return 1;
    }
    
    SOCKADDR_IN sin;
 

    /* Création de la socket */
    args.sock = socket(AF_INET, SOCK_STREAM, 0);

    /* Configuration de la connexion */
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);

    /* Si le client arrive à se connecter */
    if(connect(args.sock, (SOCKADDR*)&sin, sizeof(sin)) != SOCKET_ERROR)
        printf("Connexion à %s sur le port %d\n", inet_ntoa(sin.sin_addr), htons(sin.sin_port));
    else
        printf("Impossible de se connecter\n");

    pthread_t threadW;
    //thread whileread
    //thread whilewrite
    pthread_create(&threadW, NULL, whileWrite, (void*)&args);
    //end of thread
    pthread_join(threadW, NULL);
    close(args.sock);

    printf("File copied successfully\n");
    fclose(args.input);
        
 
    return EXIT_SUCCESS;
}