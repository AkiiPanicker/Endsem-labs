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
    
    int *arr = NULL,x;
    int bsize = size*(sizeof(int)+MPI_BSEND_OVERHEAD);
    char *buf = malloc(bsize);
    MPI_Buffer_attach(buf,size);

    if (rank==0){
        arr=malloc(size*sizeof(int));
        for(int i=0;i<size;i++) arr[i]=i+1;

        for(int i=1;i<size;i++){
            MPI_Bsend(&arr[i],1,MPI_INT,i,0,MPI_COMM_WORLD);
        }

        x=arr[0];
    }
    else{
        MPI_Recv(&x,1,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    }
    if(rank%2==0) printf("Rank %d: %d^2=%d \n",rank,x,x*x);
    else printf("Rank %d: %d^3=%d\n",rank,x,x*x*x);
    MPI_Buffer_detach(&buf,&bsize);
    MPI_Finalize();

    }
