#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
#define NUM 10 //flights number

//Antonios Mourtzakis 2119074
//Christos Kourkounas 2119227

struct airport
{
    int flight_id;
    char from_city[15];
    char to_city[15];
    int available_seats;
    int price;
};

int main()
{
	//Apo edw kai katw kanoume tis aparetites dhloseis gia ton Socket
    char *ip = "127.0.0.1";
    int port = 5566;

    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];
    int n;

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0)
    {
        perror("[-]Socket error");
        exit(1);
    }
    printf("[+]TCP server socket created.\n");

    memset(&server_addr, '\0', sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = port;
    server_addr.sin_addr.s_addr = inet_addr(ip);

    n = bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (n < 0)
    {
        perror("[-]Bind error");
        exit(1);
    }
    printf("[+]Bind to the port number: %d\n", port);

  //Apo edw kai katw dhlwnw tis pthseis kai tis xwres
  
    srand(time(NULL));
    struct airport arr_flights[NUM];

    int total_profits = 0;//sunolika esoda ths etairias
    int total_tickets = 0;//sunolika eishthria pou poulh8hkan
    int total_request = 0;//sunolikes aithseis

    printf("-------------------------\n");
    printf("The cities are:\n");
    printf("1) Athens\n");
    printf("2) Thessaloniki\n");
    printf("3) London\n");
    printf("4) Paris\n");
    printf("5) Rome\n");
    printf("6) Geneva\n");
    printf("7) Venezia\n");
    printf("8) Madrid\n");
    printf("9) Berlin\n");
    printf("10) Dublin\n\n");
    printf("==============================\n");
    printf("The available flights are: %d\n", NUM);
    printf("==============================\n");

    //Arxikopoioume tis xwres
    int tocity;
    int fromcity;
    for (int i = 0; i < NUM; i++)//gia 10 pthseis
    {
        arr_flights[i].flight_id = i;
        do
        {
            tocity = 1 + rand() % 10;
            fromcity = 1 + rand() % 10;

            if (fromcity == 1)
            {
                 strcpy(arr_flights[i].from_city,"Athens");
            }
            if (fromcity == 2)
            {
                 strcpy(arr_flights[i].from_city,"Thessaloniki");
            }
            if (fromcity == 3)
            {
                 strcpy(arr_flights[i].from_city,"London");
            }
            if (fromcity == 4)
            {
                 strcpy(arr_flights[i].from_city,"Paris");
            }
            if (fromcity == 5)
            {
                 strcpy(arr_flights[i].from_city,"Rome");
            }
            if (fromcity == 6)
            {
                 strcpy(arr_flights[i].from_city,"Geneva");
            }
            if (fromcity == 7)
            {
                 strcpy(arr_flights[i].from_city,"Venezia");
            }
            if (fromcity == 8)
            {
                 strcpy(arr_flights[i].from_city,"Madrid");
            }
            if (fromcity == 9)
            {
                 strcpy(arr_flights[i].from_city,"Berlin");
            }
            if (fromcity == 10)
            {
                 strcpy(arr_flights[i].from_city,"Dublin");
            }
            //----------------------------------------------
            if (tocity == 1)
            {
                 strcpy(arr_flights[i].to_city,"Athens");
            }
            if (tocity == 2)
            {
                 strcpy(arr_flights[i].to_city,"Thessaloniki");
            }
            if (tocity == 3)
            {
                 strcpy(arr_flights[i].to_city,"London");
            }
            if (tocity == 4)
            {
                 strcpy(arr_flights[i].to_city,"Paris");
            }
            if (tocity == 5)
            {
                 strcpy(arr_flights[i].to_city,"Rome");
            }
            if (tocity == 6)
            {
                 strcpy(arr_flights[i].to_city,"Geneva");
            }
            if (tocity == 7)
            {
                 strcpy(arr_flights[i].to_city,"Venezia");
            }
            if (tocity == 8)
            {
                 strcpy(arr_flights[i].to_city,"Madrid");
            }
            if (tocity == 9)
            {
                 strcpy(arr_flights[i].to_city,"Berlin");
            }
            if (tocity == 10)
            {
                 strcpy(arr_flights[i].to_city,"Dublin");
            }

        }while(fromcity == tocity);

        printf("The flight with ID %d takes off from %s and lands to %s\n",arr_flights[i].flight_id, arr_flights[i].from_city, arr_flights[i].to_city );

        arr_flights[i].available_seats = 1 + rand() % 5; //poses diathesimes theseis exei
        printf("The available seats are: %d\n", arr_flights[i].available_seats);

        arr_flights[i].price = 100 + rand() % 400;
        printf("The price is: %d euro\n", arr_flights[i].price);
        printf("--------------------------------------------------------------------\n");

    }

    printf("\n");

    //Perimenw apanthsh apo ton client
    listen(server_sock, 5);
    printf("Listening...\n");

    int client = 0;

    while(1)//H ka8e epanalipsi 8a einai kai enas pelaths
    {
        addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &addr_size);

        printf("################################################################\n");
        printf("[+]Client connected.\n");
        printf("-----------------------\n");

        int tickets_number;
        int flight_number[3];

        //kanw read tous pinakes mou apo ton client
        read(client_sock, &tickets_number, sizeof(int));
        read(client_sock, flight_number, 3*sizeof(int));
        
        int answer=0;

        printf("========================================\n");
        printf("For client %d\n", client+1 );
        printf("=================\n");
        printf("The tickets are: %d\n",tickets_number);
        printf("The flights he/she wants are:\n");

        // edw metrame ton arithmo aithmatwn gia krathsh
        total_request = total_request + tickets_number;
                  
        if(tickets_number == 1)//Ean o pelaths zhthsei 1 eishthrio
        {
            printf("-----------------\n");
            printf("ID: %d\n", flight_number[0]);

            printf("%s --> ", arr_flights[flight_number[0]].from_city);
            printf("%s\n", arr_flights[flight_number[0]].to_city);

            int x = flight_number[0];//dhlonoume ton arithmo ths pthshs me x gia na mh mas mperdeuei

            if (arr_flights[x].available_seats > 0)//Ean uparxoun eleu8eres 8eseis
            {
                //Afairoume ena eishthrio efoson auth h 8esh thn phre o pelaths
                arr_flights[x].available_seats--;

                printf("--Ticket Booking SUCCESSFUL--\n");
                printf("--The cost of ticket is %d euro--\n", arr_flights[x].price);
                printf("(There are %d tickets left for this flight)\n\n", arr_flights[x].available_seats );
                //edw metrame ta sunolika esoda ths aeroporikhs etairias
                total_profits = total_profits + arr_flights[x].price;
                //edw metrame ta sinolika eishthria pou poulhthikan
                total_tickets++;

                answer = answer + arr_flights[x].price;
                write(client_sock, &answer, sizeof(int));

                answer=0;

            }
            else//Ean den uprxoun kenes 8eseis
            {
                printf("--Warning! The tickets of flight:%d have been sold--\n", flight_number[0]);
                printf("--Ticket Booking UNSUCCESSFUL--\n\n");

                write(client_sock, &answer, sizeof(int));
            }

        }
        else if(tickets_number == 2)//Ean o pelaths zhthsei 2 eishthria
        {
            printf("-----------------\n");
            printf("ID: %d\n", flight_number[0]);

            printf("%s --> ", arr_flights[flight_number[0]].from_city);
            printf("%s\n", arr_flights[flight_number[0]].to_city);

            int x = flight_number[0];//dhlonoume ton arithmo ths pthshs me x gia na mh mas mperdeuei

            if (arr_flights[x].available_seats > 0)//Ean uparxoun eleu8eres 8eseis
            {
                //Afairoume ena eishthrio efoson auth h 8esh thn phre o pelaths
                arr_flights[x].available_seats--;

                printf("--Ticket Booking SUCCESSFUL--\n");
                printf("--The cost of ticket is %d euro--\n", arr_flights[x].price);
                printf("(There are %d tickets left for this flight)\n\n", arr_flights[x].available_seats );
                //edw metrame ta sunolika esoda ths aeroporikhs etairias
                total_profits = total_profits + arr_flights[x].price;
                //edw metrame ta sinolika eishthria pou poulhthikan
                total_tickets++;

                answer = answer + arr_flights[x].price;
                write(client_sock, &answer, sizeof(int));

                answer=0;

            }
            else//Ean den uprxoun kenes 8eseis
            {
                printf("--Warning! The tickets of flight:%d have been sold--\n", flight_number[0]);
                printf("--Ticket Booking UNSUCCESSFUL--\n\n");

                write(client_sock, &answer, sizeof(int));
            }

            printf("ID: %d\n", flight_number[1]);

            printf("%s --> ", arr_flights[flight_number[1]].from_city);
            printf("%s\n", arr_flights[flight_number[1]].to_city);

            int y = flight_number[1];//dhlonoume ton arithmo ths pthshs me y gia na mh mas mperdeuei

            if (arr_flights[y].available_seats > 0)//Ean uparxoun eleu8eres 8eseis
            {
                //Afairoume ena eishthrio efoson auth h 8esh thn phre o pelaths
                arr_flights[y].available_seats--;

                printf("--Ticket Booking SUCCESSFUL--\n");
                printf("--The cost of ticket is %d euro--\n", arr_flights[y].price);
                printf("(There are %d tickets left for this flight)\n\n", arr_flights[y].available_seats );
                //edw metrame ta sunolika esoda ths aeroporikhs etairias
                total_profits = total_profits + arr_flights[y].price;
                //edw metrame ta sinolika eishthria pou poulhthikan
                total_tickets++;

                answer = answer + arr_flights[y].price;
                write(client_sock, &answer, sizeof(int));

                answer=0;

            }
            else//Ean den uprxoun kenes 8eseis
            {
                printf("--Warning! The tickets of flight:%d have been sold--\n", flight_number[1]);
                printf("--Ticket Booking UNSUCCESSFUL--\n\n");

                write(client_sock, &answer, sizeof(int));
            }
        }
        else if(tickets_number == 3)//Ean o pelaths zhthsei 3 eishthria
        {
            printf("-----------------\n");
            printf("ID: %d\n", flight_number[0]);

            printf("%s --> ", arr_flights[flight_number[0]].from_city);
            printf("%s\n", arr_flights[flight_number[0]].to_city);

            int x = flight_number[0];//dhlonoume ton arithmo ths pthshs me x gia na mh mas mperdeuei

            if (arr_flights[x].available_seats > 0)//Ean uparxoun eleu8eres 8eseis
            {
                //Afairoume ena eishthrio efoson auth h 8esh thn phre o pelaths
                arr_flights[x].available_seats--;

                printf("--Ticket Booking SUCCESSFUL--\n");
                printf("--The cost of ticket is %d euro--\n", arr_flights[x].price);
                printf("(There are %d tickets left for this flight)\n\n", arr_flights[x].available_seats );
                //edw metrame ta sunolika esoda ths aeroporikhs etairias
                total_profits = total_profits + arr_flights[x].price;
                //edw metrame ta sinolika eishthria pou poulhthikan
                total_tickets++;

                answer = answer + arr_flights[x].price;
                write(client_sock, &answer, sizeof(int));

                answer=0;

            }
            else//Ean den uprxoun kenes 8eseis
            {
                printf("--Warning! The tickets of flight:%d have been sold--\n", flight_number[0]);
                printf("--Ticket Booking UNSUCCESSFUL--\n\n");

                write(client_sock, &answer, sizeof(int));
            }

            printf("ID: %d\n", flight_number[1]);

            printf("%s --> ", arr_flights[flight_number[1]].from_city);
            printf("%s\n", arr_flights[flight_number[1]].to_city);

            int y = flight_number[1];//dhlonoume ton arithmo ths pthshs me y gia na mh mas mperdeuei

            if (arr_flights[y].available_seats > 0)//Ean uparxoun eleu8eres 8eseis
            {
                //Afairoume ena eishthrio efoson auth h 8esh thn phre o pelaths
                arr_flights[y].available_seats--;

                printf("--Ticket Booking SUCCESSFUL--\n");
                printf("--The cost of ticket is %d euro--\n", arr_flights[y].price);
                printf("(There are %d tickets left for this flight)\n\n", arr_flights[y].available_seats );
                //edw metrame ta sunolika esoda ths aeroporikhs etairias
                total_profits = total_profits + arr_flights[y].price;
                //edw metrame ta sinolika eishthria pou poulhthikan
                total_tickets++;

                answer = answer + arr_flights[y].price;
                write(client_sock, &answer, sizeof(int));

                answer=0;

            }
            else//Ean den uprxoun kenes 8eseis
            {
                printf("--Warning! The tickets of flight:%d have been sold--\n", flight_number[1]);
                printf("--Ticket Booking UNSUCCESSFUL--\n\n");

                write(client_sock, &answer, sizeof(int));
            }

            printf("ID: %d\n", flight_number[2]);

            printf("%s --> ", arr_flights[flight_number[2]].from_city);
            printf("%s\n", arr_flights[flight_number[2]].to_city);
            int z = flight_number[2];
            if (arr_flights[z].available_seats > 0)
            {
                arr_flights[z].available_seats--;

                printf("--Ticket Booking SUCCESSFUL--\n");
                printf("--The cost of ticket is %d euro--\n", arr_flights[z].price);
                printf("(There are %d tickets left for this flight)\n\n", arr_flights[x].available_seats );
                //edw metrame ta sunolika esoda ths aeroporikhs etairias
                total_profits = total_profits + arr_flights[z].price;
                //edw metrame ta sinolika eishthria pou poulhthikan
                total_tickets++;

                answer = answer + arr_flights[z].price;
                write(client_sock, &answer, sizeof(int));

                answer=0;

            }
            else
            {
                printf("--Warning! The tickets of flight:%d have been sold--\n", flight_number[2]);
                printf("--Ticket Booking UNSUCCESSFUL--\n\n");

                write(client_sock, &answer, sizeof(int));
            }

        }

        client++;

        close(client_sock);
        
    printf("================================================================\n");
    printf("--> The total profits of the company are: %d €\n",total_profits);
    printf("--> The total requests are: %d\n",total_request);
    printf("--> The total tickets that have been sold are: %d\n",total_tickets);
    printf("--> The total Unsuccessful requests are: %d \n", total_request - total_tickets);

    printf("-----------------------\n");
    printf("[+]Client disconnected.\n");
    printf("################################################################\n");

    }

  return 0;
}
