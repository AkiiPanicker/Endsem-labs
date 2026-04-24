// nvcc row_power.cu -o row_power
#include <stdio.h>
#define M 3
#define N 3

__global__ void transform(int *A) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;

    if (idx < M*N) {
        int row = idx / N;
        int val = A[idx];

        int res = 1;
        for (int i = 0; i <= row; i++)
            res *= val;

        A[idx] = res;
    }
}

int main() {
    int A[M*N] = {1,2,3,4,5,6,7,8,9};

    int *d_A;
    cudaMalloc(&d_A, sizeof(A));
    cudaMemcpy(d_A, A, sizeof(A), cudaMemcpyHostToDevice);

    transform<<<1, M*N>>>(d_A);

    cudaMemcpy(A, d_A, sizeof(A), cudaMemcpyDeviceToHost);

    for(int i=0;i<M*N;i++) printf("%d ", A[i]);

    return 0;
}