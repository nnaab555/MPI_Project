#include <stdio.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

    int MyRank, Numprocs;
    int i, dest, source;
    int tag = 100;

    char send_message[100];
    char recv_message[100];

    MPI_Status status;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &Numprocs);

    MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);

    snprintf(send_message, sizeof(send_message),
             "%d:Hello", MyRank);

    printf("Process %d started.\n", MyRank);

    for (i = 1; i < Numprocs; i++) {

        dest = (MyRank + i) % Numprocs;
        source = (MyRank - i + Numprocs) % Numprocs;

        MPI_Sendrecv(
            send_message, strlen(send_message) + 1,
            MPI_CHAR, dest, tag,
            recv_message, sizeof(recv_message),
            MPI_CHAR, source, tag,
            MPI_COMM_WORLD, &status
        );

        printf("Process %d received message from Process %d: %s\n",
               MyRank, source, recv_message);
    }

    MPI_Finalize();

    return 0;
}
