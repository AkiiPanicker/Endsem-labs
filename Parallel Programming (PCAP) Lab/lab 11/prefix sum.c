// nvcc scan.cu -o scan
#include <stdio.h>

#define N 8

__global__ void scan(int *A) {
    int i = threadIdx.x;

    for (int stride = 1; stride < N; stride *= 2) {
        int val = 0;
        if (i >= stride)
            val = A[i - stride];

        __syncthreads();

        if (i >= stride)
            A[i] += val;

        __syncthreads();
    }
}

int main() {
    int A[N] = {1,2,3,4,5,6,7,8};

    int *d_A;
    cudaMalloc(&d_A,sizeof(A));
    cudaMemcpy(d_A,A,sizeof(A),cudaMemcpyHostToDevice);

    scan<<<1,N>>>(d_A);

    cudaMemcpy(A,d_A,sizeof(A),cudaMemcpyDeviceToHost);

    for(int i=0;i<N;i++) printf("%d ",A[i]);

    return 0;
}