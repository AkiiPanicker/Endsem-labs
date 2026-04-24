#include <stdio.h>

__global__ void convulation_1d(float *N, float *M, float *P, int width, int mask_width){
    int i = blockIdx.x * blockDim.x + threadIdx.x;
    if(i<width){
        float value = 0.0f;
        int start = i-(mask_width/2);
        for(int j=0;j<mask_width;j++){
            if(start+j>0 && start+j<width){
                value+=N[start+j] * M[j];
            }
        }
        P[i] = value;
    }
}
int main(){
    int width, mask_width;
    printf("Enter array width and mask width:");
    scanf("%d %d", &width, &mask_width);

    float *h_N = (float*)malloc(width * sizeof(float));
    float *h_M = (float*)malloc(mask_width * sizeof(float));
    float *h_P = (float*)malloc(width * sizeof(float));

    printf("Enter %d array elements:", width);
    for(int i=0; i<width; i++)
    scanf("%f", &h_N[i]);
    printf("Enter %d mask elements:", mask_width);
    for(int j=0;j<mask_width;j++)
    scanf("%f",&h_M[j]);

    float *d_N, *d_M, *d_P;
    cudaMalloc(&d_N, width * sizeof(float))
    cudaMalloc(&d_M, mask_width * sizeof(float))
    cudaMalloc(&d_P, width * sizeof(float))
    cudaMemcpy(d_N, h_N, width * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_M, h_M, mask_width * sizeof(float), cudaMemcpyHostToDevice);

    convulation_1d<<<(width+255)/256,256>>>(d_N, d_M, width, mask_width);
    cudaMemcpy(h_P,d_P,width*sizeof(float),cudaMemcpyDeviceToHost);

    printf("Result :");
    for(int i=0; i<width; i++) printf("%.1f",h_P[i]);
    printf("\n");

    cudaFree(d_N);
    cudaFree(d_M);
    cudaFree(d_P);

    free(h_N);
    free(h_M);
    free(h_P);
    return 0;

}