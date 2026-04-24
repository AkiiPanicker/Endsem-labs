#include <mpi.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char** argv){
    MPI_Init(&argc,&argv);
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
    char s1[100]="string", s2[100]="length";
    int n=strlen(s1), len=n/size;
    char a[10],b[10],res[20];

    MPI_Scatter(s1,len,MPI_CHAR,a,len,MPI_CHAR,0,MPI_COMM_WORLD);
    MPI_Scatter(s2,len,MPI_CHAR,b,len,MPI_CHAR,0,MPI_COMM_WORLD);

    for(int i=0;i<len;i++){
        res[2*i] = a[i];
        res[2*i+1]= b[i];
    }
    char final[200];
    MPI_Gather(res,2*len,MPI_CHAR,final,2*len,MPI_CHAR,0,MPI_COMM_WORLD).
    if(rank==0){
        final[2*n] = '\0';
        printf("%s\n",final);
    }
    MPI_Finalize();

}