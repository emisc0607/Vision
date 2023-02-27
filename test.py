import cv2
import numpy as np
import funciones as fn

img =  cv2.imread('img3.png')
h, w, c = img.shape
print(str(h) + ' ' + str(w) + ' ' + str(c))
#Binaria
binn = fn.binaria(img, h, w, 100)
#Gris
gris = fn.grises(img, h, w)
#Suma
sum = fn.suma(img, h, w, 100)
sum = sum.astype(np.uint8)
#Resta
res = fn.resta(img, h, w, 100)
res = res.astype(np.uint8)
#Multiplicacion
mul = fn.multiplicacion(img, h, w, 2)
mul = mul.astype(np.uint8)
#Division
div = fn.division(img, h, w, 2)
div = div.astype(np.uint8)
#Negativo
neg = fn.negativo(img, h, w)
neg = neg.astype(np.uint8)
#Filtro promedio
#Negativo
prom = fn.promedio(img, h, w)
prom = prom.astype(np.uint8)


#cv2.imshow("Original", img)
cv2.imshow("Gris", gris)
#cv2.imshow("Binaria", binn)
#cv2.imshow("Suma", sum)
#cv2.imshow("Resta", res)
#cv2.imshow("Multiplicacion", mul)
#cv2.imshow("Division", div)
#cv2.imshow("Negativo", neg)
cv2.imshow("Promedio", prom)
cv2.waitKey(0)
cv2.destroyAllWindows()
