#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main()
{
    int client_socket;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    int connection_status = connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    if (connection_status < 0)
    {
        printf("Connection not esablished.\n");
        exit(1);
    }
    else
    {
        printf("Connection established with server.\n");
    }
    char buffer[256];
    while(fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        int recieved_status = recv(client_socket, buffer, sizeof(buffer), 0);
        if(recieved_status < 0)
        {
            printf("Message not recieved.\n");
        }

        int send_status = recv(client_socket, buffer, sizeof(buffer), 0);
        if (send_status < 0)
        {
            printf("Message not sent.\n");
        }
    }

    close(client_socket);
    
    return 0;
}