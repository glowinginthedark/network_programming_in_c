#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

#include <netinet/in.h>

int main()
{
    // Create a socket
    int network_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Specify an address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Connect
    int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    if (connection_status == -1)
    {
        printf("Error occured while trying to connect...\n\n");
    }

    // Recieve data
    char server_response[256];
    recv(network_socket, &server_response, sizeof(server_response), 0);

    // Print response
    printf("The server sent back: %s\n\n", server_response);

    // Close
    close(network_socket);

    return 0;
}
