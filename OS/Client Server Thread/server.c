#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<pthread.h>

#define MYPORT 8080
#define BACKLOG 10      // pending connections queue
#define MAXDATASIZE 256 // max nmber of bytes of buffer
int client_number = 0;
int clientaddr[100];
struct client{
    struct sockaddr_in clientsock;
    int sock;
}clientid[100];

void* serverThread(void* sock){
    int newSocket=*((int*)sock);
    char buffer[MAXDATASIZE];
    bzero(buffer, MAXDATASIZE);
    
    recv(newSocket , buffer , 2000 , 0);
    int i;
    for(i=0;i<100;i++){
        if(clientid[i].sock=newSocket)break;
    }
    printf("Here is the message from %d: %s\n",ntohs(clientid[i].clientsock.sin_port), buffer);
}

int main(void)
{
    int sockfd;
    struct sockaddr_in server_addr; // server address
    // socket opening
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

    
    pthread_t serv[100];
    int i=0;
    while (1)
    {
        socklen_t sin_size;
        struct sockaddr_in client_addr; // connector's address

        // accept new client
        int new_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
        printf("Connection accepted from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        clientid[client_number++].clientsock=client_addr;
        clientid[client_number].sock=new_sockfd;
        //printf("Client number: %d\n", ++client_number);
        if (new_sockfd < 0)
        {
            printf("Error accepting client\n");
            exit(1);
        }

        if(pthread_create(&serv[i++],NULL,serverThread,&new_sockfd)!=0){
            printf("Failed to create thread\n");
        }
       

        if(i>=100){//100 server thread created
            int i=0;
            while(i<50){
                pthread_join(serv[i++],NULL);
            }
            i=0;
        }
        close(new_sockfd);
    }

    close(sockfd);
}