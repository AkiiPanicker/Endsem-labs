// nvcc complement.cu -o complement
#include <stdio.h>
#define M 4
#define N 4

__global__ void process(int *A, int *B) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < M*N) {
        int row = idx / N;
        int col = idx % N;

        if (row==0 || col==0 || row==M-1 || col==N-1)
            B[idx] = A[idx];   // border
        else
            B[idx] = ~A[idx];  // 1's complement
    }
}

int main() {
    int A[M*N] = {
        1,2,3,4,
        6,5,8,3,
        2,4,10,1,
        9,1,2,5
    };

    int B[M*N];

    int *d_A,*d_B;
    cudaMalloc(&d_A,sizeof(A));
    cudaMalloc(&d_B,sizeof(B));

    cudaMemcpy(d_A,A,sizeof(A),cudaMemcpyHostToDevice);

    process<<<1,M*N>>>(d_A,d_B);

    cudaMemcpy(B,d_B,sizeof(B),cudaMemcpyDeviceToHost);

    for(int i=0;i<M*N;i++) printf("%d ",B[i]);

    return 0;
}