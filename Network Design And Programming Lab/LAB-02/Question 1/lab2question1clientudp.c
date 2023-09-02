#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    int client_socket;
    struct sockaddr_in server_address;

    // Create socket
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket == -1) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    // Set server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345);
    server_address.sin_addr.s_addr = inet_addr("172.16.57.162");

    printf("Enter the filename: ");
    char filename[256];
    scanf("%s", filename);

    sendto(client_socket, filename, strlen(filename), 0, (struct sockaddr *)&server_address, sizeof(server_address));

    // Display menu and get user choice
    while (1) {
        printf("Menu:\n");
        printf("1. Search\n");
        printf("2. Replace\n");
        printf("3. Reorder\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        int choice;
        scanf("%d", &choice);

        sendto(client_socket, &choice, sizeof(int), 0, (struct sockaddr *)&server_address, sizeof(server_address));

        switch (choice) {
            case 1: // Search
                printf("Enter string to search: ");
                char str1[256];
                scanf("%s", str1);
                sendto(client_socket, str1, strlen(str1), 0, (struct sockaddr *)&server_address, sizeof(server_address));

                char searchResult[256];
                recvfrom(client_socket, searchResult, sizeof(searchResult), 0, NULL, NULL);
                printf("Search result: %s\n", searchResult);
                break;
            case 2: // Replace
                // Replace operation for UDP (not implemented here)
                break;
            case 3: // Reorder
                // Reorder operation for UDP (not implemented here)
                break;
            case 4: // Exit
                printf("Exiting...\n");
                close(client_socket);
                return 0;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    close(client_socket);

    return 0;
}
