#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

#include <netinet/in.h>

int main()
{
    // Data
    char server_message[256] = "You have reached the server lol";

    // Create a socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Specify an address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Bind
    bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    // Listen
    listen(server_socket, 5);

    // Create client socket that will accept connections
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    // Send
    send(client_socket, server_message, sizeof(server_message), 0);

    // Close
    int shutdown_status = shutdown(server_socket, SHUT_RDWR);
    if (shutdown_status == -1)
    {
        printf("Problem shutting down.\n\n");
    }
    close(server_socket);

    return 0;
}
