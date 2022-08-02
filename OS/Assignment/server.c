#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MYPORT 8080
#define BACKLOG 10      // pending connections queue
#define MAXDATASIZE 256 // max nmber of bytes of buffer

int main(void)
{
    int sockfd;
    struct sockaddr_in server_addr; // server address

    // creating daemon

    int daemon_pid = fork();

    if (daemon_pid < 0)
    {
        exit(EXIT_FAILURE);
    }
    else if (daemon_pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    int sid = setsid();
    if (sid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/")) < 0)
    {
        exit(EXIT_FAILURE);
    }

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

    int client_number = 0;

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

        int pid = fork();

        printf("Connection accepted from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        printf("Client number: %d\n", ++client_number);

        while (pid != 0)
        {
            char buffer[MAXDATASIZE];
            char sentMsg[MAXDATASIZE];

            bzero(buffer, MAXDATASIZE);

            strcpy(sentMsg, "Please enter your message: ");

            if (write(new_sockfd, sentMsg, 28) < 0)
            {
                perror("ERROR writing to socket");
            }

            if (read(new_sockfd, buffer, MAXDATASIZE - 1) < 0)
            {
                perror("ERROR reading from socket");
                exit(1);
            }
            printf("Here is the message from %d: %s\n", ntohs(client_addr.sin_port), buffer);
        }

        close(new_sockfd);
    }

    close(sockfd);
}