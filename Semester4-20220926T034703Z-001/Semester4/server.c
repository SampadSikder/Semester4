#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MYPORT 8080
#define BACKLOG 10      // pending connections queue
#define MAXDATASIZE 256 // max nmber of bytes of buffer
int client_number = 0;
int clientaddr[100];
pthread_t serv[100];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
struct client
{
    char name[1024];
    struct sockaddr_in clientsock;
    int sock;
    int c_num;
} clientid[100];
void sendToClient(struct client *c_id, struct client reciever)
{
    // printf("Sending to %s");
    char rcvd[1024];
    int len = recv(c_id->sock, rcvd, 1024, 0);
    rcvd[len] = '\0';
    char snd[2048] = "";
    sprintf(snd, "%s: %s", c_id->name, rcvd);
    send(reciever.sock, snd, strlen(snd), 0);
}
void sendToAll(struct client *c_id)
{
    printf("\nSending to all\n");
    char rcvd[1024];
    int len = recv(c_id->sock, rcvd, 1024, 0);
    rcvd[len] = '\0';
    char snd[2048] = "";
    sprintf(snd, "%s: %s", c_id->name, rcvd);
    for (int i = 0; i < client_number; i++)
    {
        if (c_id->sock != clientid[i].sock)
        {
            send(clientid[i].sock, snd, strlen(snd), 0);
        }
    }
}
void *serverThread(void *num)
{
    struct client *c_id = (struct client *)num;
    printf("Recieving from %s\n", c_id->name);
    while (1)
    {
        char to[101];
        int len = recv(c_id->sock, to, 101, 0);
        to[len] = '\0';
        if (!strcmp(to, "Quit"))
        {
            send(c_id->sock, to, 101, 0);
            break;
        }

        printf("%s Sending to: ", c_id->name);
        puts(to);
        if (!strcmp(to, "@all"))
        {
            sendToAll(c_id);
        }

        for (int i = 0; i < client_number; i++)
        {
            if (!strcmp(to, clientid[i].name))
            {
                sendToClient(c_id, clientid[i]);
            }
        }
    }
    printf("%s quit\n", c_id->name);
    close(c_id->sock);
}

int main(void)
{
    int sockfd;
    struct sockaddr_in server_addr; // server address
    // socket opening
    int len = 1;
    setsockopt(sockfd, NULL, SO_REUSEADDR | SO_REUSEPORT, &len, sizeof(len));
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("ERROR opening socket");
        exit(1);
    }

    bzero((char *)&server_addr, sizeof(server_addr)); // zeroing the rest

    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(MYPORT); // to order the network bytes as it is sent in reverse

    // binding

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0)
    {
        perror("ERROR on binding");
        exit(1);
    }

    // Listen

    if (listen(sockfd, BACKLOG) < 0)
    {
        perror("ERROR on listen");
        exit(1);
    }
    // accepting multiple connections

    int i = 0;
    while (1)
    {
        socklen_t sin_size;
        struct sockaddr_in client_addr; // connector's address

        // accept new client
        int new_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
        if (new_sockfd < 0)
        {
            printf("Error accepting client\n");
            exit(1);
        }
        // printf("Connection accepted from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        clientid[client_number].sock = new_sockfd;
        clientid[client_number].clientsock = client_addr;
        clientid[client_number].c_num = client_number;
        char name[100];
        int len = recv(clientid[client_number].sock, name, 100, 0);
        name[len] = '\0';
        sprintf(clientid[client_number].name, "@%s", name);
        printf("Client number: %d\n", client_number + 1);
        printf("Joined: ");
        puts(clientid[client_number].name);

        if (pthread_create(&serv[client_number], NULL, serverThread, &clientid[client_number]) != 0)
        {
            printf("Failed to create thread\n");
        }
        client_number++;
    }
    for (int i = 0; i < client_number; i++)
    {
        pthread_join(serv[i], NULL);
    }
}
