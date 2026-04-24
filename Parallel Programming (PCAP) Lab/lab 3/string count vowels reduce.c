#include <mpi.h>
#include <stdio.h>
#include <string.h>

int isv(char c){
    return c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||
           c=='A'||c=='E'||c=='I'||c=='O'||c=='U';
}

int main(int argc,char** argv){
    MPI_Init(&argc,&argv);
    int rank,size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);

    char str[100]="HELLOWORLD",sub[10];
    int n=strlen(str),len=n/size,c=0,total;
    MPI_Scatter(str,len,MPI_CHAR,sub,len,MPI_CHAR,0,MPI_COMM_WORLD);

    for(int i=0;i<len;i++) if(!isv(sub[i])) c++;

    MPI_Reduce(&c,&total,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);
    if(rank==0) printf("Total=%d \n",total);
    MPI_Finalize();
}