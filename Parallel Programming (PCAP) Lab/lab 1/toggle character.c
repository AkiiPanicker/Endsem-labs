#include <mpi.h>
#include <stdio.h>
#include <ctype.h>

int main(int argc,char** argv){
    MPI_Init(&argc,&argv);
    int rank; MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    char str[]="HELLO";
    char c = str[rank];
    if(isupper(c))
        c=tolower(c);
    else
        c=toupper(c);
    printf("Rank %d: %c\n",rank,c);
    MPI_Finalize();

}