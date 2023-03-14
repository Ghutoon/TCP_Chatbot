#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

struct client
{
    int id;
    int client_socket_fd;
    /* data */
};

int main()
{
    pid_t childpid;
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    int client_socket;

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8080);
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);

    int bind_status = bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    if (bind_status < 0)
    {
        printf("Binding not succesfull.\n");
        exit(1);
    }

    listen(server_socket, 5);

    int client_mapping[10];
    int cnt = 0;

    while (1)
    {
        client_socket = accept(server_socket, NULL, NULL);
        client_mapping[cnt++] = client_socket;
        if ((childpid = fork()) == 0)
        {
            close(server_socket);

            char buffer[256];
            int recieve_status = recv(client_socket, buffer, sizeof(buffer), 0);
            printf("%s\n", buffer);
            if (recieve_status < 0)
            {
                printf("Message not recieved.\n");
            }
            else
            {
                int destination = buffer[0] - 48;
                int send_stauts = send(client_mapping[destination], buffer, sizeof(buffer), 0);
                if (send_stauts < 0)
                {
                    printf("Message not sent.\n");
                }
            }
        }
    }

    close(client_socket);
}