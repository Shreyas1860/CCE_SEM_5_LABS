#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

void searchAndSendOccurrences(FILE *file, int client_socket, const char *searchString, struct sockaddr_in client_address) {
    char buffer[256];
    int count = 0;
    char *line;
    size_t len = 0;

    fseek(file, 0, SEEK_SET);

    while ((getline(&line, &len, file)) != -1) {
        if (strstr(line, searchString) != NULL) {
            count++;
        }
    }

    sprintf(buffer, "Occurrences: %d\n", count);
    sendto(client_socket, buffer, strlen(buffer), 0, (struct sockaddr *)&client_address, sizeof(client_address));
}

int main() {
    int server_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length = sizeof(client_address);

    FILE *file = fopen("data.txt", "r");
    if (!file) {
        perror("File opening error");
        exit(EXIT_FAILURE);
    }

    // Create socket
    server_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (server_socket == -1) {
        perror("Socket creation error");
        exit(EXIT_FAILURE);
    }

    // Bind socket to port
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12345); // Change to desired port
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Binding error");
        exit(EXIT_FAILURE);
    }

    printf("Server listening for connections...\n");

    char filename[256];
    char buffer[256];
    int choice;
    char str1[256];
    char str2[256];

    while (1) {
        recvfrom(server_socket, filename, sizeof(filename), 0, (struct sockaddr *)&client_address, &client_address_length);

        FILE *requested_file = fopen(filename, "r");
        if (!requested_file) {
            sendto(server_socket, "File not present", strlen("File not present"), 0, (struct sockaddr *)&client_address, sizeof(client_address));
            continue;
        }

        printf("Client connected.\n");

        while (1) {
            recvfrom(server_socket, &choice, sizeof(int), 0, (struct sockaddr *)&client_address, &client_address_length);
            switch (choice) {
                case 1: // Search
                    recvfrom(server_socket, str1, sizeof(str1), 0, (struct sockaddr *)&client_address, &client_address_length);
                    searchAndSendOccurrences(requested_file, server_socket, str1, client_address);
                    break;
                case 2: // Replace
                    // Replace operation for UDP (not implemented here)
                    break;
                case 3: // Reorder
                    // Reorder operation for UDP (not implemented here)
                    break;
                case 4: // Exit
                    printf("Client requested termination.\n");
                    fclose(requested_file);
                    close(server_socket);
                    return 0;
            }
        }

        fclose(requested_file);
    }

    fclose(file);
    close(server_socket);

    return 0;
}
