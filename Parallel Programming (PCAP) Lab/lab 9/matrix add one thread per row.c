// nvcc add_row.cu -o add_row
#include <stdio.h>

#define N 3

__global__ void addRow(int *A, int *B, int *C) {
    int row = threadIdx.x;

    if (row < N) {
        for (int j = 0; j < N; j++) {
            C[row*N + j] = A[row*N + j] + B[row*N + j];
        }
    }
}

int main() {
    int A[N*N]={1,2,3,4,5,6,7,8,9};
    int B[N*N]={9,8,7,6,5,4,3,2,1};
    int C[N*N];

    int *dA,*dB,*dC;
    cudaMalloc(&dA,N*N*sizeof(int));
    cudaMalloc(&dB,N*N*sizeof(int));
    cudaMalloc(&dC,N*N*sizeof(int));

    cudaMemcpy(dA,A,sizeof(A),cudaMemcpyHostToDevice);
    cudaMemcpy(dB,B,sizeof(B),cudaMemcpyHostToDevice);

    addRow<<<1,N>>>(dA,dB,dC);

    cudaMemcpy(C,dC,sizeof(C),cudaMemcpyDeviceToHost);

    for(int i=0;i<N*N;i++) printf("%d ",C[i]);

    return 0;
}