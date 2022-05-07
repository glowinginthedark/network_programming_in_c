#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>

#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char** argv)
{
    // Store first argument
    char* address = argv[1];

    // Create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Specify remote (server) address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    inet_aton(address, &(server_address.sin_addr));

    // Connect
    connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address));

    // Create request
    char request[] = "GET / HTTP/1.1\r\n\r\n";
    char response[4096];

    // Send
    send(client_socket, request, sizeof(request), 0);

    // Recieve response
    recv(client_socket, &response, sizeof(response), 0);

    // Print response
    printf("Response from server: %s\n\n", response);

    // Close
    close(client_socket);

    // Exit
    return 0;
}

/*

Notes:

char* mystring vs char mystring[]
- These are 2 different types
- sizeof(mystring) with the former will return pointer size
    while with the latter will return the size of the array.
- C will optionally store the size of the array if it is
    static

https://stackoverflow.com/questions/10186765/what-is-the-difference-between-char-array-and-char-pointer-in-c

*/
