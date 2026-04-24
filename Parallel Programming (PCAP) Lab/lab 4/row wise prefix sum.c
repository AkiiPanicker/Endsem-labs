#include <mpi.h>
#include <stdio.h>

int main(int argc,char** argv){
    MPI_Init(&argc,&argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);

    int a[4][4]={
        {1,2,3,4},
        {1,2,3,1},
        {1,1,1,1},
        {2,1,2,1}
    };

    int row[4],res[4];

    MPI_Scatter(a,4,MPI_INT,row,4,MPI_INT,0,MPI_COMM_WORLD);

    res[0]=row[0];
    for(int i=1;i<4;i++) res[i]=res[i-1]+row[i];

    int out[4][4];
    MPI_Gather(res,4,MPI_INT,out,4,MPI_INT,0,MPI_COMM_WORLD);

    if(rank==0){
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++)
                printf("%d ",out[i][j]);
            printf("\n");
        }
    }

    MPI_Finalize();
}