#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string.h>

#define MYPORT 8080     // the port users will be connecting to
#define BACKLOG 10      // how many pending connections queue will hold
#define MAXDATASIZE 256 // max number of bytes we can get at once
void str_trim(char *arr, int length)
{
    int i;
    for (i = 0; i < length; i++)
    { // trim \n
        if (arr[i] == '\n')
        {
            arr[i] = '\0';
            break;
        }
    }
}
void *recieve(void *sockfd)
{
    int sock = *(int *)sockfd;
    while (1)
    {
        char rcvd[1024];
        int len = recv(sock, rcvd, 1024, 0);
        rcvd[len] = '\0';
        printf("%s\n", rcvd);
        if (!strcmp(rcvd, "Quit"))
        {
            exit(0);
        }
    }
}
void send_message(int sockfd)
{
    char message[1024];
    fgets(message, sizeof(message), stdin);
    str_trim(message, strlen(message));
    send(sockfd, message, strlen(message), 0);
}
int main(void)
{
    int sockfd, new_sockfd;         // listen on sockfd, new connection on new_sockfd
    struct sockaddr_in server_addr; // connector's address information
    char name[100];
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    str_trim(name, strlen(name));
    int sin_size;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("ERROR opening socket");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(MYPORT);

    if (new_sockfd = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Error in connection");
    }
    pthread_t thread; // thread running parallely to recieve
    pthread_create(&thread, NULL, recieve, (void *)&sockfd);
    send(sockfd, name, 100, 0);
    char reciever[101];

    while (1)
    {
        // printf("Send to: ");
        fgets(reciever, sizeof(reciever), stdin);
        str_trim(reciever, strlen(reciever));
        printf(": ");
        send(sockfd, reciever, 101, 0);
        send_message(sockfd);
    }
    close(sockfd);
    pthread_exit(NULL);
    exit(1);
    return 0;
}
