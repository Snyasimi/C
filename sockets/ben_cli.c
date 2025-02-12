#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    
    // Create socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\nSocket creation error\n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "192.168.164.191", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address / Address not supported\n");
        return -1;
    }
    
    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection failed\n");
        return -1;
    }
    
    printf("Connected to server.\n");

    while (1) {
        // Send message to the server
        printf("Client: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        send(sock, buffer, strlen(buffer), 0);
        
        // Check if the client wants to end the chat
        if (strncmp(buffer, "bye", 3) == 0) {
            printf("Chat ended by client.\n");
            break;
        }

        memset(buffer, 0, BUFFER_SIZE);
        // Receive a response from the server
        int valread = read(sock, buffer, BUFFER_SIZE);
        printf("Server: %s\n", buffer);
        
        // Check if the server wants to end the chat
        if (strncmp(buffer, "bye", 3) == 0) {
            printf("Chat ended by server.\n");
            break;
        }
    }

    // Close the socket
    close(sock);
    return 0;
}
