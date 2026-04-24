// nvcc rs_string.cu -o rs_string
#include <stdio.h>
#include <string.h>

__global__ void buildRS(char *S, char *RS, int n) {
    int i = threadIdx.x;  // one thread per block (small input)

    if (i < n) {
        int offset = (i * (i + 1)) / 2;  // prefix sum position

        for (int j = 0; j <= i; j++) {
            RS[offset + j] = S[j];
        }
    }
}

int main() {
    char S[] = "PCAP";
    int n = strlen(S);

    int out_len = n * (n + 1) / 2;

    char *d_S, *d_RS, RS[out_len + 1];

    cudaMalloc(&d_S, n);
    cudaMalloc(&d_RS, out_len);

    cudaMemcpy(d_S, S, n, cudaMemcpyHostToDevice);

    buildRS<<<1, n>>>(d_S, d_RS, n);

    cudaMemcpy(RS, d_RS, out_len, cudaMemcpyDeviceToHost);
    RS[out_len] = '\0';

    printf("RS = %s\n", RS);

    cudaFree(d_S); cudaFree(d_RS);
    return 0;
}

/*
nvcc word_count.cu -o word_count
./word_count

nvcc rs_string.cu -o rs_string
./rs_string

*/