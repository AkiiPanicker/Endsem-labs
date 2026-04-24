// nvcc conv1d_const.cu -o conv1d_const
#include <stdio.h>

#define N 8
#define K 3

__constant__ int d_kernel[K];

__global__ void conv1D(int *input, int *output) {
    int i = threadIdx.x;

    if (i < N) {
        int sum = 0;
        for (int j = 0; j < K; j++) {
            if (i - j >= 0)
                sum += input[i - j] * d_kernel[j];
        }
        output[i] = sum;
    }
}

int main() {
    int h_input[N] = {1,2,3,4,5,6,7,8};
    int h_kernel[K] = {1,0,-1};
    int h_output[N];

    int *d_input,*d_output;

    cudaMalloc(&d_input,sizeof(h_input));
    cudaMalloc(&d_output,sizeof(h_output));

    cudaMemcpy(d_input,h_input,sizeof(h_input),cudaMemcpyHostToDevice);
    cudaMemcpyToSymbol(d_kernel,h_kernel,sizeof(h_kernel));

    conv1D<<<1,N>>>(d_input,d_output);

    cudaMemcpy(h_output,d_output,sizeof(h_output),cudaMemcpyDeviceToHost);

    for(int i=0;i<N;i++) printf("%d ",h_output[i]);

    return 0;
}