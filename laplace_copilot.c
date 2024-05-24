#include <stdio.h>
#include <stdlib.h>
#define WIDTH 332
#define HEIGHT 271
void applyLaplacianFilter(unsigned char* image, unsigned char* filteredImage) {
    int i, j;
    int pixel;
    int sum;
    for (i = 1; i < HEIGHT - 1; i++) {
        for (j = 1; j < WIDTH - 1; j++) {
            sum = 0;
            // Apply the laplacian filter
            sum += image[(i - 1) * WIDTH + (j - 1)] * 0;
            sum += image[(i - 1) * WIDTH + j] * -1;
            sum += image[(i - 1) * WIDTH + (j + 1)] * 0;
            sum += image[i * WIDTH + (j - 1)] * -1;
            sum += image[i * WIDTH + j] * 4;
            sum += image[i * WIDTH + (j + 1)] * -1;
            sum += image[(i + 1) * WIDTH + (j - 1)] * 0;
            sum += image[(i + 1) * WIDTH + j] * -1;
            sum += image[(i + 1) * WIDTH + (j + 1)] * 0;
            // Clamp the result to the range [0, 255]
            if (sum < 0) {
                sum = 0;
            } else if (sum > 255) {
                sum = 255;
            }
            // Store the filtered pixel value
            filteredImage[i * WIDTH + j] = (unsigned char)sum;
        }
    }
}

int main() {
    FILE* inputFile = fopen("zezo_bytes.bin", "rb");
    FILE* outputFile = fopen("output_image.bmp", "wb");

    if (inputFile == NULL || outputFile == NULL) {
        printf("Failed to open input or output file.\n");
        return 1;
    }

    unsigned char* image = (unsigned char*)malloc(WIDTH * HEIGHT);
    unsigned char* filteredImage = (unsigned char*)malloc(WIDTH * HEIGHT);

    if (image == NULL || filteredImage == NULL) {
        printf("Failed to allocate memory.\n");
        return 1;
    }

    fread(image, sizeof(unsigned char), WIDTH * HEIGHT, inputFile);

    applyLaplacianFilter(image, filteredImage);

    fwrite(filteredImage, sizeof(unsigned char), WIDTH * HEIGHT, outputFile);

    free(image);
    free(filteredImage);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}