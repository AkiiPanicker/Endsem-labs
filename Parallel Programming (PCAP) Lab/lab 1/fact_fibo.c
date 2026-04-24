#include <mpi.h>
#include <stdio.h>

int fact(int n){ return (n<=1)?1:n*fact(n-1); }

int fib(int n){
    if(n<=1) return n;
    int a=0,b=1,c;
    for(int i=2;i<=n;i++){ c=a+b; a=b; b=c; }
    return b;
}

int main(int argc,char** argv){
    MPI_Init(&argc,&argv);
    int rank; MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    if(rank%2==0)
        printf("Rank %d: fact=%d\n",rank,fact(rank));
    else
        printf("Rank %d: fib=%d\n",rank,fib(rank));

    MPI_Finalize();
}