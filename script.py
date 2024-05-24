import cv2

image = cv2.imread('./zezo_reduzido_v2.jpeg') #esse param 0 fazer ler a img em escala de cinza
rows,cols = image.shape
print('.data')

print('imagem: .byte ', end='')
for i in range(rows):
    for j in range(cols):
        k = image[i,j]
        print(f"{k}", end=',')
print("")
print(".text")