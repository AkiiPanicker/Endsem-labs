#include <stdio.h>
#include <cuda_runtime.h>
#include <stdlib.h>

__global__ void odd_even_transposition(int *data, int n, int phase){
    int i= blockIdx.x * blockDim.x + threadIdx.x;
    int index = 2*i + (phase % 2);
    if(index  <n-1){
        if(data[index]>data[index+1]){
            int temp = data[index];
            data[index] = data[index+1];
            data[index+1] = temp;
        }
    }
}
int main(){
    int n;
    printf("Enter array size:");
    scanf("%d",&n);

    int *h_data = (int*)malloc(n*sizeof(int));
    printf("Enter elements:");
    for(int i=0; i<n; i++)
    scanf("%d",&h_data[i]);

    int *d_data;
    cudaMalloc(&d_data,n*sizeof(data));
    cudaMemcpy(d_data,h_data, n*sizeof(int), cudaMemcpyHostToDevice);

    for(int phase=0;phase<n;phase++){
        odd_even_transposition<<<(n/2+255)/256,256>>>(d_data,n,phase);
        cudaDeviceSynchronize();

    }

    cudaMemcpy(h_data,d_data,n*sizeof(int),cudaMemcpyDeviceToHost);
    printf("Sorted:");
    for(int i=0;i<n;i++)printf("%d",h_data[i]);
    printf("\n");

    cudaFree(d_data);
    free(h_data);
    return 0;

}