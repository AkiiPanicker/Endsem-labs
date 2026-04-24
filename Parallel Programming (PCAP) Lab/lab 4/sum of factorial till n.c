#include <mpi.h>
#include <stdio.h>

int fact(int n){ return (n<=1)?1:n*fact(n-1); }

int main(int argc,char** argv){
    MPI_Init(&argc,&argv);
    int rank,size,local,sum;

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    local=fact(rank+1);
    MPI_Scan(&local,&sum,1,MPI_INT,MPI_SUM,MPI_COMM_WORLD);
    if(rank==size-1){
        printf("Result = %d \n",sum);
    }
    MPI_Finalize();
}
