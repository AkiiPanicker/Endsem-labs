#include <mpi.h>
#include <stdio.h>
int main(int argc,char** argv){
    MPI_Init(&argc,&argv);
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);   
    int M=2;
    int a[100],sub[10];
    float avg, all[10],tot=0;

    if(rank==0){
        for(int i=0;i<size*M;i++) a[i]=i+1;
    }
    MPI_Scatter(a,M,MPI_INT,sub,M,MPI_INT,0,MPI_COMM_WORLD);
    int s=0;
    for(int i=0;i<M;i++) s+=sub[i];
    avg=(float)s/M;
    MPI_Gather(&avg,1,MPI_FLOAT,all,1,MPI_FLOAT,0,MPI_COMM_WORLD);
    if(rank==0){
        for(int i=0; i<size;i++) tot+=all[i];
        printf("Total avg=%f\n",tot/size);
    }
    MPI_Finalize();
    return 0;
}