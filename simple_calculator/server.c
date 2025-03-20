#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

// Antonios Mourtzakis 2119074
// Christos Kourkounas 2119227

int main(int argc, char* argv[])
{
    // Έλεγχος ορισμάτων γραμμής εντολών
    if (argc != 2) {
        printf("Usage: %s <PORT>\n", argv[0]);
        exit(1);
    }

    char *ip = "127.0.0.1";
    int port = strtol(argv[1], NULL, 10);

    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];
    int n;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("[-]Socket error");
        exit(1);
    }
    printf("[+]TCP server socket created.\n");

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);  // Χρήση htons για σωστή διαμόρφωση του port
    server_addr.sin_addr.s_addr = inet_addr(ip);

    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("[-]Bind error");
        close(server_sock);
        exit(1);
    }
    printf("[+]Bind to the port number: %d\n", port);

    printf("[+]Ip address: 127.0.0.1\n");
    printf("\n");

    listen(server_sock, 5);
    printf("Listening...\n");

    while (1) {
        addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);

        printf("################################################################\n");
        printf("[+]Client connected.\n");
        printf("-----------------------\n");

        double number1, number2, answer;
        char op;

        read(client_sock, &number1, sizeof(number1));
        read(client_sock, &number2, sizeof(number2));
        read(client_sock, &op, sizeof(op));

        if (op == '+') {
            answer = number1 + number2;
        } else if (op == '-') {
            answer = number1 - number2;
        } else if (op == '*') {
            answer = number1 * number2;
        } else if (op == '/') {
            if (number2 == 0) {
                printf("Division by zero attempted. Sending error to client.\n");
                answer = 0;  // Στέλνουμε 0 σε περίπτωση διαίρεσης με μηδέν
            } else {
                answer = number1 / number2;
            }
        }

        write(client_sock, &answer, sizeof(answer));

        close(client_sock);
        printf("-----------------------\n");
        printf("[+]Client disconnected.\n");
        printf("################################################################\n");
    }

    close(server_sock);
    return 0;
}
