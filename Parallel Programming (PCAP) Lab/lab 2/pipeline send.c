#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <mpi.h>

int main(int argc, char**argv){
    MPI_Init(&argc,&argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    int size;
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    if(rank==0){
        x=5;
        MPI_Send(&x,1,MPI_INT,1,0,MPI_COMM_WORLD);
    }
    else{
        MPI_Recv(&x,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATS_IGNORE);
        printf("Rank %d got %d \n", rank, x);
        if(rank!=size-1){
            MPI_Send(&x,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
        }
    }
}