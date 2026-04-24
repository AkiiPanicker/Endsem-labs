// nvcc add_col.cu -o add_col
#include <stdio.h>
#define N 3

__global__ void addCol(int *A,int *B,int *C){
    int col = threadIdx.x;

    if(col < N){
        for(int i=0;i<N;i++){
            C[i*N + col] = A[i*N + col] + B[i*N + col];
        }
    }
}

int main(){
    int A[N*N]={1,2,3,4,5,6,7,8,9};
    int B[N*N]={9,8,7,6,5,4,3,2,1};
    int C[N*N];

    int *dA,*dB,*dC;
    cudaMalloc(&dA,sizeof(A));
    cudaMalloc(&dB,sizeof(B));
    cudaMalloc(&dC,sizeof(C));

    cudaMemcpy(dA,A,sizeof(A),cudaMemcpyHostToDevice);
    cudaMemcpy(dB,B,sizeof(B),cudaMemcpyHostToDevice);

    addCol<<<1,N>>>(dA,dB,dC);

    cudaMemcpy(C,dC,sizeof(C),cudaMemcpyDeviceToHost);

    for(int i=0;i<N*N;i++) printf("%d ",C[i]);

    return 0;
}