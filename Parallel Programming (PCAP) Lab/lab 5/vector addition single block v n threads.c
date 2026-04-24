#include <cuda_runtime.h>
#include <stdlib.h>
__global__ void add_vectors(int *a, int *b, int *c, int n){
    int i = threadIdx.x;
    if (i<n) 
    c[i] = a[i] + b[i];

}
int main(){
    int n;
    printf("Enter vector length N :");
    scanf("%d",&n);
    
    size_t size = n * sizeof(int);
    int *h_a = (int *)malloc(size), *h_b = (int*)malloc(size), *h_c = (int*)malloc(size);

    printf("Enter elements for A and B: ");
    for (int i = 0 ; i<n; i++){
        h_a[i]=i;
        h_b[i]=i*2;
    }
    int *d_a, *d_b, *d_c;
    cudaMalloc(&d_a,size);
    cudaMalloc(&d_b,size);
    cudaMalloc(&d_c,size);

    cudaMemcpy(d_a,h_a,size,cudaMemcpyHostToDevice );
    cudaMemcpy(d_b,h_b,size,cudaMemcpyHostToDevice);

    int threads = 256;
    int blocks = (n+threads-1)/threads;
    add_vectors<<<1,n>>>(d_a,d_b,d_c,n);

    cudaMemcpy(h_c,d_c,size,cudaMemcpyDeviceToHost);
    printf("Last element (index %d): %d \n",n-1,h_c[n-1]);

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    free(h_a);
    free(h_b);
    free(h_c);
    return 0;
}