# Abra o arquivo de texto e leia o conteúdo
with open('zezo_bytes.txt', 'r') as f:
    content = f.read()

# Divida o conteúdo em uma lista de strings
str_values = content.split()

# Converta as strings em inteiros
int_values = [int(val) for val in str_values]

# Converta os inteiros em bytes
byte_values = bytes(int_values)

# Escreva os bytes em um novo arquivo binário
with open('zezo_bytes.bin', 'wb') as f:
    f.write(byte_values)