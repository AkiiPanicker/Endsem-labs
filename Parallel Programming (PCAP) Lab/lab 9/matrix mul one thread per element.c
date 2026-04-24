// nvcc mul_elem.cu -o mul_elem
#include <stdio.h>
#define N 3

__global__ void mulElem(int *A,int *B,int *C){
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if(idx < N*N){
        int row = idx / N;
        int col = idx % N;

        int sum=0;
        for(int k=0;k<N;k++)
            sum += A[row*N+k]*B[k*N+col];

        C[idx] = sum;
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

    mulElem<<<1,N*N>>>(dA,dB,dC);

    cudaMemcpy(C,dC,sizeof(C),cudaMemcpyDeviceToHost);

    for(int i=0;i<N*N;i++) printf("%d ",C[i]);

    return 0;
}