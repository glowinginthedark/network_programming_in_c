#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <netinet/in.h>

int main()
{
    // Open HTML file
    FILE* html_data = fopen("index.html", "r");

    // Load up the HTML in a string variable
    char response_data[1024];
    fgets(response_data, 1024, html_data);

    // Create HTTP packet
    char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";
    strcat(http_header, response_data);

    // Create socket
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
    
    // Accept new requests forever. Is this iterative?
    while (1)
    {
        // Accept request and respond with http_header
        client_socket = accept(server_socket, NULL, NULL);
        send(client_socket, http_header, sizeof(http_header), 0);

        // Close client socket
        close(client_socket);
    }

    // Close server socket
    close(server_socket);

    // Exit
    return 0;
}
