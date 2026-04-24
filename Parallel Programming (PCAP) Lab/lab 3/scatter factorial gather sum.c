#include <mpi.h>
#include <stdio.h>

int fact(int n){ return (n<=1)?1:n*fact(n-1);}
int main(int argc,char** argv){
    MPI_Init(&argc,&argv);
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);    
    int a[100],x,res,sum=0;
    if(rank==0){
        for(int i=0; i<size; i++) a[i]=i+1;
    }
    MPI_Scatter(a,1,MPI_INT,&x,1,MPI_INT,0,MPI_COMM_WORLD);
    res=fact(x);
    MPI_Gather(&res,1,MPI_INT,a,1,MPI_INT,0,MPI_COMM_WORLD);
    if(rank==0){
        for(int i=0;i<size;i++) sum+=a[i];
        printf("Sum=%d\n");
    }
    MPI_Finalize();
    return 0;

}