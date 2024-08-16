import cv2
import numpy as np
 
image = open('zezo.txt','r').read().split(",")

lst = []

h = 136
w = 166

for i in range(h):
    lst_=[]
    for j in range(w):
        try:
            lst_.append([image[i*w+j]])
        except Exception as e:
            print(e,"-",i,":",j)
    lst.append(lst_.copy())

image = np.asarray(lst, dtype=np.uint8)

cv2.imshow("zezo2.jpg",image)
cv2.imwrite("zezo2.jpg",image)
cv2.waitKey()