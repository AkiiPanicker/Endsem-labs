// nvcc mul_col.cu -o mul_col
#include <stdio.h>
#define N 3

__global__ void mulCol(int *A,int *B,int *C){
    int col = threadIdx.x;

    if(col < N){
        for(int i=0;i<N;i++){
            int sum=0;
            for(int k=0;k<N;k++)
                sum += A[i*N+k]*B[k*N+col];
            C[i*N+col] = sum;
        }
    }
}

int main(){
    int A[N*N]={1,2,3,4,5,6,7,8,9};
    int B[N*N]={1,0,0,0,1,0,0,0,1};
    int C[N*N];

    int *dA,*dB,*dC;
    cudaMalloc(&dA,sizeof(A));
    cudaMalloc(&dB,sizeof(B));
    cudaMalloc(&dC,sizeof(C));

    cudaMemcpy(dA,A,sizeof(A),cudaMemcpyHostToDevice);
    cudaMemcpy(dB,B,sizeof(B),cudaMemcpyHostToDevice);

    mulCol<<<1,N>>>(dA,dB,dC);

    cudaMemcpy(C,dC,sizeof(C),cudaMemcpyDeviceToHost);

    for(int i=0;i<N*N;i++) printf("%d ",C[i]);

    return 0;
}