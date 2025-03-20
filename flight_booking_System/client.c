#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

//Antonios Mourtzakis 2119074
//Christos Kourkounas 2119227


int main(){

    char *ip = "127.0.0.1";
    int port = 5566;

    int sock;
    struct sockaddr_in addr;
    socklen_t addr_size;
    char buffer[1024];
    int n;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("[-]Socket error");
        exit(1);
    }
    printf("[+]TCP server socket created.\n");

    memset(&addr, '\0', sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = port;
    addr.sin_addr.s_addr = inet_addr(ip);

    connect(sock, (struct sockaddr*)&addr, sizeof(addr));
    printf("Connected to the server.\n");
    printf("---------------------------------\n");

    srand(time(NULL));

    int tickets_number;
    int flight_number[3];
    int answer;

    tickets_number = 1 + rand()%3;


    if(tickets_number == 1)//Ean o pelaths thelei 1 eishthrio
    {

        flight_number[0] = rand()%10;
        flight_number[1] = 0;
        flight_number[2] = 0;

    }            
    else if(tickets_number == 2)//Ean o pelaths thelei 2 eishthria
    {
        
        flight_number[0] = rand()%10;
        flight_number[1] = rand()%10;
        flight_number[2] = 0;   

    }             
    else if(tickets_number == 3)//Ean o pelaths thelei 3 eishthria
    {
        flight_number[0] = rand()%10;
        flight_number[1] = rand()%10;
        flight_number[2] = rand()%10;

    }

    //stelnw tous pinakes ston server
    write(sock, &tickets_number, sizeof(int));
    write(sock, flight_number, 3*sizeof(int));

    if(tickets_number == 1)//Ean o pelaths thelei 1 eishthrio
    {
        printf("The client he wants %d ticket\n\n", tickets_number );
        printf("Τhe ticket he wants is the flight with ID:%d\n", flight_number[0] );
        read(sock, &answer, sizeof(int));

        if (answer>0)//ean h apanthsh einai >0 tote shmainei pos exei katoxyrothei timh
        {
            printf("The answer is: --SUCCESSFUL--\n");
            printf("The price is: %d €\n",answer );
            
        }
        else
        {
            printf("The answer is: --UNSUCCESSFUL--\n");
        }

    }            
    else if(tickets_number == 2)//Ean o pelaths thelei 2 eishthria
    {
        printf("The client he wants %d tickets\n\n", tickets_number );
        printf("Τhe tickets he wants are:\n");

        printf("\n-->Flight with ID:%d\n",flight_number[0]);
        read(sock, &answer, sizeof(int));
        if (answer>0)
        {
            printf("The answer is: --SUCCESSFUL--\n");
            printf("The price is: %d €\n",answer );
            
        }
        else
        {
            printf("The answer is: --UNSUCCESSFUL--\n");
        }
        printf("\n-->Flight with ID:%d\n",flight_number[1]);
        read(sock, &answer, sizeof(int));
        if (answer>0)
        {
            printf("The answer is: --SUCCESSFUL--\n");
            printf("The price is: %d €\n",answer );
            
        }
        else
        {
            printf("The answer is: --UNSUCCESSFUL--\n");
        }
   

    }             
    else if(tickets_number == 3)//Ean o pelaths thelei 3 eishthria
    {
        printf("The client he wants %d tickets\n\n", tickets_number );
        printf("Τhe tickets he wants are:\n");

        printf("\n-->Flight with ID:%d\n",flight_number[0]);
        read(sock, &answer, sizeof(int));
        if (answer>0)
        {
            printf("The answer is: --SUCCESSFUL--\n");
            printf("The price is: %d €\n",answer );
            
        }
        else
        {
            printf("The answer is: --UNSUCCESSFUL--\n");
        }
        printf("\n-->Flight with ID:%d\n",flight_number[1]);
        read(sock, &answer, sizeof(int));
        if (answer>0)
        {
            printf("The answer is: --SUCCESSFUL--\n");
            printf("The price is: %d €\n",answer );
            
        }
        else
        {
            printf("The answer is: --UNSUCCESSFUL--\n");
        }
        read(sock, &answer, sizeof(int));
        printf("\n-->Flight with ID:%d\n",flight_number[2]);
        if (answer>0)
        {
            printf("The answer is: --SUCCESSFUL--\n");
            printf("The price is: %d €\n",answer );
            
        }
        else
        {
            printf("The answer is: --UNSUCCESSFUL--\n");
        }

    }
    
    close(sock);
    printf("---------------------------------\n");
    printf("Disconnected from the server.\n");

    return 0;

}
