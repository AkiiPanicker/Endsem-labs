// nvcc word_count.cu -o word_count
#include <stdio.h>
#include <string.h>

__global__ void countWord(char *text, char *word, int *count, int n, int m) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i <= n - m) {
        int match = 1;
        for (int j = 0; j < m; j++) {
            if (text[i + j] != word[j]) {
                match = 0;
                break;
            }
        }
        if (match) atomicAdd(count, 1);
    }
}

int main() {
    char text[] = "this is a test this is a test this";
    char word[] = "this";

    int n = strlen(text);
    int m = strlen(word);

    char *d_text, *d_word;
    int *d_count, h_count = 0;

    cudaMalloc(&d_text, n);
    cudaMalloc(&d_word, m);
    cudaMalloc(&d_count, sizeof(int));

    cudaMemcpy(d_text, text, n, cudaMemcpyHostToDevice);
    cudaMemcpy(d_word, word, m, cudaMemcpyHostToDevice);
    cudaMemcpy(d_count, &h_count, sizeof(int), cudaMemcpyHostToDevice);

    countWord<<<(n+255)/256, 256>>>(d_text, d_word, d_count, n, m);

    cudaMemcpy(&h_count, d_count, sizeof(int), cudaMemcpyDeviceToHost);

    printf("Count = %d\n", h_count);

    cudaFree(d_text); cudaFree(d_word); cudaFree(d_count);
    return 0;
}