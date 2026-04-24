#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <mpi.h>

int main(int argc, char** argc){
    MPI_Init(&argc, &agv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    char str[50] = "HELLO";

    if(rank==0){
        MPI_Ssend(str,50,MPI_CHAR,1,0,MPI_COMM_WORLD);
        MPI_Recv(str,50,MPI_CHAR,1,0,MPI_COMM_WORLD,MPI_STATUS,IGNORE);
        printf("Final: %s\n", str);
    }
    else if(rank==1){
        MPI_Recv(str,50,MPI_CHAR,0,0,MPI_COMM_WORLD,MPI_STATUS,IGNORE);
        for(int i=0;str[i];i++){
            str[i]= isupper(str[i])?tolower(str[i]):toupper(str[i]);
        MPI_Ssend(str,50,MPI_CHAR,0,0,MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;

}