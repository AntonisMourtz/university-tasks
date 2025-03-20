#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>


int main(int argc, char* argv[])
{
    // Έλεγχος ορισμάτων γραμμής εντολών
    if (argc != 3) {
        printf("Usage: %s <IP> <PORT>\n", argv[0]);
        exit(1);
    }

    char *ip = argv[1];
    int port = strtol(argv[2], NULL, 10);

    int sock;
    struct sockaddr_in addr;
    socklen_t addr_size;
    char buffer[1024];
    int n;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("[-]Socket error");
        exit(1);
    }
    printf("[+]TCP server socket created.\n");

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);  // Χρήση htons για σωστή διαμόρφωση του port
    addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("[-]Connect error");
        close(sock);
        exit(1);
    }
    printf("Connected to the server.\n");
    printf("---------------------------------\n");

    double number1, number2, answer;
    char op;

    printf("Give me the First number: \n");
    scanf("%lf", &number1);

    printf("Give me the Arithmetic Operation\n");
    printf("Choose one of them:\n");
    printf("'+' for Addition\n");
    printf("'-' for Subtraction\n");
    printf("'*' for Multiplication\n");
    printf("'/' for Division\n");

    // Καθαρισμός του buffer για να αποφευχθεί η ανάγνωση του newline character
    while (getchar() != '\n');

    scanf("%c", &op);

    while (op != '+' && op != '-' && op != '*' && op != '/') {
        printf("Invalid operation. Please choose one of '+', '-', '*', '/':\n");
        while (getchar() != '\n');  // Καθαρισμός του buffer
        scanf("%c", &op);
    }

    printf("Give me the Second number: \n");
    scanf("%lf", &number2);

    if (op == '/' && number2 == 0) {  // Έλεγχος για διαίρεση με μηδέν
        printf("The Division by Zero can't be done!!!\n");
        close(sock);
        exit(1);
    }

    printf("\n----------------\n");
    printf("%.1lf %c %.1lf = ?", number1, op, number2);
    printf("\n----------------\n");

    write(sock, &number1, sizeof(number1));
    write(sock, &number2, sizeof(number2));
    write(sock, &op, sizeof(op));

    read(sock, &answer, sizeof(answer));

    printf("The answer is:\n");
    printf("%.1lf %c %.1lf = %.1lf\n", number1, op, number2, answer);

    close(sock);
    printf("\n---------------------------------\n");
    printf("Disconnected from the server.\n");

    return 0;
}
