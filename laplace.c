#include <stdio.h>
#include <stdlib.h>

#define WIDTH 332
#define HEIGHT 271

// Filtro Laplaciano
const int laplacian_filter[3][3] = {
    {0, -1, 0},
    {-1, 4, -1},
    {0, -1, 0}
};

// Converte uma sequência de bytes em uma matriz de pixels
void bytes_to_matrix(unsigned char *bytes, int matrix[HEIGHT][WIDTH]) {
    int i, j, k = 0;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            matrix[i][j] = bytes[k++];
        }
    }
}

// Converte uma matriz de pixels em uma sequência de bytes
void matrix_to_bytes(int matrix[HEIGHT][WIDTH], unsigned char *bytes) {
    int i, j, k = 0;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            bytes[k++] = (unsigned char)matrix[i][j];
        }
    }
}

// Aplica o filtro Laplaciano a uma matriz de pixels
void apply_laplacian_filter(int original[HEIGHT][WIDTH], int result[HEIGHT][WIDTH]) {
    int i, j, k, l;
    for (i = 1; i < HEIGHT - 1; i++) {
        for (j = 1; j < WIDTH - 1; j++) {
            int sum = 0;
            for (k = -1; k <= 1; k++) {
                for (l = -1; l <= 1; l++) {
                    sum += original[i + k][j + l] * laplacian_filter[k + 1][l + 1];
                }
            }
            result[i][j] = sum > 255 ? 255 : sum < 0 ? 0 : sum;
        }
    }
}

int main() {
    const char *input_filename = "zezo_bytes.bin";
    const char *output_filename = "zezo_laplace.pgm";

    // Abrir arquivo e ler sequência de bytes
    FILE *file = fopen(input_filename, "rb");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    unsigned char *bytes = (unsigned char *)malloc(WIDTH * HEIGHT * sizeof(unsigned char));
    if (!bytes) {
        perror("Error allocating memory");
        fclose(file);
        return 1;
    }

    fread(bytes, sizeof(unsigned char), WIDTH * HEIGHT, file);
    fclose(file);

    // Converter bytes em matriz
    int original[HEIGHT][WIDTH];
    bytes_to_matrix(bytes, original);

    // Aplicar filtro Laplaciano
    int result[HEIGHT][WIDTH];
    apply_laplacian_filter(original, result);

    // Converter matriz resultante em bytes
    matrix_to_bytes(result, bytes);

    // Exportar a imagem resultante
    FILE *output_file = fopen(output_filename, "wb");
    if (!output_file) {
        perror("Error creating output file");
        free(bytes);
        return 1;
    }

    // Escrever o cabeçalho PGM
    fprintf(output_file, "P5\n%d %d\n255\n", WIDTH, HEIGHT);

    // Escrever os dados da imagem
    fwrite(bytes, sizeof(unsigned char), WIDTH * HEIGHT, output_file);

    fclose(output_file);

    printf("Image saved as %s\n", output_filename);

    // Liberar memória
    free(bytes);

    return 0;
}
