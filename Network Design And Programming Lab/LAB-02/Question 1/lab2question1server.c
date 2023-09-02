#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

void searchAndSendOccurrences(FILE *file, int client_socket, const char *searchString) {
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
    send(client_socket, buffer, strlen(buffer), 0);
}

void replaceInFile(FILE *file, const char *str1, const char *str2) {
    FILE *tempFile = tmpfile();

    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fseek(file, 0, SEEK_SET);

    while ((read = getline(&line, &len, file)) != -1) {
        char *pos;
        while ((pos = strstr(line, str1)) != NULL) {
            size_t before = pos - line;
            fwrite(line, 1, before, tempFile);
            fwrite(str2, 1, strlen(str2), tempFile);
            line += before + strlen(str1);
        }
        fwrite(line, 1, read, tempFile);
    }

    fseek(file, 0, SEEK_SET);
    fseek(tempFile, 0, SEEK_SET);

    char c;
    while ((c = fgetc(tempFile)) != EOF) {
        fputc(c, file);
    }

    fclose(tempFile);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_length = sizeof(client_address);

    FILE *file = fopen("data.txt", "r+");
    if (!file) {
        perror("File opening error");
        exit(EXIT_FAILURE);
    }

    // Create socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
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

    // Listen for connections
    if (listen(server_socket, 5) == -1) {
        perror("Listening error");
        exit(EXIT_FAILURE);
    }

    printf("Server listening for connections...\n");

    // Accept connections
    client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_length);
    if (client_socket == -1) {
        perror("Accepting connection error");
        exit(EXIT_FAILURE);
    }

    printf("Client connected.\n");

    char filename[256];
    char buffer[256];
    char str1[256];
    char str2[256];
    int choice;

    recv(client_socket, filename, sizeof(filename), 0);

    FILE *requested_file = fopen(filename, "r");
    if (!requested_file) {
        send(client_socket, "File not present", strlen("File not present"), 0);
        fclose(file);
        close(client_socket);
        close(server_socket);
        return 0;
    }

    while (1) {
        recv(client_socket, &choice, sizeof(int), 0);
        switch (choice) {
            case 1: // Search
                recv(client_socket, str1, sizeof(str1), 0);
                searchAndSendOccurrences(requested_file, client_socket, str1);
                break;
            case 2: // Replace
                recv(client_socket, str1, sizeof(str1), 0);
                recv(client_socket, str2, sizeof(str2), 0);
                replaceInFile(requested_file, str1, str2);
                send(client_socket, "String replaced", strlen("String replaced"), 0);
                break;
            case 3: // Reorder
                // Implement reordering here
                break;
            case 4: // Exit
                printf("Client requested termination.\n");
                fclose(requested_file);
                fclose(file);
                close(client_socket);
                close(server_socket);
                return 0;
        }
    }

    fclose(requested_file);
    fclose(file);
    close(client_socket);
    close(server_socket);

    return 0;
}
