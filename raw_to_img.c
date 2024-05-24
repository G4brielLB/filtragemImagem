#include <stdio.h>
#include <stdlib.h>

#define WIDTH 332
#define HEIGHT 271

void read_bytes_from_file(const char *filename, unsigned char *image) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    int byte;
    int index = 0;
    while (fscanf(file, "%d", &byte) == 1) {
        if (index >= WIDTH * HEIGHT) {
            fprintf(stderr, "Error: More bytes in file than expected for the given dimensions.\n");
            exit(EXIT_FAILURE);
        }
        image[index++] = (unsigned char)byte;
    }

    if (index != WIDTH * HEIGHT) {
        fprintf(stderr, "Error: Less bytes in file than expected for the given dimensions.\n");
        exit(EXIT_FAILURE);
    }

    fclose(file);
}

void save_image_as_pgm(const char *filename, unsigned char *image, int width, int height) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Write the PGM header
    fprintf(file, "P5\n%d %d\n255\n", width, height);

    // Write the image data
    fwrite(image, sizeof(unsigned char), width * height, file);

    fclose(file);
}

int main() {
    const char *input_filename = "zezo_bytes.txt";
    const char *output_filename = "zezo_raw_to_img.pgm";
    
    // Allocate memory for the image
    unsigned char *image = (unsigned char *)malloc(WIDTH * HEIGHT);
    if (!image) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    // Read bytes from the file
    read_bytes_from_file(input_filename, image);

    // Save the image as a PGM file
    save_image_as_pgm(output_filename, image, WIDTH, HEIGHT);

    // Free allocated memory
    free(image);

    printf("Image saved as %s\n", output_filename);
    return 0;
}
