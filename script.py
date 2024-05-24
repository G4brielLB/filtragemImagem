import cv2

image = cv2.imread('./zezo_reduzido_v3.jpeg', 0) #esse param 0 fazer ler a img em escala de cinza
rows,cols = image.shape

with open("zezo_bytes.txt", "w") as f:
    for i in range(rows):
        for j in range(cols):
            k = image[i,j]
            f.write(f"{k} ")

print('.data')

print('imagem: .byte ', end='')
for i in range(rows):
    for j in range(cols):
        k = image[i,j]
        print(f"{k}", end=',')
print("")
print(".text")