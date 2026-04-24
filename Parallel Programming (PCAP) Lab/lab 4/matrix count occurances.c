#include <mpi.h>
#include <stdio.h>

int main(int argc,char** argv){
    MPI_Init(&argc,&argv);
    int rank,x,count=0,total;

    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    int a[9]={1,2,3,1,2,1,3,1,2};

    if(rank==0) x=1; // element to search

    MPI_Bcast(&x,1,MPI_INT,0,MPI_COMM_WORLD);

    for(int i=rank*3;i<(rank+1)*3;i++)
        if(a[i]==x) count++;

    MPI_Reduce(&count,&total,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);

    if(rank==0) printf("Count=%d\n",total);

    MPI_Finalize();
}