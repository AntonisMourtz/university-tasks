#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MY_INFINITY 1000
#define MAX 100

// Function to implement Dijkstra's algorithm and find paths
void Dijkstra_and_Paths(float gr[MAX][MAX], int N, int start, float B[N], float A[N]) {
    float cost[MAX][MAX];
    float pred[MAX], apost[MAX];
    float vis[MAX], apost2;
    int count, nextkomb, i, j;

    // Initialize cost matrix
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (gr[i][j] == 0)
                cost[i][j] = MY_INFINITY;
            else
                cost[i][j] = gr[i][j];
        }
    }

    // Initialize distances, predecessors, and visited array
    for (i = 0; i < N; i++) {
        apost[i] = cost[start][i];
        pred[i] = start;
        vis[i] = 0;
    }

    apost[start] = 0;
    vis[start] = 1;
    count = 1;

    // Dijkstra's algorithm
    while (count < N - 1) {
        apost2 = MY_INFINITY;

        // Find the next node with the smallest distance
        for (i = 0; i < N; i++) {
            if (apost[i] < apost2 && !vis[i]) {
                apost2 = apost[i];
                nextkomb = i;
            }
        }

        vis[nextkomb] = 1;

        // Update distances
        for (i = 0; i < N; i++) {
            if (!vis[i]) {
                if (apost2 + cost[nextkomb][i] < apost[i]) {
                    apost[i] = apost2 + cost[nextkomb][i];
                    pred[i] = nextkomb;
                }
            }
        }
        count++;
    }

    // Ask user for destination station
    int y = start;
    int destination;
    do {
        printf("Which station do you want to go to? (0-%d, excluding %d): ", N - 1, y);
        scanf("%d", &destination);
        if (destination >= N || destination < 0 || destination == y) {
            printf("Invalid input! Please enter a valid station number.\n");
        }
    } while (destination >= N || destination < 0 || destination == y);

    // Print distance to destination
    printf("\nDistance from %d to %d: %.2f km\n", y, destination, apost[destination]);
    printf("\n===============================================\n");
    printf("Line 1");
    printf("\n===============================================\n");

    // Calculate and print path for Line 1 (forward direction)
    float a1 = 0, b1 = 0;
    if (y < destination) {
        for (i = y; i < destination; i++) {
            printf("%d --> %d : %.2f km || Waiting time: %.2f min\n", i, i + 1, B[i], A[i]);
            a1 += A[i];
            b1 += B[i];
        }
    } else if (y > destination) {
        for (i = y; i < N; i++) {
            printf("%d --> %d : %.2f km || Waiting time: %.2f min\n", i, (i + 1) % N, B[i], A[i]);
            a1 += A[i];
            b1 += B[i];
        }
        for (i = 0; i < destination; i++) {
            printf("%d --> %d : %.2f km || Waiting time: %.2f min\n", i, i + 1, B[i], A[i]);
            a1 += A[i];
            b1 += B[i];
        }
    }

    printf("\n------------------------------------\n");
    printf("Total time for Line 1: %.2f min\n", a1);

    // Calculate and print path for Line 2 (backward direction)
    printf("\n===============================================\n");
    printf("Line 2");
    printf("\n===============================================\n");

    float a2 = 0, b2 = 0;
    if (y > destination) {
        for (i = y; i > destination; i--) {
            printf("%d --> %d : %.2f km || Waiting time: %.2f min\n", i, i - 1, B[i - 1], A[i - 1]);
            a2 += A[i - 1];
            b2 += B[i - 1];
        }
    } else if (y < destination) {
        for (i = y; i >= 0; i--) {
            printf("%d --> %d : %.2f km || Waiting time: %.2f min\n", i, (i - 1 + N) % N, B[(i - 1 + N) % N], A[(i - 1 + N) % N]);
            a2 += A[(i - 1 + N) % N];
            b2 += B[(i - 1 + N) % N];
        }
        for (i = N - 1; i > destination; i--) {
            printf("%d --> %d : %.2f km || Waiting time: %.2f min\n", i, i - 1, B[i - 1], A[i - 1]);
            a2 += A[i - 1];
            b2 += B[i - 1];
        }
    }

    printf("\n------------------------------------\n");
    printf("Total time for Line 2: %.2f min\n", a2);

    // Determine the best path
    printf("\n================================================================\n");
    if (a1 < a2) {
        printf("The best path is Line 1\n");
        printf("Total distance: %.2f km\n", b1);
        printf("Total time: %.2f min\n", a1);
    } else {
        printf("The best path is Line 2\n");
        printf("Total distance: %.2f km\n", b2);
        printf("Total time: %.2f min\n", a2);
    }
}

int main() {
    int i, j;
    float delay = 1; // Delay per station
    int N = 10;      // Number of stations
    float gr[MAX][MAX];
    float A[N];      // Waiting time per station
    float B[N];      // Distance between stations

    int speed = 50; // Train speed in km/h
    srand(time(NULL));

    // Initialize the graph with random distances
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (i == j) {
                gr[i][j] = 0;
            } else {
                gr[i][j] = 1 + (float)rand() / (RAND_MAX)*4; // Random distance between 1 and 5 km
            }
        }
    }

    // Make the graph cyclic
    gr[0][N - 1] = gr[N - 1][0] = 1 + (float)rand() / (RAND_MAX)*4;

    // Print the graph
    printf("\n====================\n");
    printf("The Graph: ");
    printf("\n====================\n");
    for (i = 0; i < N; i++) {
        printf("|");
        for (j = 0; j < N; j++) {
            printf("%.2f |", gr[i][j]);
        }
        printf("\n");
    }

    // Calculate distances and waiting times
    for (i = 0; i < N; i++) {
        B[i] = gr[i][(i + 1) % N]; // Distance to next station
        A[i] = (B[i] / speed) * 60 + delay; // Waiting time in minutes
    }

    // Ask user for current station
    int u;
    do {
        printf("\nWhat station are you at? (0-%d): ", N - 1);
        scanf("%d", &u);
        if (u >= N || u < 0) {
            printf("Invalid input! Please enter a valid station number.\n");
        }
    } while (u >= N || u < 0);

    // Run Dijkstra and find paths
    Dijkstra_and_Paths(gr, N, u, B, A);

    return 0;
}
