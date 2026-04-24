#include <stdio.h>
#include <cuda_runtime.h>
#include <stdlib.h>

__gloabl__ void selection_sort_parallel(int *in, int *out, int n){
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i<n){
        int count = 0;
        for (int j=0; j<n; j++){
            if(in[j] < in[i] || in[j]==in[i] && j<i){
                count++;
            }

        }
        out[count] = in[i];
    }
}

int main(){
    int n ;
    printf("Enter array size:");
    scanf("%d",&n);

    int *h_in = (int*)malloc(n*sizeof(int));
    int *h_out = (int*)malloc(n*sizeof(int));

    printf("Enter elements:");
    for(int i=0; i<n;i++)
    scanf("%d",&h_in[i]);

    int *d_in, *d_out;
    cudaMalloc(&d_in, n*sizeof(int));
    cudaMalloc(&d_out, n*sizeof(int));

    cudaMemcpy(d_in, h_in, n*sizeof(int),cudaMemcpyHostToDevice);
    selection_sort_parallel<<<(n+255)/256,256>>>(d_in,d_out,n);
    cudaMemcpy(h_out,d_out,n*sizeof(int),cudaMemcpyDeviceToHost);

    printf("Sorted:");
    for(int i=0; i<n; i++) printf("%d",h_out[i]);
    printf("\n");

    cudaFree(d_in);
    cudaFree(d_out);
    free(h_in);
    free(h_out);
    return 0;
}