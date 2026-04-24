#include <stdio.h>
#include <cuda_runtime.h>
#include <stdlib.h>
#include <math.h>

__global__ void compute_sine(float *in, float *out, int n){
    int i = blockIdx.x + blockDim.x * threadIdx.x;
    if(i<n)
    out[i] = sinf(in[i]);
}
int main(){
    int n;
    printf("Enter number of angles: ");
    scanf("%d",&n);

    float *h_in = (float *)malloc(n*sizeof(float));
    float *h_out = (float *)malloc(n*sizeof(float));

    printf("Enter %d angles in radians:");
    for(int i=0; i<n; i++)
    scanf("%f",&h_in[i]);

    float *d_in, *d_out;
    cudaMalloc(&d_in, n*sizeof(float));
    cudaMalloc(&d_out, n*sizeof(float));
    cudaMemcpy(d_in, h_in, n*sizeof(float),cudaMemcpyHostToDevice);

    compute_sine<<<(n+255)/256,256>>>(d_in,d_out,n);
    cudaMemcpy(h_out,d_out,n*sizeof(float),cudaMemcpyDeviceToHost);

    for(int i=0; i<n; i++)
    printf("sin(%.2f)= %.2f\n", h_in[i], h_out[i]);

    cudaFree(d_in);
    cudaFree(d_out);
    free(h_in);
    free(h_out);
    return 0;
}