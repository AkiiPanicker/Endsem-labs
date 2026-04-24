#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char** argv){
    MPI_Init(&argc,&argv);
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    char str[100]="PCAP",c;
    MPI_Scatter(str,1,MPI_CHAR,&c,1,MPI_CHAR,0,MPI_COMM_WORLD);

    char out[100];
    for(int i=0;i<=rank;i++) out[i]=c;

    char final[500];
    int counts[10],displs[10];

    for(int i=0;i<size;i++){
        counts[i]=i+1;
        displs[i]=(i*(i+1))/2;
    }

    MPI_Gatherv(out,rank+1,MPI_CHAR,final,counts,displs,MPI_CHAR,0,MPI_COMM_WORLD);

    if(rank==0){
        final[(size*(size+1))/2]='\0';
        printf("%s\n",final);
    }

    MPI_Finalize();
}