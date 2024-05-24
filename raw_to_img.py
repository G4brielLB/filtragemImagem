from PIL import Image
import numpy as np

# Função para converter sequência de bytes estilo assembly em uma imagem
def bytes_to_image(byte_sequence, width, height):
    # Converter a string de bytes em uma lista de inteiros
    bytes_list = [int(byte, 16) for byte in byte_sequence.split()]
    
    # Verificar se a quantidade de bytes é adequada para as dimensões fornecidas
    if len(bytes_list) != width * height:
        raise ValueError("A quantidade de bytes não corresponde às dimensões da imagem.")

    # Converter a lista de bytes em uma matriz numpy
    image_array = np.array(bytes_list, dtype=np.uint8).reshape((height, width))

    # Criar uma imagem PIL a partir da matriz numpy
    image = Image.fromarray(image_array, mode='L')

    return image


# Dimensões da imagem
width = 128
height = 96

# Função para ler a sequência de bytes de um arquivo
def read_byte_sequence_from_file(file_path):
    with open(file_path, 'r') as file:
        return file.read()

# Caminho para o arquivo contendo a sequência de bytes
file_path = 'violao_bytes.txt'

# Ler a sequência de bytes do arquivo
byte_sequence = read_byte_sequence_from_file(file_path)

# Gerar a imagem
image = bytes_to_image(byte_sequence, width, height)

# Salvar a imagem resultante
image.save('output_image.png')

# Mostrar a imagem (opcional)
image.show()
