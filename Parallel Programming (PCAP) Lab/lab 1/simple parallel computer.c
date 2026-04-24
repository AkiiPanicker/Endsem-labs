#include <mpi.h>
#include <stdio.h>
int main(int argc, char** argv){
    MPI_Init(&argc,&argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int a=10 b=5;
    if(rank==0) printf("Add: %d\n",a+b);
    if(rank==1) printf("Sub: %d\n",a-b);
    if(rank==2) printf("Mul: %d\n",a*b);
    if(rank==3) printf("Div: %d\n",a/b);

    MPI_Finalize();
}