// nvcc csr_spmv.cu -o csr_spmv
#include <stdio.h>

__global__ void spmv(int *rowPtr, int *colIdx, int *val, int *x, int *y, int n) {
    int row = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < n) {
        int sum = 0;
        for (int j = rowPtr[row]; j < rowPtr[row+1]; j++) {
            sum += val[j] * x[colIdx[j]];
        }
        y[row] = sum;
    }
}

int main() {
    int n = 3;

    // CSR for matrix:
    // [1 0 2]
    // [0 3 0]
    // [4 0 5]

    int rowPtr[] = {0, 2, 3, 5};
    int colIdx[] = {0, 2, 1, 0, 2};
    int val[]    = {1, 2, 3, 4, 5};

    int x[] = {1, 2, 3};
    int y[3];

    int *d_r, *d_c, *d_v, *d_x, *d_y;

    cudaMalloc(&d_r, sizeof(rowPtr));
    cudaMalloc(&d_c, sizeof(colIdx));
    cudaMalloc(&d_v, sizeof(val));
    cudaMalloc(&d_x, sizeof(x));
    cudaMalloc(&d_y, sizeof(y));

    cudaMemcpy(d_r, rowPtr, sizeof(rowPtr), cudaMemcpyHostToDevice);
    cudaMemcpy(d_c, colIdx, sizeof(colIdx), cudaMemcpyHostToDevice);
    cudaMemcpy(d_v, val, sizeof(val), cudaMemcpyHostToDevice);
    cudaMemcpy(d_x, x, sizeof(x), cudaMemcpyHostToDevice);

    spmv<<<1, n>>>(d_r, d_c, d_v, d_x, d_y, n);

    cudaMemcpy(y, d_y, sizeof(y), cudaMemcpyDeviceToHost);

    for(int i=0;i<n;i++) printf("%d ", y[i]);

    return 0;
}