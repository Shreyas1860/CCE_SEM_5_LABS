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
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345);
    server_address.sin_addr.s_addr = inet_addr("172.16.57.196");

    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Connection error");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server.\n");

    char filename[256];
    int choice;
    char str1[256];
    char str2[256];

    printf("Enter the filename: ");
    scanf("%s", filename);

    send(client_socket, filename, strlen(filename), 0);

    // Display menu and get user choice
    while (1) {
        printf("Menu:\n");
        printf("1. Search\n");
        printf("2. Replace\n");
        printf("3. Reorder\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        send(client_socket, &choice, sizeof(int), 0);

        switch (choice) {
            case 1: // Search
                printf("Enter string to search: ");
                scanf("%s", str1);
                send(client_socket, str1, strlen(str1), 0);

                char searchResult[256];
                recv(client_socket, searchResult, sizeof(searchResult), 0);
                printf("Search result: %s\n", searchResult);
                break;
            case 2: // Replace
                printf("Enter string to replace: ");
                scanf("%s", str1);
                printf("Enter replacement string: ");
                scanf("%s", str2);
                send(client_socket, str1, strlen(str1), 0);
                send(client_socket, str2, strlen(str2), 0);

                char replaceResult[256];
                recv(client_socket, replaceResult, sizeof(replaceResult), 0);
                printf("Replace result: %s\n", replaceResult);
                break;
            case 3: // Reorder
                // Implement reordering if needed
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
